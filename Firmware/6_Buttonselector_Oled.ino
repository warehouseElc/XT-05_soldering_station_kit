#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSansBold9pt7b.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

// the number of the input pushbutton pin
const int i1Pin = 2;    
const int i2Pin = 3;    
const int i3Pin = 4;    
const int i4Pin = 7;     
const int i5Pin = 6;     
const int i6Pin = 5;     
// the number of the output pin
const int o1Pin =  13;      
const int o2Pin =  12; 
const int o3Pin =  11; 
const int o4Pin =  8; 
const int o5Pin =  9; 
const int o6Pin =  10; 
// input button
const int upiPin =  A0; 
const int dwiPin =  A3; 
// simulated output
const int upoPin =  A1; 
const int dwoPin =  A2; 

// variables will change:
int i1State = 0;         // variable for reading the pushbutton status
int i2State = 0;         // variable for reading the pushbutton status
int i3State = 0;         // variable for reading the pushbutton status
int i4State = 0;         // variable for reading the pushbutton status
int i5State = 0;         // variable for reading the pushbutton status
int i6State = 0;         // variable for reading the pushbutton status
int upState = 0;         // variable for reading the pushbutton status
int dwState = 0;         // variable for reading the pushbutton status
int state = 0, Loadstate=0;

void setup() {
  // initialize
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  

  display.fillScreen(WHITE);
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(1,23);
  display.println("SOLDERING STATION KIT");
  display.setFont(&FreeSansBold9pt7b);
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(5,15);
  display.println("WAREHOUSE");
  display.display();
  delay(1000);
  display.setFont();

  pinMode(o1Pin, OUTPUT);
  pinMode(o2Pin, OUTPUT);
  pinMode(o3Pin, OUTPUT);
  pinMode(o4Pin, OUTPUT);
  pinMode(o5Pin, OUTPUT);
  pinMode(o6Pin, OUTPUT);
  pinMode(upoPin, OUTPUT);
  pinMode(dwoPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(i1Pin, INPUT);
  pinMode(i2Pin, INPUT);
  pinMode(i3Pin, INPUT);
  pinMode(i4Pin, INPUT);
  pinMode(i5Pin, INPUT);
  pinMode(i6Pin, INPUT);
  pinMode(upiPin, INPUT);
  pinMode(dwiPin, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  i1State = digitalRead(i1Pin);
  i2State = digitalRead(i2Pin);
  i3State = digitalRead(i3Pin);
  i4State = digitalRead(i4Pin);
  i5State = digitalRead(i5Pin);
  i6State = digitalRead(i6Pin);
  upState = digitalRead(upiPin);
  dwState = digitalRead(dwiPin);


  if (upState == HIGH) {                                       // turn up
  display.fillScreen(BLACK);
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(20,0);
  display.println(">>>");
  display.display();
                                                              
    digitalWrite(upoPin, HIGH);
    delay(50);
    digitalWrite(dwoPin, HIGH);
    delay(50);
    digitalWrite(upoPin, LOW);
    delay(50);
    digitalWrite(dwoPin, LOW);
  } 
  
  if (dwState == HIGH) {                                     // turn down
  display.fillScreen(BLACK);
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(20,0);
  display.println("<<<");
  display.display();
  
    digitalWrite(dwoPin, HIGH);
    delay(50);
    digitalWrite(upoPin, HIGH);
    delay(50);
    digitalWrite(dwoPin, LOW);
    delay(50);
    digitalWrite(upoPin, LOW);
  } 
  
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (i1State == HIGH) {                                     // turn Output 1:
  display.fillScreen(BLACK);
  display.drawLine(5,27,122,27, WHITE);
  display.drawLine(122,0,122,27, WHITE);
  display.drawLine(122,27,127,32, WHITE);  //
  display.drawLine(45,32,40,27, WHITE);    //
  display.drawLine(85,27,80,32, WHITE);    //
  display.fillTriangle(0,32,0,27,5,27, WHITE);
  display.fillRect(0,0,5,27,WHITE);
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(20,0);
  display.println("T-115");
  display.display();
  
    digitalWrite(o1Pin, HIGH);
    digitalWrite(o2Pin, LOW);
    digitalWrite(o3Pin, LOW);
    digitalWrite(o4Pin, LOW);
    digitalWrite(o5Pin, LOW);

  } 
  else if (i2State == HIGH) {                                  // turn Output 2:
  display.clearDisplay();
  display.drawLine(5,0,5,27, WHITE);
  display.drawLine(5,27,122,27, WHITE);
  display.drawLine(122,0,122,27, WHITE);
  display.drawLine(5,27,0,32, WHITE);      //
  display.drawLine(122,27,127,32, WHITE);  //
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(20,0);
  display.println("T-210");
  display.fillTriangle(40,27,45,32,45,27, WHITE);
  display.fillRect(45,27,37,5,WHITE);
  display.fillTriangle(80,32,85,27,80,27, WHITE);
  display.display();
  
    digitalWrite(o1Pin, LOW);
    digitalWrite(o2Pin, HIGH);
    digitalWrite(o3Pin, LOW);
    digitalWrite(o4Pin, LOW);
    digitalWrite(o5Pin, LOW);

  } 
  else if (i3State == HIGH) {                                         // turn Output 3:
  display.clearDisplay();
  display.drawLine(5,0,5,27, WHITE);
  display.drawLine(5,27,122,27, WHITE);
  display.drawLine(122,0,122,27, WHITE);
  display.drawLine(122,27,127,32, WHITE);  //
  display.drawLine(85,27,80,32, WHITE);    //
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(30,0);
  display.println("IRON");
  display.fillTriangle(0,32,5,32,5,27, WHITE);
  display.fillRect(5,27,35,5,WHITE);
  display.fillTriangle(40,32,40,27,45,32, WHITE);
  display.display();  
  
    digitalWrite(o1Pin, LOW);
    digitalWrite(o2Pin, LOW);
    digitalWrite(o3Pin, HIGH);
    digitalWrite(o4Pin, LOW);
    digitalWrite(o5Pin, LOW);

  } 
  else if (i4State == HIGH) {                                     // turn Output 4:
  display.clearDisplay();
  display.drawLine(5,0,5,27, WHITE);
  display.drawLine(5,27,122,27, WHITE);
  display.drawLine(122,0,122,27, WHITE);
  display.drawLine(5,27,0,32, WHITE);      //
  display.drawLine(45,32,40,27, WHITE);    //
  display.fillTriangle(122,32,127,32,122,27, WHITE);
  display.fillRect(85,27,37,5,WHITE);
  display.fillTriangle(80,32,85,27,85,32, WHITE);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(24,0);
  display.println("HOT-AIR");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(40,18);
  display.println("STATION");
  display.display();
  
    digitalWrite(o1Pin, LOW);
    digitalWrite(o2Pin, LOW);
    digitalWrite(o3Pin, LOW);
    digitalWrite(o4Pin, HIGH);
    digitalWrite(o5Pin, LOW);

  } 
  else if (i5State == HIGH) {                                     // turn Output 5:
  display.clearDisplay();
  display.drawLine(5,0,5,27, WHITE);
  display.drawLine(5,27,122,27, WHITE);
  display.drawLine(5,27,0,32, WHITE);      //
  display.drawLine(45,32,40,27, WHITE);    //
  display.drawLine(85,27,80,32, WHITE);    //
  display.fillTriangle(122,27,127,32,127,27, WHITE);
  display.fillRect(122,0,7,27,WHITE);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(45,0);
  display.println("PCB");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(33,18);
  display.println("PRE-HEATER");
  display.display();
  
    digitalWrite(o1Pin, LOW);
    digitalWrite(o2Pin, LOW);
    digitalWrite(o3Pin, LOW);
    digitalWrite(o4Pin, LOW);
    digitalWrite(o5Pin, HIGH);

  } 
 
  if (state == 0 && i6State == HIGH) {      // turn ON Output 6:
    state = 1;
    Loadstate=!Loadstate;
  }
  if (state == 1 && i6State == LOW) {   
    state = 0;
  }
   if (Loadstate==HIGH){
    display.fillRoundRect(115,2,5,5,4, WHITE);
    display.display();
    digitalWrite(o6Pin, HIGH);
   }
   else{
    display.fillRoundRect(115,2,5,5,4, BLACK);
    display.display();
    digitalWrite(o6Pin, LOW);             // turn OFF Output 6:
   }
}
