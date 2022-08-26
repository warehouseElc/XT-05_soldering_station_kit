#include <Time.h>
#include <TimeLib.h>
#include <DS3232RTC.h>
#include <CommonControls.h>

/*
 * Backlight control of lcd display 16x2 or similar
 * This time we can use Real Time clock module, DS3231, to setup
 * morning and evening times. The bakckight would be dimmed
 * to the night brightness at evening and turn on at morning
 * 
 * ARDUINO      lcd/other components
 * A0 ---+----- photo resistor -> +5v
 *       +----- 10k -> gnd
 * D9 --------- lcd brightness pin
 * A5 --------- RTC SCL
 * A4 --------- RTC SDA
 */

const uint8_t   LIGHT_SENSOR    = A0;       // Can be any other analog pin
const uint8_t   LCD_BLGHT_PIN   = 9;        // Can be any other PWM-capable pin

const uint16_t  SENSOR_DARK     =  50;      // A0 readings when it is dark
const uint16_t  SENSOR_DAYLIGHT = 500;      // A0 readings when it is day time and backlight should be switched off
const uint8_t   BL_DARK         = 1;        // PWM signal to brightness pin at night
const uint8_t   BL_DAY_MAX      = 150;      // PWM signal to brightness pin at day
const uint8_t   MORNING_TIME    =  54;      // The time of morning (in 10-minutes interval), 9:00
const uint8_t   EVENING_TIME    = 115;      // The time of evening (in 10-minutes interval), 19:05

BL  bckLight(LIGHT_SENSOR, LCD_BLGHT_PIN);

void setup() {
    time_t now_t = RTC.get();               // Read time from RTC module
    setTime(now_t);                         // Initialize arduino system time
    
    bckLight.init();
    // Setup lcd backlight parameters. True means turn-off the backlight at day time
    bckLight.setLimits(SENSOR_DARK, SENSOR_DAYLIGHT, BL_DARK, BL_DAY_MAX, true);
    bckLight.setNightPeriod(EVENING_TIME, MORNING_TIME);
}

void loop() {
    bckLight.adjust();
}
