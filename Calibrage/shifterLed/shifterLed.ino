//**************************************************************//
//  Name    : shiftOutCode, Hello World                                
//  Author  : Carlyn Maw,Tom Igoe, David A. Mellis 
//  Date    : 25 Oct, 2006    
//  Modified: 23 Mar 2010                                 
//  Version : 2.0                                             
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255                           
//****************************************************************

int latchPinA = 13;
int latchPinB = 12;
int latchPinC = 11;
int latchPinD = 10;
int latchPinE = 9;
int latchPinF = 8;
int latchPinG = 7;
int latchPinH = 6;
int latchPinI = 5;

int dataPin = 2;
int clockPin = 3;



void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPinA, OUTPUT);
  pinMode(latchPinB, OUTPUT);
  pinMode(latchPinC, OUTPUT);
  pinMode(latchPinD, OUTPUT);
  pinMode(latchPinE, OUTPUT);
  pinMode(latchPinF, OUTPUT);
  pinMode(latchPinG, OUTPUT);
  pinMode(latchPinH, OUTPUT);
  pinMode(latchPinI, OUTPUT);
  
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

byte LeftRedAnim = 1;
byte LeftGreenAnim = 1;
byte MiddleYellowAnim = 0b01010;
byte RightRedAnim = 1;
byte RightGreenAnim = 1;
byte ModesAnim = 1;

byte LauncherAnim = 1;
byte LooseAnim = 0b111;

byte FlashAnim = 0b11111111;

byte Pletter = 1;
byte Sletter = 1;
byte Iletter = 1;
byte Tletter = 1;

byte KO1Anim = 1;

byte Gate1Light = 1;
byte Gate2Light = 1;
byte Gate3Light = 1;

int time = 0;

void loop() {
    time++;
    
    byte dataToShifterA = (LeftGreenAnim & 0b00011111) | (Pletter << 5);
    digitalWrite(latchPinA, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, dataToShifterA);  
    digitalWrite(latchPinA, HIGH);
    
    byte dataToShifterB = (LeftRedAnim & 0b00011111) | (Sletter << 5);
    digitalWrite(latchPinB, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, dataToShifterB);  
    digitalWrite(latchPinB, HIGH);
    
    digitalWrite(latchPinC, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, MiddleYellowAnim);  
    digitalWrite(latchPinC, HIGH);
    
    byte dataToShifterD = (RightRedAnim & 0b00011111) | (Iletter << 5);
    digitalWrite(latchPinD, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, dataToShifterD);  
    digitalWrite(latchPinD, HIGH);
    
    byte dataToShifterE = (RightGreenAnim & 0b00011111) | (Gate1Light << 5) | (Gate2Light << 6) | (Gate3Light << 7);
    digitalWrite(latchPinE, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, dataToShifterE);  
    digitalWrite(latchPinE, HIGH);
    
    digitalWrite(latchPinF, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, ModesAnim);  
    digitalWrite(latchPinF, HIGH);
    
    byte dataToShifterG = (LauncherAnim & 0b00011111) | (LooseAnim << 5);
    digitalWrite(latchPinG, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, dataToShifterG);  
    digitalWrite(latchPinG, HIGH);
    
    digitalWrite(latchPinH, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, FlashAnim);  
    digitalWrite(latchPinH, HIGH);
    
    byte dataToShifterI = (KO1Anim & 0b00011111) | (Tletter << 5);
    digitalWrite(latchPinI, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, dataToShifterI);  
    digitalWrite(latchPinI, HIGH);
    
    delay(100);
    
    LeftGreenAnim = LeftGreenAnim << 1;
    if(LeftGreenAnim == 0) LeftGreenAnim = 1;
    
    LeftRedAnim = LeftRedAnim << 1;
    if(LeftRedAnim == 0) LeftRedAnim = 1;
    
    //MiddleYellowAnim = MiddleYellowAnim << 1;
    //if(MiddleYellowAnim == 0) MiddleYellowAnim = 1;
    if(time%2 == 0 )MiddleYellowAnim = ~MiddleYellowAnim;
    

    if(time%1 == 0 ) LooseAnim = ~LooseAnim;
    
    RightRedAnim = RightRedAnim << 1;
    if(RightRedAnim == 0) RightRedAnim = 1;
    
    RightGreenAnim = RightGreenAnim << 1;
    if(RightGreenAnim == 0) RightGreenAnim = 1;
    
    ModesAnim = ModesAnim << 1;
    if(ModesAnim == 0) ModesAnim = 1;
    
    LauncherAnim = LauncherAnim << 1;
    if(LauncherAnim == 0) LauncherAnim = 1;
    
    //FlashAnim = FlashAnim << 1;
    //if(FlashAnim == 0) FlashAnim = 1;
    if(time%1 == 0 )FlashAnim = ~FlashAnim;
    
    KO1Anim = KO1Anim << 1;
    if(KO1Anim == 0) KO1Anim = 1;
}

