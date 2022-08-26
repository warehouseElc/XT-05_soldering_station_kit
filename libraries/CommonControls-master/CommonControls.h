#ifndef CommonControls_h
#define CommonControls_h

//------------------------------------------ backlight of the LCD display (lite version) ----------------------
class BL {
    public:
        BL(uint8_t sensorPIN, uint8_t lightPIN, uint8_t start_brightness = 128);
        void        init(void);                    // Initialize the data
        void        adjust(void);                  // Automatically adjust the brightness
        int         getSensorValue(void)           { return analogRead(sensor_pin); }
        void        setBrightness(uint8_t b);
        void        turnAuto(bool a);
        void        setLimits(uint16_t dark, uint16_t daylight, uint8_t br_nightly, uint8_t br_daily, bool offDaily = true);
        void        setNightPeriod(uint8_t Evening, uint8_t Morning);
        bool        isDark(void);                   // Whether it is night time or it is dark here
    private:
        int         empAverage(int v);              // Exponential average value
        uint8_t     sensor_pin;                     // Light sensor pin
        uint8_t     led_pin;                        // Led PWM pin
        bool        off_daily;                      // Whether turn the light daily
        uint32_t    check_ms;                        // Time in ms when the sensor was checked
        uint32_t    ch_step;                        // The time in ms when the brightness can be adjusted
        bool        automatic;                      // Whether the backlight should be adjusted automatically
        bool        use_local_time;                 // Whether to use local time to switch off the light nightly
        uint8_t     brightness;                     // The backlight brightness
        uint8_t     new_brightness;                 // The baclight brightness to set up
        uint8_t     evening, morning;               // The time of evening and morning (in 10-minutes interval)
        long        emp;                            // Exponential average value
        uint8_t     default_brightness;             // Default brightness of backlight
        uint16_t    b_night;                        // light sensor value of the night
        uint16_t    b_day;                          // light sensor value of the day light
        uint8_t     daily_brightness;               // The maximum brightness of backlight when light between b_night and b_day
        uint8_t     nightly_brightness;             // The brightness to use nightly
        const uint8_t       emp_k = 8;              // The exponential average coefficient
        const uint16_t      period  = 200;          // The period in ms to check the photoresister
        const uint16_t      ch_period = 5;          // The period to adjust brightness
};

//------------------------------------------ class BUTTON ------------------------------------------------------
class BUTTON {
    public:
        BUTTON(uint8_t ButtonPIN, unsigned int timeout_ms = 3000);
        void        init(void)                      { pinMode(button_pin, INPUT_PULLUP); }
        void        setTimeout(uint16_t to = 3000)  { over_press = to; }
        uint8_t     intButtonStatus(void)                     { uint8_t m = mode; mode = 0; return m; }
        void        changeINTR(void);
        uint8_t     buttonCheck(void);
        bool        buttonTick(void);
    private:
        uint32_t    tick_time;                      // The time in ms when the button Tick was set
        uint8_t     button_pin;                     // The pin number connected to the button
        uint16_t    over_press;                     // Maximum time in ms the button can be pressed
        volatile uint8_t    mode;                   // The button mode: 0 - not pressed, 1 - pressed, 2 - long pressed
        volatile uint32_t   pt;                     // Time in ms when the button was pressed (press time)
        const uint16_t      tick_timeout = 200;     // Period of button tick, while the button is pressed 
        const uint16_t      shortPress  = 900;      // If the button was pressed less that this timeout, we assume the short button press
        const uint8_t       bounce      = 50;       // Bouncing timeout (ms)
};

//------------------------------------------ class SWITCH ------------------------------------------------------
class SWITCH {
    public:
        SWITCH(uint8_t SwitchPIN);
        void        init(uint32_t on_to = 500, uint32_t off_to = 500);
        bool        status(void);
    private:
        uint8_t     switch_pin;                     // The pin number connected to the button
        bool        mode;                           // The switch mode on (true)/off
        bool        last_mode;                      // The mode measured last time
        uint32_t    pt;                             // Time in ms when the switch status changed
        uint32_t    on_time  = 500;                 // Turn on  interval (ms)
        uint32_t    off_time = 500;                 // Turn off interval (ms)    
};

//------------------------------------------ class ENCODER ------------------------------------------------------
class ENCODER {
    public:
        ENCODER(uint8_t aPIN, uint8_t bPIN, int16_t initPos = 0);
        void        init(void);
        void        set_increment(uint8_t inc)      { increment = inc; }
        uint8_t     get_increment(void)             { return increment; }
        int16_t     read(void)                      { return pos; }
        void        reset(int16_t initPos, int16_t low, int16_t upp, uint8_t inc = 1, uint8_t fast_inc = 0, bool looped = false);
        bool        write(int16_t initPos);
        void        changeINTR(void);
    private:
        int32_t     min_pos, max_pos;
        uint8_t     m_pin, s_pin;                     // The pin numbers connected to the main channel and to the socondary channel
        bool        is_looped;                      // Whether the encoder is looped
        uint8_t     increment;                      // The value to add or subtract for each encoder tick
        uint8_t     fast_increment;                 // The value to change encoder when in runs quickly
        volatile uint32_t   pt;                     // Time in ms when the encoder was rotaded
        volatile uint32_t   changed;                // Time in ms when the value was changed
        volatile bool       ch_b;
        volatile int16_t    pos;                    // Encoder current position
        const uint16_t      fast_timeout    = 300;  // Time in ms to change encoder quickly
        const uint16_t      over_press      = 1000;
};

#endif