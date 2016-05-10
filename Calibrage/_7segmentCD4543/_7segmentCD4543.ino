/*
Ce programme pilote 7 afficheurs 7 segments a l aide d un CD4543
*/

void setup() {
  Serial.begin(9600);
  
  // put your setup code here, to run once:
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  
}


void loop() {
  
  
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  digitalWrite(9, HIGH);
  delayMicroseconds(1000);
  
}
