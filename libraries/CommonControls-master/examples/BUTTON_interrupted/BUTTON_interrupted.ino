#include <CommonControls.h>

/*
 * Simple push button connected to regular, not-interruptable, pin
 * Do not forget to plug 100nF capacitor across the button pins
 * When the button pressed the interrupt handler should calls the changeINTR() method
 * In this case it is not necessery to test the button status
 * You cannot miss the press button event
 */

const uint8_t   BTN_PIN         = 2;        // Can be interrupt pin only (2,3 on atmega328)

BUTTON  btn(BTN_PIN);

void buttonPress(void) {
    btn.changeINTR();
}

void setup() {
    Serial.begin(115200);
    btn.init();
    attachInterrupt(digitalPinToInterrupt(BTN_PIN), buttonPress,   CHANGE);
}

uint16_t value = 0;

void loop() {
    uint8_t bStatus = btn.intButtonStatus();
    switch (bStatus) {
        case 2:                             // long press;
            Serial.println("Button long press");
            break;
        case 1:                             // short press
            Serial.println("Button pressed");
            break;
        case 0:                             // Not pressed
        default:
            Serial.println("Not pressed");
            break;
    }
    delay(1000);
}
