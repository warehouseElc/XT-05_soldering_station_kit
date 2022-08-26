#include <CommonControls.h>

/*
 * Backlight control of lcd display 16x2 or similar
 * The backlight brightness growing with the ambient light
 * till day time, then the backlight is turned off
 * 
 * ARDUINO      lcd/other components
 * A0 ---+----- photo resistor -> +5v
 *       +----- 10k -> gnd
 * D9 --------- lcd brightness pin
 */

const uint8_t   LIGHT_SENSOR    = A0;       // Can be any other analog pin
const uint8_t   LCD_BLGHT_PIN   = 9;        // Can be any other PWM-capable pin

const uint16_t  SENSOR_DARK     =  50;      // A0 readings when it is dark
const uint16_t  SENSOR_DAYLIGHT = 500;      // A0 readings when it is day time and backlight should be switched off
const uint8_t   BL_DARK         = 1;        // PWM signal to brightness pin at night
const uint8_t   BL_DAY_MAX      = 150;      // PWM signal to brightness pin at day

BL  bckLight(LIGHT_SENSOR, LCD_BLGHT_PIN);

void setup() {
    bckLight.init();
    // Setup lcd backlight parameters. True means turn-off the backlight at day time
    bckLight.setLimits(SENSOR_DARK, SENSOR_DAYLIGHT, BL_DARK, BL_DAY_MAX, true);
}

void loop() {
    bckLight.adjust();
}
