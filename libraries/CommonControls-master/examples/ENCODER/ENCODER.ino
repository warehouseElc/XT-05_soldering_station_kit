#include <CommonControls.h>

/*
 * Simple key switch can be on or off
 * Do not forget to plug 100nF capacitor across the switch pins
 * 
 */

const uint8_t R_MAIN_PIN    = 3;                        // Interrupt pin only
const uint8_t R_SECD_PIN    = 4;                        // Any digital pin
const uint8_t R_BUTN_PIN    = 5;                        // Any digital pin

// Rotary encoder consists of encoder and button classes
ENCODER rotEncoder(R_MAIN_PIN, R_SECD_PIN);
BUTTON  rotButton(R_BUTN_PIN);

// Encoder interrupt handler
void rotEncChange(void) {
    rotEncoder.changeINTR();
}

void setup() {
    Serial.begin(115200);

    // Initialize rotary encoder
    rotEncoder.init();
    rotButton.init();
    rotEncoder.reset(0, -200, 200, 1, 5);
    delay(500);
    attachInterrupt(digitalPinToInterrupt(R_MAIN_PIN), rotEncChange,   CHANGE);
}


void loop() {
    static int16_t  old_pos     = rotEncoder.read();

    int16_t pos = rotEncoder.read();
    if (old_pos != pos) {
        Serial.print("New encoder value = "); Serial.println(pos);
        old_pos = pos;
    }

    uint8_t bStatus = rotButton.buttonCheck();
    switch (bStatus) {
        case 2:                                         // long press;
            Serial.println("Chanding encoder interval to [0; 600]");
            rotEncoder.reset(0, 0, 600, 1, 10);
            break;
        case 1:                                         // short press
            Serial.println("Chanding encoder interval to [-1000; 0]");
            rotEncoder.reset(0, -1000, 0, 1, 5);
            break;
        case 0:                                         // Not pressed
        default:
            break;
    }
    delay(500);
}
