#include <CommonControls.h>

/*
 * Simple push button connected to regular, not-interruptable, pin
 * Do not forget to plug 100nF capacitor across the button pins
 * Counts some value till the button pressed
 * Can be used in clock applications or similar
 * The button should be checked by buttonCheckStatus() periodically
 */

const uint8_t   BTN_PIN         = 4;        // Can be any other digital pin

BUTTON  btn(BTN_PIN);

void setup() {
    Serial.begin(115200);
    btn.init();
}

uint16_t value = 0;

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

    if (btn.buttonTick()) {
        ++value;
        Serial.println(value);
    }
}
