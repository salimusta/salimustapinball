#include <Wire.h>

const int buttonPin = 1;
const int ledPin =  12;

int buttonState = 0;
int buttonOldState = 0;

int nb = 0;

void setup() {
  pinMode(ledPin, OUTPUT); 

  pinMode(buttonPin, INPUT);

  Wire.begin(); // Start I2C Bus as Master
}

void loop(){
  //digitalWrite(ledLeftPin, HIGH); 
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {       
    digitalWrite(ledPin, HIGH);  
  } 
  else {
    digitalWrite(ledPin, LOW); 
  }
  
  if(buttonOldState != buttonState){
    if (buttonState == HIGH) {
     nb++; 
    }
    
    if(nb > 2) nb = 0;
    
    Wire.beginTransmission(nb + 9); // transmit to device #9
    Wire.write(buttonState);
    Wire.endTransmission();    // stop transmitting
    
    
  }
 buttonOldState = buttonState;
}
