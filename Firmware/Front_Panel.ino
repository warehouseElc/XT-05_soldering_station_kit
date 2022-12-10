//https://wokwi.com/projects/350487167572640339

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeMono12pt7b.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
// clock
int h = 0;
int m = 0;
int s = 0;
int flag = 0;
int TIME = 0;
int state1 = 0;
int state2 = 0;
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
const int upiPin =  A7; 
const int dwiPin =  A6; 
// simulated output
const int upoPin =  A1; 
const int dwoPin =  A2;
const int stbyPin =  A3;
// Buzzer
const byte buzzerPIN = A0;  
bool buzzerFlag = false;
bool buzzerFlag1 = false;
bool buzzerFlag2 = false;
bool buzzerFlag3 = false;
bool buzzerFlag4 = false;
bool buzzerFlag5 = false;
bool buzzerFlag6 = false;
bool buzzerFlag8 = true;
bool buzzerFlag9 = false;
// variables will change: for reading the pushbutton status
int i1State = 0;         
int i2State = 0;         
int i3State = 0;         
int i4State = 0;         
int i5State = 0;         
int i6State = 0;         
int upState = 0;         
int dwState = 0;         
int state = 0, Loadstate=0;
int state6 = 0, Loadstate6=0;


void setup() {
  // initialize
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  // Welcome display 
  display.fillScreen(WHITE);
  display.setFont(&FreeSansBold9pt7b);
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(5,15);
  display.println("WAREHOUSE");
  display.setFont();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(1,23);
  display.println("SOLDERING STATION KIT");
  display.display();
  // initialize pin ouput:
  pinMode(o1Pin, OUTPUT);
  pinMode(o2Pin, OUTPUT);
  pinMode(o3Pin, OUTPUT);
  pinMode(o4Pin, OUTPUT);
  pinMode(o5Pin, OUTPUT);
  pinMode(o6Pin, OUTPUT);
  pinMode(upoPin, OUTPUT);
  pinMode(dwoPin, OUTPUT);
  pinMode(stbyPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(i1Pin, INPUT);
  pinMode(i2Pin, INPUT);
  pinMode(i3Pin, INPUT);
  pinMode(i4Pin, INPUT);
  pinMode(i5Pin, INPUT);
  pinMode(i6Pin, INPUT);
  pinMode(upiPin, INPUT);
  pinMode(dwiPin, INPUT);
  // welcome action
  tone(buzzerPIN, 3520, 60);
  digitalWrite(o5Pin, HIGH);
  digitalWrite(o4Pin, HIGH);
  digitalWrite(o3Pin, HIGH);
  digitalWrite(o2Pin, HIGH);
  digitalWrite(o1Pin, HIGH);  
  delay(50);
  digitalWrite(o5Pin, LOW);
  digitalWrite(o4Pin, LOW);
  digitalWrite(o3Pin, LOW);
  digitalWrite(o2Pin, LOW);
  digitalWrite(o1Pin, LOW);  
  delay(100);
  digitalWrite(o5Pin, HIGH);
  digitalWrite(o4Pin, HIGH);
  digitalWrite(o3Pin, HIGH);
  digitalWrite(o2Pin, HIGH);
  digitalWrite(o1Pin, HIGH);  
  delay(200);
  digitalWrite(o5Pin, LOW);
  digitalWrite(o4Pin, LOW);
  digitalWrite(o3Pin, LOW);
  digitalWrite(o2Pin, LOW);
  digitalWrite(o1Pin, LOW); 
  delay(500);
    tone(buzzerPIN, 1397, 200);
    delay(150);
    tone(buzzerPIN, 1568, 200);
    delay(150);
    tone(buzzerPIN, 2093, 300);
    delay(250);
    noTone(buzzerPIN);
  digitalWrite(o1Pin, HIGH);
  delay(100);
  digitalWrite(o2Pin, HIGH);
  digitalWrite(o1Pin, LOW);
  delay(100);
  digitalWrite(o3Pin, HIGH);
  digitalWrite(o2Pin, LOW);
  digitalWrite(o1Pin, LOW);
  delay(100);
  digitalWrite(o4Pin, HIGH);
  digitalWrite(o3Pin, LOW);
  digitalWrite(o2Pin, LOW);
  digitalWrite(o1Pin, LOW);
  delay(100);
  digitalWrite(o5Pin, HIGH);
  digitalWrite(o4Pin, LOW);
  digitalWrite(o3Pin, LOW);
  digitalWrite(o2Pin, LOW);
  digitalWrite(o1Pin, LOW);  
  delay(100);
  digitalWrite(o5Pin, LOW);
  digitalWrite(o4Pin, LOW);
  digitalWrite(o3Pin, LOW);
  digitalWrite(o2Pin, LOW);
  digitalWrite(o1Pin, LOW);  
  delay(200);
  digitalWrite(o5Pin, HIGH);
  delay(100);
  digitalWrite(o5Pin, LOW);
  digitalWrite(o4Pin, HIGH);
  delay(100);
  digitalWrite(o5Pin, LOW);
  digitalWrite(o4Pin, LOW);
  digitalWrite(o3Pin, HIGH);
  delay(100);
  digitalWrite(o5Pin, LOW);
  digitalWrite(o4Pin, LOW);
  digitalWrite(o3Pin, LOW);
  digitalWrite(o2Pin, HIGH);
  delay(100);
  digitalWrite(o5Pin, LOW);
  digitalWrite(o4Pin, LOW);
  digitalWrite(o3Pin, LOW);
  digitalWrite(o2Pin, LOW);
  digitalWrite(o1Pin, HIGH);
  delay(100);
  digitalWrite(o5Pin, LOW);
  digitalWrite(o4Pin, LOW);
  digitalWrite(o3Pin, LOW);
  digitalWrite(o2Pin, LOW);
  digitalWrite(o1Pin, LOW);
  delay(500);  
  display.fillScreen(BLACK);
  display.drawLine(5,27,122,27, WHITE);
  display.drawLine(122,0,122,27, WHITE);
  display.drawLine(122,27,127,32, WHITE);  //
  display.drawLine(45,32,40,27, WHITE);    //
  display.drawLine(85,27,80,32, WHITE);    //
  display.drawLine(5,27,0,32, WHITE); 
  display.drawLine(5,0,5,27, WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,8);
  display.println("Ready to select");
  display.display();
}

void loop() {
  // read the state of the pushbutton value: 
  i1State = digitalRead(i1Pin);
  i2State = digitalRead(i2Pin);
  i3State = digitalRead(i3Pin);
  i4State = digitalRead(i4Pin);
  i5State = digitalRead(i5Pin);
  i6State = digitalRead(i6Pin);
  upState = analogRead(A7) < 100 ? 0 : 1;
  dwState = analogRead(A6) < 100 ? 0 : 1;
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (i1State == HIGH) {                                   // turn Output 1:
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
if (buzzerFlag1 == false ) {
     tone(buzzerPIN, 3520, 60);
    delay(50);
    noTone(buzzerPIN);
    buzzerFlag1 = true;
    buzzerFlag2 = false;
    buzzerFlag3 = false;
    buzzerFlag4 = false;
    buzzerFlag5 = false;
    }
  } 
  else if (i2State == HIGH) {                                  // turn Output 2:
  display.clearDisplay();
  display.drawLine(5,0,5,27, WHITE);
  display.drawLine(5,27,122,27, WHITE);
  display.drawLine(122,0,122,27, WHITE);
  display.drawLine(5,27,0,32, WHITE);      
  display.drawLine(122,27,127,32, WHITE);  
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
if (buzzerFlag2 == false ) {
    tone(buzzerPIN, 3520, 60);
    delay(50);
    noTone(buzzerPIN);
    buzzerFlag1 = false;
    buzzerFlag2 = true;
    buzzerFlag3 = false;
    buzzerFlag4 = false;
    buzzerFlag5 = false;
    }
  } 
  else if (i3State == HIGH) {                                         // turn Output 3:
  display.clearDisplay();
  display.drawLine(5,0,5,27, WHITE);
  display.drawLine(5,27,122,27, WHITE);
  display.drawLine(122,0,122,27, WHITE);
  display.drawLine(122,27,127,32, WHITE);  
  display.drawLine(85,27,80,32, WHITE);    
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
if (buzzerFlag3 == false ) {
    tone(buzzerPIN, 3520, 60);
    delay(50);
    noTone(buzzerPIN);
    buzzerFlag1 = false;
    buzzerFlag2 = false;
    buzzerFlag3 = true;
    buzzerFlag4 = false;
    buzzerFlag5 = false;
    }
  } 
  else if (i4State == HIGH) {                                     // turn Output 4:
  display.clearDisplay();
  display.drawLine(5,0,5,27, WHITE);
  display.drawLine(5,27,122,27, WHITE);
  display.drawLine(122,0,122,27, WHITE);
  display.drawLine(5,27,0,32, WHITE);      
  display.drawLine(45,32,40,27, WHITE);    
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
if (buzzerFlag4 == false ) {
    tone(buzzerPIN, 3520, 60);
    delay(50);
    noTone(buzzerPIN);
    buzzerFlag1 = false;
    buzzerFlag2 = false;
    buzzerFlag3 = false;
    buzzerFlag4 = true;
    buzzerFlag5 = false;
    }
  } 
  else if (i5State == HIGH) {                                     // turn Output 5:
  display.clearDisplay();
  display.drawLine(5,0,5,27, WHITE);
  display.drawLine(5,27,122,27, WHITE);
  display.drawLine(5,27,0,32, WHITE);      
  display.drawLine(45,32,40,27, WHITE);    
  display.drawLine(85,27,80,32, WHITE);    
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
if (buzzerFlag5 == false ) {
    tone(buzzerPIN, 3520, 60);
    delay(50);
    noTone(buzzerPIN);
    buzzerFlag1 = false;
    buzzerFlag2 = false;
    buzzerFlag3 = false;
    buzzerFlag4 = false;
    buzzerFlag5 = true;
    }
  } 
 
  if (state6 == 0 && i6State == HIGH) {                       // turn ON Output 6:
    state6 = 1;
    Loadstate6=!Loadstate6;
  }
  if (state6 == 1 && i6State == LOW) {   
    state6 = 0;
  
  }
   if (Loadstate6==HIGH){
    display.fillRoundRect(107,20,5,5,4, WHITE);
    display.display();
    digitalWrite(o6Pin, HIGH);
    if (buzzerFlag6 == false ) {
        tone(buzzerPIN, 3520, 60);
        delay(50);
        noTone(buzzerPIN);
        buzzerFlag = false;
        buzzerFlag6 = true;
        }
    }
   else{                                                       // turn OFF Output 6:
    display.fillRoundRect(107,20,5,5,4, BLACK);
    display.display();
    digitalWrite(o6Pin, LOW); 
    if (buzzerFlag == false ) {
        tone(buzzerPIN, 4186, 20);
        delay(100);
        tone(buzzerPIN, 4186, 20);
        delay(50);
        noTone(buzzerPIN);
        buzzerFlag6 = false;
        buzzerFlag = true;
        }         
    }

   if (upState == HIGH) {                                       // turn up                                         
    digitalWrite(upoPin, HIGH);
    delay(5);
    digitalWrite(dwoPin, HIGH);
    delay(5);
    digitalWrite(upoPin, LOW);
    delay(5);
    digitalWrite(dwoPin, LOW);
    //tone(buzzerPIN, 4186, 20);
    delay(10);
    //noTone(buzzerPIN);
        display.fillTriangle(114,25,117,21,120,25, WHITE);
        display.fillTriangle(114,17,117,13,120,17, WHITE);
        display.fillTriangle(114,9,117,5,120,9, WHITE);
        display.fillTriangle(7,25,10,21,13,25, WHITE);
        display.fillTriangle(7,17,10,13,13,17, WHITE);
        display.fillTriangle(7,9,10,5,13,9, WHITE);
        display.display();
    } else { 
        display.fillTriangle(114,25,117,21,120,25, BLACK);
        display.fillTriangle(114,17,117,13,120,17, BLACK);
        display.fillTriangle(114,9,117,5,120,9, BLACK);
        display.fillTriangle(7,25,10,21,13,25, BLACK);
        display.fillTriangle(7,17,10,13,13,17, BLACK);
        display.fillTriangle(7,9,10,5,13,9, BLACK);
        display.display();
        }
 
  
  if (dwState == HIGH) {                                        // turn down
    digitalWrite(dwoPin, HIGH);
    delay(5);
    digitalWrite(upoPin, HIGH);
    delay(5);
    digitalWrite(dwoPin, LOW);
    delay(5);
    digitalWrite(upoPin, LOW);  
    //tone(buzzerPIN, 4186, 20);
    delay(10);
    //noTone(buzzerPIN);                            
        display.fillTriangle(114,21,117,25,120,21, WHITE);
        display.fillTriangle(114,13,117,17,120,13, WHITE);
        display.fillTriangle(114,5,117,9,120,5, WHITE);
        display.fillTriangle(7,21,10,25,13,21, WHITE);
        display.fillTriangle(7,13,10,17,13,13, WHITE);
        display.fillTriangle(7,5,10,9,13,5, WHITE);
        display.display();
 } else {
        display.fillTriangle(114,21,117,25,120,21, BLACK);
        display.fillTriangle(114,13,117,17,120,13, BLACK);
        display.fillTriangle(114,5,117,9,120,5, BLACK);
        display.fillTriangle(7,21,10,25,13,21, BLACK);
        display.fillTriangle(7,13,10,17,13,13, BLACK);
        display.fillTriangle(7,5,10,9,13,5, BLACK);
        display.display();
 }

 lock:                                                                    // loop here when locking
  upState = analogRead(A7) < 100 ? 0 : 1;
  dwState = analogRead(A6) < 100 ? 0 : 1;

if (state == 0 && upState == HIGH && dwState == HIGH) {                   // simulated 2 button
    digitalWrite(o1Pin, LOW);
    digitalWrite(o2Pin, LOW);
    digitalWrite(o3Pin, LOW);
    digitalWrite(o4Pin, LOW);
    digitalWrite(o5Pin, LOW);
    digitalWrite(o6Pin, LOW);
    digitalWrite(upoPin, LOW);
    digitalWrite(dwoPin, LOW);
    s = 0;
    m = 0;
    state = 1;
    Loadstate=!Loadstate;
  }
  if (state == 1 && upState == LOW && dwState == LOW) {                   
    state = 0;
  // Welcome display 
  display.fillScreen(BLACK);
  display.drawLine(5,27,122,27, WHITE);
  display.drawLine(122,0,122,27, WHITE);
  display.drawLine(122,27,127,32, WHITE);  //
  display.drawLine(45,32,40,27, WHITE);    //
  display.drawLine(85,27,80,32, WHITE);    //
  display.drawLine(5,27,0,32, WHITE); 
  display.drawLine(5,0,5,27, WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,8);
  display.println("Ready to select");
  }
   if (Loadstate==HIGH){
     //clock
    display.clearDisplay();
    display.setCursor(0, 0);
 s=s+1;
 if(s==60){
  s=0;
  m=m+1;
 }
 if(m==60)
 {
  m=0;
  h=h+1;    
 }
 if(h==1)
 {
  h=1;
 }
 if(h==2)
 {
  digitalWrite(stbyPin, HIGH);
 }
  s = s + 0.50;
  display.fillRoundRect(5,12,50,18,1, WHITE);
  display.setTextSize(2);
  display.setTextColor(BLACK);
  display.setCursor(7,14);
  display.println("LOCK!");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(5,0);
  display.println("SW:v1.2.1");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(68,0);
  display.println("HW:v1.4.0");
  delay(970);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(65, 14);
  display.print(m);
  display.print(":");
  display.print(s);
  display.display();
  //endclock
    if (buzzerFlag9 == false ) {
        tone(buzzerPIN, 3520, 60);
        delay(200);
        noTone(buzzerPIN);
        display.clearDisplay();
    buzzerFlag8 = false;
    buzzerFlag9 = true;
    }
    goto lock;
   } else {
    if (buzzerFlag8 == false ) {
    buzzerFlag9 = false;
    buzzerFlag8 = true;
    display.clearDisplay();
    display.display();
    digitalWrite(stbyPin, LOW);
        tone(buzzerPIN, 4186, 20);
        delay(100);
        tone(buzzerPIN, 4186, 20);
        delay(50);
        noTone(buzzerPIN);
    delay(1000);
    }        
   }
}//endloop
