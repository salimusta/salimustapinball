#include <Wire.h>

const int ledPin =  12;

int receivedButtonState = 0;

void setup() {
  pinMode(ledPin, OUTPUT); 
  
  Wire.begin(9);                // Start I2C Bus as a Slave (Device Number 9)
  Wire.onReceive(receiveEvent); // register event

}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (receivedButtonState == HIGH) {       
    digitalWrite(ledPin, HIGH);  
  } 
  else {
    digitalWrite(ledPin, LOW); 
  }

}

void receiveEvent(int howMany) {
  receivedButtonState = Wire.read();    // receive byte as an integer
}
