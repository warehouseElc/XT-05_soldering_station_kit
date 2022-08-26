#include <Time.h>
#include <CommonControls.h>

/*
 * Backlight control of LED display, i.e 4*7-segmant indicator or similar
 * The backlight brightness growing with the ambient light
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
const uint8_t   BL_DAY_MAX      = 255;      // PWM signal to brightness pin at day


BL  bckLight(LIGHT_SENSOR, LCD_BLGHT_PIN);

void setup() {
    bckLight.init();
    // Setup lcd backlight parameters. False means do not turn-off the backlight at day time
    bckLight.setLimits(SENSOR_DARK, SENSOR_DAYLIGHT, BL_DARK, BL_DAY_MAX, false);
}

void loop() {
    bckLight.adjust();
}
