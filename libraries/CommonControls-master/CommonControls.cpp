#include <Arduino.h>
#include <Time.h>
#include <TimeLib.h>
#include "CommonControls.h"

//------------------------------------------ backlight of the LCD display (lite version) ----------------------
BL::BL(uint8_t sensorPIN, uint8_t lightPIN, uint8_t start_brightness) {
    sensor_pin          = sensorPIN;
    led_pin             = lightPIN;
    default_brightness  = start_brightness;
    b_night             =  50;
    daily_brightness    = 150;
    b_day               = 500;
}

void BL::init(void) {
    pinMode(led_pin, OUTPUT);
    pinMode(sensor_pin, INPUT);
    emp = 0;
    brightness = new_brightness = default_brightness;
    check_ms = ch_step = 0;
    use_local_time = false;
    automatic = true;
    nightly_brightness = 50;
    evening = morning = 0;                          // This value will be overwritten by config
    adjust();
}

int BL::empAverage(int v) {
    long nv = v *emp_k;
    int round_v = emp_k >> 1;
    emp += (nv - emp + round_v) / emp_k;
    int r = (emp + round_v) / emp_k;
    return r;
}
  
void BL::adjust(void) {
    if (!automatic) return;
  
    uint32_t ms = millis();
    if ((ms > ch_step) && (new_brightness != brightness)) {
        if (new_brightness > brightness) ++brightness; else --brightness;
        analogWrite(led_pin, brightness);
        ch_step = ms + ch_period;
    }

    if (ms < check_ms) return;
    check_ms = ms + period;

    // Turn off the backlight at night
    if (isDark()) {
        new_brightness = nightly_brightness;
        return;
    }
  
    uint16_t light = analogRead(sensor_pin);

    light = empAverage(light);
    if (light < b_night) {
        new_brightness = nightly_brightness;
        return;
    }

    if (off_daily && (light > b_day)) {
        new_brightness = 0;
        return;
    }

    light          = constrain(light, b_night, b_day);
    new_brightness = map(light, b_night, b_day, nightly_brightness, daily_brightness);
    new_brightness = constrain(new_brightness, nightly_brightness, daily_brightness);
}

void BL::setBrightness(uint8_t b) {
    brightness = b;
    automatic = false;
    analogWrite(led_pin, brightness);
}

void BL::turnAuto(bool a) {
    automatic = a;
    check_ms = 0;
    if (a) adjust();    
}

void BL::setLimits(uint16_t dark, uint16_t daylight, uint8_t br_nightly, uint8_t br_daily, bool offDaily) {
    b_night             = dark;
    b_day               = daylight;
    daily_brightness    = br_daily;
    nightly_brightness  = br_nightly;
    off_daily           = offDaily;
}

void BL::setNightPeriod(uint8_t Evening, uint8_t Morning) { // Time in 10-minute intervals from midnight
    if (Evening <= Morning) return;
    if (Evening > 144)      return;
    morning = Morning;
    evening = Evening;
    use_local_time = true;
}

bool BL::isDark(void) {
    if (use_local_time) {
        long now_t = hour(); now_t *= 60;
        now_t += minute();   now_t *= 60;
        now_t += second();
        long m = long(morning) * 600;
        long e = long(evening) * 600;
        return ((now_t < m) || (now_t >= e));
    }

    long light = 0;
    for (uint8_t i = 0; i < 4; ++i) {
        light += analogRead(sensor_pin);
        delay(20);
    }
    light >>= 2;
    return (light < b_night);
}

//------------------------------------------ class BUTTON ------------------------------------------------------
BUTTON::BUTTON(uint8_t ButtonPIN, unsigned int timeout_ms) {
    pt = tick_time = 0;
    button_pin = ButtonPIN;
    over_press = timeout_ms;
}

void BUTTON::changeINTR(void) {                     // Interrupt function, called when the button status changed
    bool keyUp = digitalRead(button_pin);
    unsigned long now_t = millis();
    if (!keyUp) {                                   // The button has been pressed
        if ((pt == 0) || (now_t - pt > over_press)) pt = now_t; 
    } else {
        if (pt > 0) {
            if ((now_t - pt) < shortPress) mode = 1;// short press
            else mode = 2;                          // long press
            pt = 0;
        }
    }
}

uint8_t BUTTON::buttonCheck(void) {                 // Check the button state, called each time in the main loop
    mode = 0;
    bool keyUp = digitalRead(button_pin);           // Read the current state of the button
    uint32_t now_t = millis();
    if (!keyUp) {                                   // The button is pressed
        if ((pt == 0) || (now_t - pt > over_press)) pt = now_t;
    } else {
        if (pt == 0) return 0;
        if ((now_t - pt) < bounce) return 0;
        if ((now_t - pt) > shortPress)              // Long press
            mode = 2;
        else
            mode = 1;
        pt = 0;
    } 
    return mode;
}

bool BUTTON::buttonTick(void) {                     // When the button pressed for a while, generate periodical ticks
    bool keyUp = digitalRead(button_pin);           // Read the current state of the button
    uint32_t now_t = millis();
    if (!keyUp && (now_t - pt > shortPress)) {      // The button have been pressed for a while
        if (now_t - tick_time > tick_timeout) {
            tick_time = now_t;
            return (pt != 0);
        }
    } else {
        if (pt == 0) return false;
        tick_time = 0;
    } 
    return false;
}

//------------------------------------------ class SWITCH ------------------------------------------------------
SWITCH::SWITCH(uint8_t SwitchPIN) {
    pt = 0;
    switch_pin    = SwitchPIN;
}

void SWITCH::init(uint32_t on_to, uint32_t off_to) {
    on_time     = on_to;
    off_time    = off_to;
    pinMode(switch_pin, INPUT_PULLUP);
    last_mode = mode = digitalRead(switch_pin);
    pt = 0;
}

bool SWITCH::status(void) {
    bool sw_on = digitalRead(switch_pin);           // Read the current state of the switch
    uint32_t now_t = millis();
    if (last_mode != sw_on) {                       // Mode changed ftom last time
        pt = now_t;
        last_mode   = sw_on;
    } else {
        uint32_t switch_time    = off_time;
        if (sw_on) switch_time  = on_time;
        if (pt == 0) pt = now_t;
        if ((now_t - pt) >= switch_time) {          // Time to change mode
            mode = sw_on;
            pt = 0;
        }
    }
    return mode;
}

//------------------------------------------ class ENCODER ------------------------------------------------------
ENCODER::ENCODER(uint8_t aPIN, uint8_t bPIN, int16_t initPos) {
    pt = 0; m_pin = aPIN; s_pin = bPIN; pos = initPos;
    min_pos = -32767; max_pos = 32766; ch_b = false; increment = 1;
    changed = 0;
    is_looped = false;
}

void ENCODER::init(void) {
    pinMode(m_pin, INPUT_PULLUP);
    pinMode(s_pin, INPUT_PULLUP);
}

bool ENCODER::write(int16_t initPos) {
    if ((initPos >= min_pos) && (initPos <= max_pos)) {
        pos = initPos;
        return true;
    }
    return false;
}

void ENCODER::reset(int16_t initPos, int16_t low, int16_t upp, uint8_t inc, uint8_t fast_inc, bool looped) {
    min_pos = low; max_pos = upp;
    if (!write(initPos)) initPos = min_pos;
    increment = fast_increment = inc;
    if (fast_inc > increment) fast_increment = fast_inc;
    is_looped = looped;
}

void ENCODER::changeINTR(void) {                    // Interrupt function, called when the channel A of encoder changed
    bool rUp = digitalRead(m_pin);
    unsigned long now_t = millis();
    if (!rUp) {                                     // The channel A has been "pressed"
        if ((pt == 0) || (now_t - pt > over_press)) {
            pt = now_t;
            ch_b = digitalRead(s_pin);
        }
    } else {
        if (pt > 0) {
            uint8_t inc = increment;
            if ((now_t - pt) < over_press) {
                if ((now_t - changed) < fast_timeout) inc = fast_increment;
                    changed = now_t;
                    if (ch_b) pos -= inc; else pos += inc;
                    if (pos > max_pos) { 
                        if (is_looped)
                            pos = min_pos;
                        else 
                            pos = max_pos;
                    }
                    if (pos < min_pos) {
                        if (is_looped)
                            pos = max_pos;
                        else
                            pos = min_pos;
                    }
                }
                pt = 0; 
        }
    }
}
