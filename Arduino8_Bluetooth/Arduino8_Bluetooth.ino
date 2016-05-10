#include <SoftwareSerial.h>// import the serial library
#include <Wire.h>

SoftwareSerial Genotronex(10, 11); // RX, TX
int ledpin1=13; // led on D13 will show blink on / off
int ledpin2=12;
int BluetoothData; // the data given from Computer
byte flippersState = 0;

void setup() {
  // put your setup code here, to run once:
  Genotronex.begin(9600);
  Genotronex.println("Bienvenue Bro");
  pinMode(ledpin1,OUTPUT);
  pinMode(ledpin2,OUTPUT);
  
  Wire.begin(8);
  //Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  
  //Serial.begin(9600);
  
}
/*
void receiveEvent(int howMany) {

  for(int x=0; x<howMany;x++){
    byte data = Wire.read();
    
  }
  
}
*/

void requestEvent()
{
  byte response = 0;
  Wire.write(flippersState); 
}

void loop() {
  // put your main code here, to run repeatedly:
   if (Genotronex.available()){
      BluetoothData = Genotronex.read() - 48;
      //Serial.print(BluetoothData); Serial.print("\n");
      flippersState = BluetoothData;
      if(BluetoothData & 0b01) digitalWrite(ledpin1,1);
      else digitalWrite(ledpin1,0);
      
      if((BluetoothData & 0b10) >> 1) digitalWrite(ledpin2,1);
      else digitalWrite(ledpin2,0);
      
    }
    delay(50);// prepare for next data ...
}
