const int buttonLeftPin = 2;
const int buttonRightPin = 3;
const int ledLeftPin =  13;
const int ledRightPin =  12;

int buttonLeftState = 0;
int buttonRightState = 0;

void setup() {
  pinMode(ledLeftPin, OUTPUT); 
  pinMode(ledRightPin, OUTPUT);   

  pinMode(buttonLeftPin, INPUT);  
  pinMode(buttonRightPin, INPUT);

digitalWrite(ledRightPin, HIGH);    
}

void loop(){
  //digitalWrite(ledLeftPin, HIGH); 
  buttonLeftState = digitalRead(buttonLeftPin);
  buttonRightState = digitalRead(buttonRightPin);

  if (buttonLeftState == HIGH) {       
    digitalWrite(ledLeftPin, HIGH);  
  } 
  else {
    digitalWrite(ledLeftPin, LOW); 
  }
  
  if (buttonRightState == HIGH) {       
    digitalWrite(ledRightPin, HIGH);  
  } 
  else {
    digitalWrite(ledRightPin, LOW); 
  }
}
