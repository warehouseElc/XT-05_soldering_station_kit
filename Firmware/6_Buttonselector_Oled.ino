#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

// the number of the input pushbutton pin
const int i1Pin = 2;    
const int i2Pin = 3;    
const int i3Pin = 4;    
const int i4Pin = 5;     
const int i5Pin = 6;     
const int i6Pin = 7;     
// the number of the output pin
const int o1Pin =  8;      
const int o2Pin =  9; 
const int o3Pin =  10; 
const int o4Pin =  11; 
const int o5Pin =  12; 
const int o6Pin =  13; 

// variables will change:
int i1State = 0;         // variable for reading the pushbutton status
int i2State = 0;         // variable for reading the pushbutton status
int i3State = 0;         // variable for reading the pushbutton status
int i4State = 0;         // variable for reading the pushbutton status
int i5State = 0;         // variable for reading the pushbutton status
int i6State = 0;         // variable for reading the pushbutton status

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.display();
  delay(500);
  display.clearDisplay();
  
  // initialize
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("WH207");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,25);
  display.println("Soldering Station");
  display.display();
  
  // initialize the LED pin as an output:
  pinMode(o1Pin, OUTPUT);
  pinMode(o2Pin, OUTPUT);
  pinMode(o3Pin, OUTPUT);
  pinMode(o4Pin, OUTPUT);
  pinMode(o5Pin, OUTPUT);
  pinMode(o6Pin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(i1Pin, INPUT);
  pinMode(i2Pin, INPUT);
  pinMode(i3Pin, INPUT);
  pinMode(i4Pin, INPUT);
  pinMode(i5Pin, INPUT);
  pinMode(i6Pin, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  i1State = digitalRead(i1Pin);
  i2State = digitalRead(i2Pin);
  i3State = digitalRead(i3Pin);
  i4State = digitalRead(i4Pin);
  i5State = digitalRead(i5Pin);
  i6State = digitalRead(i6Pin);


  
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (i1State == HIGH) {              // turn Output 1:
    digitalWrite(o1Pin, HIGH);
    digitalWrite(o2Pin, LOW);
    digitalWrite(o3Pin, LOW);
    digitalWrite(o4Pin, LOW);
    digitalWrite(o5Pin, LOW);
    digitalWrite(o6Pin, LOW);
  } 
  else if (i2State == HIGH) {        // turn Output 2:
    digitalWrite(o1Pin, LOW);
    digitalWrite(o2Pin, HIGH);
    digitalWrite(o3Pin, LOW);
    digitalWrite(o4Pin, LOW);
    digitalWrite(o5Pin, LOW);
    digitalWrite(o6Pin, LOW);
  } 
  else if (i3State == HIGH) {        // turn Output 3:
    digitalWrite(o1Pin, LOW);
    digitalWrite(o2Pin, LOW);
    digitalWrite(o3Pin, HIGH);
    digitalWrite(o4Pin, LOW);
    digitalWrite(o5Pin, LOW);
    digitalWrite(o6Pin, LOW);
  } 
  else if (i4State == HIGH) {        // turn Output 4:
    digitalWrite(o1Pin, LOW);
    digitalWrite(o2Pin, LOW);
    digitalWrite(o3Pin, LOW);
    digitalWrite(o4Pin, HIGH);
    digitalWrite(o5Pin, LOW);
    digitalWrite(o6Pin, LOW);
  } 
  else if (i5State == HIGH) {        // turn Output 5:
    digitalWrite(o1Pin, LOW);
    digitalWrite(o2Pin, LOW);
    digitalWrite(o3Pin, LOW);
    digitalWrite(o4Pin, LOW);
    digitalWrite(o5Pin, HIGH);
    digitalWrite(o6Pin, LOW);
  } 
  if (i6State == HIGH) {        // turn Output 6:
    digitalWrite(o1Pin, LOW);
    digitalWrite(o2Pin, LOW);
    digitalWrite(o3Pin, LOW);
    digitalWrite(o4Pin, LOW);
    digitalWrite(o5Pin, LOW);
    digitalWrite(o6Pin, HIGH);
  } 
}
