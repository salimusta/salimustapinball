#include <Wire.h> 
#include <SPI.h> 

#define PDB_COMMAND_WRITE 1 
#define BANK_ONE 1 
#define BANK_ZERO 0 
#define pinMOSI 11
#define DEBUG false

//PIN Connections
const int buttonLeftPin = 2;
const int buttonRightPin = 3;
const int BASW1Pin = 4;
const int BASW2Pin = 5;
const int BASW3Pin = 6;
const int RKickerPin = 8;
const int LKickerPin = 7;

const int RampPin = 9;

//Data buffers
unsigned char dataSolenoid = 0;
unsigned char dataSolenoidOld = 99;
unsigned char dataSolenoidBankB = 0;
unsigned char dataSolenoidBankBOld = 99;
byte board = 0;

//Switches State
int buttonLeftState = 0;
int buttonRightState = 0;
int buttonLeftOldState = 0;
int buttonRightOldState = 0;

int btButtonLeftState = 0;
int btButtonRightState = 0;

int BASW1State = 0;
int BASW2State = 0;
int BASW3State = 0;
int BASW1OldState = 0;
int BASW2OldState = 0;
int BASW3OldState = 0;

int RKickerState = 0;
int LKickerState = 0;
int RKickerOldState = 0;
int LKickerOldState = 0;

int RampState = 0;
int RampOldState = 0;

int Bumper1_Duration = 9999;
int Bumper2_Duration = 9999;
int Bumper3_Duration = 9999;

int timeSinceFiredBumper1 = 0;
int timeSinceFiredBumper2 = 0;
int timeSinceFiredBumper3 = 0;

int RightKicker_Duration = 9999;
int LeftKicker_Duration = 9999;

int Kickout1_Duration = 9999;
int Kickout2_Duration = 9999;

int Shooter_Duration = 9999;

bool KICKER_LEFT = 0;
bool KICKER_RIGHT = 0;

bool rampABallRequested = false;
bool testRequested = false;
bool flippersEnabled = false;
bool kickersEnabled = true;
bool kickout1Requested = false;
bool kickout2Requested = false;
bool shooterRequested = false;

unsigned long timeRampABall = 0;


const int POWER_TIME_LEFT_MS =  170;
const int POWER_TIME_RIGHT_MS =  170;
const int HOLDON_PERIOD_MS =  16;
const int HOLDON_DURATION_MS =  5;

const int BUMPER1_FIRE_DURATION = 130;
const int BUMPER2_FIRE_DURATION = 200;
const int BUMPER3_FIRE_DURATION = 150;

const int KICKER_FIRE_DURATION = 1000;
int KICKOUT1_FIRE_DURATION = 100;
int KICKOUT2_FIRE_DURATION = 100;
int SHOOTER_FIRE_DURATION = 450;

short decalage = 130;
short decalage2 = 110;
short decalage3 = 130;

long randomTime = 0;

void setup() {
 Serial.begin(9600); 

 SPI.begin(); 
 SPI.setBitOrder(MSBFIRST); 
 SPI.setClockDivider(SPI_CLOCK_DIV2);  // Need 8 MHz.  So use DIV2 on a 16 MHz board. 

 pinMode(buttonLeftPin, INPUT);  
 pinMode(buttonRightPin, INPUT);
 pinMode(BASW1Pin, INPUT);
 pinMode(BASW2Pin, INPUT);
 pinMode(BASW3Pin, INPUT);
 pinMode(RKickerPin, INPUT);
 pinMode(LKickerPin, INPUT);
 pinMode(RampPin, INPUT);
 
 Wire.begin(2);
 Wire.onReceive(receiveEvent);
 Wire.onRequest(requestEvent);

 SolenoidStatesBankA(0, 0, 0, 0, 0);
 SolenoidStatesBankB(0, 0, 0, 0, 0);
 SolenoidOff(2);
 SolenoidOff(3);

}


void receiveEvent(int howMany) {
  //10 for RampABall function
  //20 for test solenoids
  //30 to disable flippers
  //40 to enable flippers
  //50 To fire Kickout 1
  //60 to Fire Kickout 2
  //80 to disable side kickers
  //90 to Shoot a Ball
  for(int x=0; x<howMany;x++){
    byte data = Wire.read();
    
    if(data == 10){
      rampABallRequested = true;
      timeRampABall = millis();
      //Serial.print("RAMP A BALL\n");
    }else if(data == 20){
      testRequested = true;
    }else if(data == 30){
      //Serial.print("FLIPPERS DISABLED\n");
      flippersEnabled = false;
    }else if(data == 40){
      //Serial.print("FLIPPERS ENABLED\n");
      flippersEnabled = true;
      kickersEnabled = true;
    }else if(data == 50){
      //Serial.print("KICKOUT 1\n");
      kickout1Requested = true;
      Kickout1_Duration = 0;
      randomTime = random(30);
      KICKOUT1_FIRE_DURATION = 70 + randomTime;
    }else if(data == 60){
      //Serial.print("KICKOUT 2\n");
      kickout2Requested = true;
      Kickout2_Duration = 0;
      randomTime = random(30);
      KICKOUT2_FIRE_DURATION = 100 + randomTime;
    }else if(data == 80){
      kickersEnabled = false;
      
    }else if(data == 90){
      rampABallRequested = true;
      timeRampABall = millis();
      shooterRequested = true;
      Shooter_Duration = 0;
    }else{
      //custom Data
      
      btButtonLeftState = (data & 0x2) >> 1;
      btButtonRightState = data & 0x1;
    }
  }
}

void requestEvent()
{
  //write a byte like 
  //order starting from bit 0: KickerLeft, KickerRight, LeftFLipper, RightFLipper
  byte response = buttonRightState;
  response = (response << 1) | buttonLeftState;
  response = (response << 1) | KICKER_RIGHT;
  response = (response << 1) | KICKER_LEFT;
  
  Wire.write(response); 
}


int leftFlipper_startTime = 0;
int rightFlipper_startTime = 0;
int BASW1_startTime = 0;
int BASW2_startTime = 0;
int BASW3_startTime = 0;
int RKickerSW_startTime = 0;
int LKickerSW_startTime = 0;

int leftFlipper_Time = 0;
int rightFlipper_Time = 0;


unsigned long time;
unsigned long old_time = 0;

void ReadBluetoothCommand() {

  bool btLeftButton, btRightButton;
  Wire.requestFrom(8, 1);
  while (Wire.available()) {
    char c = Wire.read(); // receive a byte as character
    
  }
  
}

void loop() {
  time = millis();
  
  buttonLeftState = digitalRead(buttonLeftPin);
  buttonRightState = digitalRead(buttonRightPin);
  BASW1State = digitalRead(BASW1Pin);
  BASW2State = digitalRead(BASW2Pin);
  BASW3State = digitalRead(BASW3Pin);
  RKickerState = digitalRead(RKickerPin);
  LKickerState = digitalRead(LKickerPin);
  RampState = digitalRead(RampPin);
  
  //Bluetooth
  if(btButtonLeftState == 1) buttonLeftState = HIGH;
  if(btButtonRightState == 1) buttonRightState = HIGH;

  int leftSolenoidState = 0;
  int rightSolenoidState = 0;
  int Bumper1_State = 0;
  int Bumper2_State = 0;
  int Bumper3_State = 0;
  int RightKicker_State = 0;
  int LeftKicker_State = 0;
  int Kickout1_State = 0;
  int Kickout2_State = 0;
  int Shooter_State = 0;
  
  bool Ramping = false;

  if(kickout1Requested){
    Kickout1_State = 1;
    Kickout1_Duration++;
    if(Kickout1_Duration > KICKOUT1_FIRE_DURATION){
      Kickout1_Duration = 999;
      kickout1Requested = false;
    }
  }
  if(kickout2Requested){
    //Serial.print("REQUESTED");
    Kickout2_State = 1;
    Kickout2_Duration++;
    if(Kickout2_Duration > KICKOUT2_FIRE_DURATION){
      Kickout2_Duration = 999;
      kickout2Requested = false;
    }
  }

  if(testRequested){
    //Serial.print("SEQUENCE DE TEST RECU\n");
    SolenoidStatesBankA(0, 0, 0, 0, 0);
    SolenoidStatesBankB(0, 0, 0, 0, 0);
    delay(2000);
    //Serial.print("LEFT FLIPPER\n");
    //LEFT FLIPPER
    SolenoidStatesBankA(1, 0, 0, 0, 0);
    delay(200);
    SolenoidStatesBankA(0, 0, 0, 0, 0);
    delay(2000);
    //Serial.print("RIGHT FLIPPER\n");
    //RIGHT FLIPPER
    SolenoidStatesBankA(0, 1, 0, 0, 0);
    delay(200);
    SolenoidStatesBankA(0, 0, 0, 0, 0);
    delay(2000);
    //Serial.print("TRIEUR\n");
    //TRIEUR
    SolenoidOn(2);
    delay(300);
    SolenoidOff(2);
    delay(2000);
    //Serial.print("RAMP\n");
    //RAMP
    SolenoidOn(3);
    delay(50);
    SolenoidOff(3);
    delay(2000);
    
    //Serial.print("Bumper 1\n");
    //Bumper 1
    SolenoidStatesBankA(0, 0, 1, 0, 0);
    delay(100);
    SolenoidStatesBankA(0, 0, 0, 0, 0);
    delay(2000);
    
    //Serial.print("Bumper 2\n");
    //Bumper 2
    SolenoidStatesBankA(0, 0, 0, 1, 0);
    delay(100);
    SolenoidStatesBankA(0, 0, 0, 0, 0);
    delay(2000);
    
    //Serial.print("Bumper 3\n");
    //Bumper 3
    SolenoidStatesBankA(0, 0, 0, 0, 1);
    delay(100);
    SolenoidStatesBankA(0, 0, 0, 0, 0);
    delay(2000);
    
    //Serial.print("Kicker Left\n");
    //Kicker Left
    SolenoidStatesBankB(0, 1, 0, 0, 0);
    delay(200);
    SolenoidStatesBankB(0, 0, 0, 0, 0);
    delay(2000);
    
    //Serial.print("Kicker Right\n");
    //Kicker Right
    SolenoidStatesBankB(1, 0, 0, 0, 0);
    delay(200);
    SolenoidStatesBankB(0, 0, 0, 0, 0);
    delay(2000);
    
    //Serial.print("Kickout 1\n");
    //Kickout 1
    SolenoidStatesBankB(0, 0, 1, 0, 0);
    delay(50);
    SolenoidStatesBankB(0, 0, 0, 0, 0);
    delay(1000);
    
    //Serial.print("Kickout 1\n");
    //Kickout 1
    SolenoidStatesBankB(0, 0, 0, 1, 0);
    delay(50);
    SolenoidStatesBankB(0, 0, 0, 0, 0);
    delay(1000);
    
    //Shooter
    SolenoidStatesBankB(0, 0, 0, 0, 1);
    delay(50);
    SolenoidStatesBankB(0, 0, 0, 0, 0);
    delay(1000);
    
    //Serial.print("FIN DE SEQUENCE\n");
    testRequested = false;
  }
  
  //At any time, if RAMP = ON Ramp the ball
  if(!rampABallRequested && RampState == HIGH){
     rampABallRequested = true;
     timeRampABall = millis() + 500;
  }
  
  //Push the ball trough sequence, we shoot a need ball
  if(rampABallRequested){
    unsigned long timeSinceRequested = time - timeRampABall;
    //time to shoot = 21
    //End the sequence after 2173 ms (then shoot if needed)
    if(timeSinceRequested > 3000 && timeSinceRequested < 10000){
      rampABallRequested = false;
      Ramping = false;
      
    //Check if the ball fell down, refire again
    }else if(timeSinceRequested > 2500){
      Ramping = true;
      if(RampState == HIGH){
        timeRampABall = time - 500;
      }  
    
    //Cut the powering session Ramp off
    }else if(timeSinceRequested > 1027){
      SolenoidOff(3);
      Ramping = true;
    //Open Ramp
    }else if(timeSinceRequested > 1005){
      SolenoidOn(3);
      Ramping = true;
      
    //Close Trieur
    }else if(timeSinceRequested > 300){
      SolenoidOff(2);
      Ramping = true;
    //Open Trieur
    }else if(timeSinceRequested >= 0){
      SolenoidOn(2);
      Ramping = true;
    }
  }
  
  //Shooting sequence
  if(shooterRequested && !rampABallRequested){
    Shooter_Duration++;
    Shooter_State = 1;
    
    if(Shooter_Duration > SHOOTER_FIRE_DURATION ){
      Shooter_Duration = 9999;
      shooterRequested = false;
    }
  }
  
  //Ramp switch management
  if(RampState != RampOldState && RampState == HIGH){
    //Serial.print("RAMP ON\n"); 
  }else if(RampState != RampOldState && RampState == LOW){
    //Serial.print("RAMP OFF\n"); 
  }
  
  
  if(buttonLeftState != buttonLeftOldState && buttonLeftState == HIGH){
    //if(time - leftFlipper_startTime > 20){
      leftFlipper_startTime = time;
      //Serial.print("LEFT ON\n");
    //}
  }
  if(buttonRightState != buttonRightOldState && buttonRightState == HIGH){
    //if(time - rightFlipper_startTime > 20){
      rightFlipper_startTime = time;
      //Serial.print("RIGHT ON\n");
   // }
  }
  
  if(buttonLeftState == HIGH){
    leftFlipper_Time = time - leftFlipper_startTime;
    if(leftFlipper_Time < POWER_TIME_LEFT_MS) leftSolenoidState = 1;
    else{
      if( (leftFlipper_Time - POWER_TIME_LEFT_MS)%HOLDON_PERIOD_MS < HOLDON_DURATION_MS){
        leftSolenoidState = 1;
      }else leftSolenoidState = 0;
    }
  }else{
    leftFlipper_Time = 0;
  }
  
  if(buttonRightState == HIGH){
    rightFlipper_Time = time - rightFlipper_startTime;
    if(rightFlipper_Time < POWER_TIME_RIGHT_MS) rightSolenoidState = 1;
    else{
      if( (rightFlipper_Time - POWER_TIME_RIGHT_MS)%HOLDON_PERIOD_MS < HOLDON_DURATION_MS){
        rightSolenoidState = 1;
      }else rightSolenoidState = 0;
    }
  }else{
    rightFlipper_Time = 0;
  }
  
  //BUMPER ACTIVATION SWITHES
  if(BASW1State != BASW1OldState && BASW1State == HIGH){
    if(time - BASW1_startTime > 100){
      BASW1_startTime = time;
      Bumper1_Duration = 0;
      //Serial.print("BASW1 ON\n");
    }
  }
  if(BASW2State != BASW2OldState && BASW2State == HIGH){
    if(time - BASW2_startTime > 100){
      BASW2_startTime = time;
      Bumper2_Duration = 0;
      //Serial.print("BASW2 ON\n");
    }
  }
  if(BASW3State != BASW3OldState && BASW3State == HIGH){
    if(time - BASW3_startTime > 100){
      BASW3_startTime = time;
      Bumper3_Duration = 0;
      //Serial.print("BASW3 ON\n");
    }
  }
  
  //BUMPER FIRE ACTIVATION
  
  if(timeSinceFiredBumper1 > 1000 && Bumper1_Duration < BUMPER1_FIRE_DURATION + decalage){
    //Adding a little delay to let the ball enter the bumper
   if (Bumper1_Duration > decalage) Bumper1_State = 1;
   else Bumper1_State = 0;
   Bumper1_Duration++;
   if(Bumper1_Duration == BUMPER1_FIRE_DURATION + decalage) timeSinceFiredBumper1 = 0;
  }else{
   Bumper1_State = 0;
   Bumper1_Duration= 9999;
  }
  
  if(timeSinceFiredBumper2 > 1000 && Bumper2_Duration < BUMPER2_FIRE_DURATION + decalage2){
   if (Bumper2_Duration > decalage2) Bumper2_State = 1; 
   else Bumper2_State = 0;
   Bumper2_Duration++;
   if(Bumper2_Duration == BUMPER2_FIRE_DURATION + decalage2) timeSinceFiredBumper2 = 0;
  }else{
   Bumper2_State = 0;
   Bumper2_Duration= 9999;
  }
  
  if(timeSinceFiredBumper3 > 1000 && Bumper3_Duration < BUMPER3_FIRE_DURATION + decalage3){
   if (Bumper3_Duration > decalage3) Bumper3_State = 1;
   else Bumper3_State = 0;
   Bumper3_Duration++;
   if(Bumper3_Duration == BUMPER3_FIRE_DURATION + decalage3) timeSinceFiredBumper3 = 0;
  }else{
   Bumper3_State = 0;
   Bumper3_Duration= 9999;
  }
  
  if(timeSinceFiredBumper1 < 10000) timeSinceFiredBumper1++;
  if(timeSinceFiredBumper2 < 10000) timeSinceFiredBumper2++;
  if(timeSinceFiredBumper3 < 10000) timeSinceFiredBumper3++;
  
  //Kicker activation switches
  if(RKickerState != RKickerOldState && RKickerState == HIGH){
    if(time - RKickerSW_startTime > 1000){
      RKickerSW_startTime = time;
      RightKicker_Duration = 0;
      KICKER_RIGHT = true;
      //Serial.print("Right Kicker Activated ON\n");
    }
  }else if(RKickerState == LOW){
   KICKER_RIGHT = false; 
  }
  if(LKickerState != LKickerOldState && LKickerState == HIGH){
    if(time - LKickerSW_startTime > 1000){
      LKickerSW_startTime = time;
      LeftKicker_Duration = 0;
      KICKER_LEFT = true;
      //Serial.print("Left Kicker Activated ON\n");
    }
  }else if(LKickerState == LOW){
   KICKER_LEFT = false; 
  }
  
  //Kicker ACTIVATION
  if(RightKicker_Duration < KICKER_FIRE_DURATION && kickersEnabled){
   RightKicker_State = 1; 
   RightKicker_Duration++;
  }else{
   RightKicker_State = 0;
   RightKicker_Duration= 9999;
  }
  
  if(LeftKicker_Duration < KICKER_FIRE_DURATION && kickersEnabled){
   LeftKicker_State = 1; 
   LeftKicker_Duration++;
  }else{
   LeftKicker_State = 0;
   LeftKicker_Duration= 9999;
  }
  
  if(flippersEnabled){
    if(Ramping == false){
      SolenoidStatesBankA(leftSolenoidState, rightSolenoidState, Bumper1_State, Bumper2_State, Bumper3_State);
      SolenoidStatesBankB(RightKicker_State, LeftKicker_State, Kickout1_State, Kickout2_State, Shooter_State);
    }else{
      SolenoidStatesBankA(0, 0, 0, 0, 0);
      SolenoidStatesBankB(0, 0, Kickout1_State, Kickout2_State, Shooter_State);
    }
    
  }else {
    SolenoidStatesBankA(0, 0, 0, 0, 0);
    SolenoidStatesBankB(0, 0, Kickout1_State, Kickout2_State, Shooter_State);
  }
  
  buttonLeftOldState = buttonLeftState;
  buttonRightOldState = buttonRightState;
  BASW1OldState = BASW1State;
  BASW2OldState = BASW2State;
  BASW3OldState = BASW3State;
  RKickerOldState = RKickerState;
  LKickerOldState = LKickerState;
  RampOldState = RampState;
  
 old_time = time;
} // loop

//0 is left, 1 i right
void SolenoidStatesBankA(byte solenoid0, byte solenoid1, byte Bumper1_Solenoid, byte Bumper2_Solenoid, byte Bumper3_Solenoid){
  
  if(solenoid0 == 1) dataSolenoid |= 1;
  else dataSolenoid &= ~1;
  
  if(solenoid1 == 1) dataSolenoid |= 1 << 1;
  else dataSolenoid &= ~(1 << 1);
  
  if(Bumper1_Solenoid == 1) dataSolenoid |= 1 << 4;
  else dataSolenoid &= ~(1 << 4);
  
  if(Bumper2_Solenoid == 1) dataSolenoid |= 1 << 5;
  else dataSolenoid &= ~(1 << 5);
  
  if(Bumper3_Solenoid == 1) dataSolenoid |= 1 << 6;
  else dataSolenoid &= ~(1 << 6);
  
  if(dataSolenoid != dataSolenoidOld){
    sendPDBCommand(board, PDB_COMMAND_WRITE, BANK_ZERO, dataSolenoid);
    //PrintBinary(dataSolenoid, 8);
  }
  dataSolenoidOld = dataSolenoid;
}

void SolenoidStatesBankB(byte RightKicker, byte LeftKicker, byte Kickout1, byte Kickout2, byte Shooter){
  
  if(LeftKicker == 1) dataSolenoidBankB |= 1;
  else dataSolenoidBankB &= ~1;
  
  if(RightKicker == 1) dataSolenoidBankB |= 1 << 1;
  else dataSolenoidBankB &= ~(1 << 1);
  
  if(Kickout1 == 1) dataSolenoidBankB |= 1 << 2;
  else dataSolenoidBankB &= ~(1 << 2);
  
  if(Kickout2 == 1) dataSolenoidBankB |= 1 << 3;
  else dataSolenoidBankB &= ~(1 << 3);
  
  if(Shooter == 1) dataSolenoidBankB |= 1 << 4;
  else dataSolenoidBankB &= ~(1 << 4);
  
  if(dataSolenoidBankB != dataSolenoidBankBOld){
    sendPDBCommand(board, PDB_COMMAND_WRITE, BANK_ONE, dataSolenoidBankB);
    //PrintBinary(dataSolenoid, 8);
  }
  dataSolenoidBankBOld = dataSolenoidBankB;
}

void SolenoidOn(byte solenoidNumber)
{
 dataSolenoid |= 1 << solenoidNumber; // set solenoid bit to one
 sendPDBCommand(board, PDB_COMMAND_WRITE, BANK_ZERO, dataSolenoid);
}

void SolenoidOff(byte solenoidNumber)
{ 
 dataSolenoid &= ~(1 << solenoidNumber); // set solenoid bit to zero
 sendPDBCommand(board, PDB_COMMAND_WRITE, 0, dataSolenoid);
}

void sendPDBCommand(byte addr, byte command, byte bankAddr, byte data) 
{ 
 byte cmdWord[5]; 
 cmdWord[0] = addr; 
 cmdWord[1] = command; 
 cmdWord[2] = bankAddr; 
 cmdWord[3] = (data >> 4) & 0xF; 
 cmdWord[4] = data & 0xF; 

 // Turn off interrupts so the transfer doesn't get interrupted. 
 noInterrupts(); 
 // Hardcode transfers to minimize IDLEs between transfers. 
 // Using a for-loop adds 5 extra IDLEs between transfers.  
 SPI.transfer(cmdWord[0]); 
 SPI.transfer(cmdWord[1]); 
 SPI.transfer(cmdWord[2]); 
 SPI.transfer(cmdWord[3]); 
 SPI.transfer(cmdWord[4]); 
 // Re-enable interrupts 
 interrupts(); 
 //Serial.println("Transferred ");
 return; 
} // sendPDBCommand

