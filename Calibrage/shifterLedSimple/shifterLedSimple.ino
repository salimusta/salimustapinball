//**************************************************************//
//  Name    : shiftOutCode, Hello World                                
//  Author  : Carlyn Maw,Tom Igoe, David A. Mellis 
//  Date    : 25 Oct, 2006    
//  Modified: 23 Mar 2010                                 
//  Version : 2.0                                             
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255                           
//****************************************************************

int latchPinM = 13;
int latchPinN = 12;

int dataPin = 2;
int clockPin = 3;



void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPinM, OUTPUT);
  pinMode(latchPinN, OUTPUT);
  
  
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

int time = 0;

byte RampAnim = 1;
byte RampGateAnim = 1;

void loop() {
    time++;
    
    byte dataToShifterM = RampAnim;
    digitalWrite(latchPinM, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, dataToShifterM);  
    digitalWrite(latchPinM, HIGH);
    
    byte dataToShifterN = RampGateAnim;
    digitalWrite(latchPinN, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, dataToShifterN);  
    digitalWrite(latchPinN, HIGH);
    
    delay(60);
    
    if(time%1 == 0){
      RampAnim = RampAnim << 1;
      if(RampAnim == 0) RampAnim = 1;
    }
    
    if(time%1 == 0){
      RampGateAnim = RampGateAnim << 1;
      if(RampGateAnim == 0) RampGateAnim = 1;
    }
    
}

