#include <Wire.h> 
#include <SPI.h> 
#include <EEPROM.h> 

#define PDB_COMMAND_WRITE 1 
#define BANK_ONE 1 
#define BANK_ZERO 0 
#define THUMPER_FIRE_DURATION 10 
#define pinMOSI 11

const int buttonPin = 2;
const int ledPin =  13;

unsigned char dataSolenoid = 0;
unsigned char j = 0;
byte board = 0;
int loopCounter = 0;

int buttonState = 0;
int buttonOldState = 0;

void setup() {

 // initialize serial monitor: 
 Serial.begin(9600); 

 // put your setup code here, to run once:
 // this serial for solenoid driver 
 SPI.begin(); 
 SPI.setBitOrder(MSBFIRST); 
 SPI.setClockDivider(SPI_CLOCK_DIV2);  // Need 8 MHz.  So use DIV2 on a 16 MHz board. 

 ++loopCounter;
 
 // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);  

 Serial.print("[HOLD ON] Debut de la sequence... dans 5s\n");
 SolenoidOff(0);
 SolenoidOff(1);
 delay(5000);
}

void loop() {
   buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);
    if(buttonState != buttonOldState){  
      Serial.print("BOUTON ON\n");
      SolenoidOn(0);
      delay(20);
    }else{
      SolenoidOn(0);
      delay(3);
      SolenoidOff(0);
      delay(10);
    }
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
    if(buttonState != buttonOldState){  
      Serial.print("BOUTON OFF\n");
    } 
  }
  
  buttonOldState = buttonState;
 
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
