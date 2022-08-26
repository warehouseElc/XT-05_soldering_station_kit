#include <CommonControls.h>

/*
 * Simple push button connected to regular, not-interruptable, pin
 * Do not forget to plug 100nF capacitor across the button pins
 * One os the button pin connect to the Arduino, another - to the ground
 */

const uint8_t   BTN_PIN         = 4;        // Can be any other digital pin

BUTTON  btn(BTN_PIN);

void setup() {
    Serial.begin(115200);
    btn.init();
}

void loop() {
    uint8_t bStatus = btn.buttonCheck();
    switch (bStatus) {
        case 2:                             // long press;
            Serial.println("Button long press");
            break;
        case 1:                             // short press
            Serial.println("Button pressed");
            break;
        case 0:                             // Not pressed
        default:
            break;
    }
}
