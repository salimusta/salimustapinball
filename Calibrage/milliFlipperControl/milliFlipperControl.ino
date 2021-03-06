#include <Wire.h> 
#include <SPI.h> 
#include <EEPROM.h> 

#define PDB_COMMAND_WRITE 1 
#define BANK_ONE 1 
#define BANK_ZERO 0 
#define pinMOSI 11
#define DEBUG false

const int buttonLeftPin = 2;
const int buttonRightPin = 3;

unsigned char dataSolenoid = 0;
unsigned char dataSolenoidOld = 99;
byte board = 0;

int buttonLeftState = 0;
int buttonRightState = 0;
int buttonLeftOldState = 0;
int buttonRightOldState = 0;

void setup() {
 Serial.begin(9600); 

 SPI.begin(); 
 SPI.setBitOrder(MSBFIRST); 
 SPI.setClockDivider(SPI_CLOCK_DIV2);  // Need 8 MHz.  So use DIV2 on a 16 MHz board. 

 pinMode(buttonLeftPin, INPUT);  
 pinMode(buttonRightPin, INPUT);   

 Serial.print("[HOLD ON] Debut de la sequence... dans 5s\n");
 SolenoidStates(0, 0);
 delay(5000);
 Serial.print("STARTED !\n");
}

const int POWER_TIME_LEFT_MS =  70;
const int POWER_TIME_RIGHT_MS =  70;
const int HOLDON_PERIOD_MS =  30;
const int HOLDON_DURATION_MS =  4;

int leftFlipper_startTime = 0;
int rightFlipper_startTime = 0;

int leftFlipper_Time = 0;
int rightFlipper_Time = 0;

unsigned long time;
unsigned long old_time = 0;

void loop() {
  time = millis();
  
  buttonLeftState = digitalRead(buttonLeftPin);
  buttonRightState = digitalRead(buttonRightPin);

  int leftSolenoidState = 0;
  int rightSolenoidState = 0;

  if(buttonLeftState != buttonLeftOldState && buttonLeftState == HIGH){
    leftFlipper_startTime = time;
    Serial.print("LEFT ON\n");
  }
  if(buttonRightState != buttonRightOldState && buttonRightState == HIGH){
    rightFlipper_startTime = time;
    Serial.print("RIGHT ON\n");
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
  
  SolenoidStates(leftSolenoidState, rightSolenoidState);
  
  buttonLeftOldState = buttonLeftState;
  buttonRightOldState = buttonRightState;
 
 old_time = time;
} // loop

//0 is left, 1 i right
void SolenoidStates(byte solenoid0, byte solenoid1){
  
  if(solenoid0 == 1) dataSolenoid |= 1;
  else dataSolenoid &= ~1;
  
  if(solenoid1 == 1) dataSolenoid |= 1 << 1;
  else dataSolenoid &= ~(1 << 1);
  
  if(dataSolenoid != dataSolenoidOld){
    sendPDBCommand(board, PDB_COMMAND_WRITE, BANK_ZERO, dataSolenoid);
    //PrintBinary(dataSolenoid, 8);
  }
  dataSolenoidOld = dataSolenoid;
}

void SolenoidOn(byte solenoidNumber)
{
 dataSolenoid |= 1 << solenoidNumber; // set solenoid bit to one

 sendPDBCommand(board, PDB_COMMAND_WRITE, BANK_ZERO, dataSolenoid);

 if (DEBUG){
   Serial.print("Solenoid On  = ");
   Serial.print(solenoidNumber);
   Serial.print("     ");
   PrintBinary(dataSolenoid, 8);    
   Serial.print("\r\n");
 }
 return;
}

void SolenoidOff(byte solenoidNumber)
{ 
 dataSolenoid &= ~(1 << solenoidNumber); // set solenoid bit to zero

 sendPDBCommand(board, PDB_COMMAND_WRITE, 0, dataSolenoid);

 if (DEBUG){
   Serial.print("Solenoid Off = ");
   Serial.print(solenoidNumber);
   Serial.print("     ");
   PrintBinary(dataSolenoid, 8);
   Serial.print("\r\n");

}

 return;
} // SolenoidOff

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

void PrintBinary(int v, int num_places)
{
   int mask=0, n;

   for (n=1; n<=num_places; n++)
   {
       mask = (mask << 1) | 0x0001;
   }
   v = v & mask;  // truncate v to specified number of places

   while(num_places)
   {

       if (v & (0x0001 << num_places-1))
       {
            Serial.print("1");
       }
       else
       {
            Serial.print("0");
       }

       --num_places;
       if(((num_places%4) == 0) && (num_places != 0))
       {
           Serial.print("_");
       }
   }
   Serial.print("\n");
} // PrintBinary
