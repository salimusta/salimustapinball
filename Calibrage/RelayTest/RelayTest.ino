void setup() {
  // put your setup code here, to run once:
  
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(9, HIGH);
  
  delay(2000);
  
  
  digitalWrite(12, LOW);
  delay(2000);
  digitalWrite(12, HIGH);
  delay(1000);
  
  digitalWrite(11, LOW);
  delay(2000);
  digitalWrite(11, HIGH);
  delay(1000);
  
  digitalWrite(10, LOW);
  delay(2000);
  digitalWrite(10, HIGH);
  delay(1000);
  
  
  digitalWrite(9, LOW);
  delay(2000);
  digitalWrite(9, HIGH);
  delay(1000);
  
  
}
