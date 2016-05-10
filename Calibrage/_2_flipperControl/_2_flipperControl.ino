#include <Wire.h> 
#include <SPI.h> 
#include <EEPROM.h> 

#define PDB_COMMAND_WRITE 1 
#define BANK_ONE 1 
#define BANK_ZERO 0 
#define THUMPER_FIRE_DURATION 10 
#define pinMOSI 11

const int buttonLeftPin = 2;
const int buttonRightPin = 3;

const int ledLeftPin =  13;
const int ledRightPin =  12;

unsigned char dataSolenoid = 0;
unsigned char j = 0;
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

  pinMode(ledLeftPin, OUTPUT);
  pinMode(ledRightPin, OUTPUT);  

  pinMode(buttonLeftPin, INPUT);  
  pinMode(buttonRightPin, INPUT);   

 Serial.print("[HOLD ON] Debut de la sequence... dans 5s\n");
 SolenoidOff(0);
 SolenoidOff(1);
 delay(5000);
}

void loop() {
  buttonLeftState = digitalRead(buttonLeftPin);
  buttonRightState = digitalRead(buttonRightPin);

  if (buttonLeftState == HIGH || buttonRightState == HIGH) {     
    // turn LED on:    
    //digitalWrite(ledPin, HIGH);
    if(buttonLeftState != buttonLeftOldState || buttonRightState != buttonRightOldState){  
      
      if(buttonLeftState == HIGH){
        Serial.print("BOUTON LEFT ON\n");
        SolenoidOn(0);
      }
      if(buttonRightState == HIGH){
        Serial.print("BOUTON RIGHT ON\n");
        SolenoidOn(1);
      }
      delay(20);
    }else{
      if(buttonLeftState == HIGH) SolenoidOn(0);
      if(buttonRightState == HIGH) SolenoidOn(1);
      delay(3);
      if(buttonLeftState == HIGH) SolenoidOff(0);
      if(buttonRightState == HIGH) SolenoidOff(1);
      delay(10);
    }
  } 
  
  //digitalWrite(ledPin, LOW);
  if(buttonLeftState == LOW && buttonLeftState != buttonLeftOldState){  
    Serial.print("BOUTON LEFT OFF\n");
  }
  if(buttonRightState == LOW && buttonRightState != buttonRightOldState){  
    Serial.print("BOUTON RIGHT OFF\n");
  }
  
  buttonLeftOldState = buttonLeftState;
  buttonRightOldState = buttonRightState;
 
} // loop

void SolenoidOn(byte solenoidNumber)
{
 dataSolenoid |= 1 << solenoidNumber; // set solenoid bit to one

 sendPDBCommand(board, PDB_COMMAND_WRITE, BANK_ZERO, dataSolenoid);

 //#if (DIAGNOSTIC_ENABLED == 1)
   //Serial.print("Solenoid On  = ");
   //Serial.print(solenoidNumber);
   //Serial.print("     ");
   //PrintBinary(dataSolenoid, 8);    
   //Serial.print("\r\n");
 //#endif

 return;
} // SolenoidOn

void SolenoidOff(byte solenoidNumber)
{ 
 dataSolenoid &= ~(1 << solenoidNumber); // set solenoid bit to zero

 sendPDBCommand(board, PDB_COMMAND_WRITE, 0, dataSolenoid);

 //#if (DIAGNOSTIC_ENABLED == 1)
   //Serial.print("Solenoid Off = ");
   //Serial.print(solenoidNumber);
   //Serial.print("     ");
   //PrintBinary(dataSolenoid, 8);
   //Serial.print("\r\n");

 //#endif

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
} // PrintBinary
