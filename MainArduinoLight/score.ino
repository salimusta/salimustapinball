
void TestScore(){
  delay(3000);
  printLine("7-DIGIT Test", "Sending test...");
  DisableIncrementalScore();
  score = 12345;
  DisplayScore();
  delay(3000);
  //lcd.setCursor(0, 1); lcd.print("Sending 88888...");
  score = 88888; DisplayScore(); delay(3000);
  
  //lcd.setCursor(0, 1); lcd.print("Blinking 11223..");
  score = 11223;
  DisplayScore(); BlinkScore(); delay(5000);
  
  //lcd.setCursor(0, 1); lcd.print("Incremental");
  EnableIncrementalScore();
  score = 1234; DisplayScore(); delay(1000);
  score = 1400; DisplayScore(); delay(5000);
  
  DisableIncrementalScore();
  score = 2; DisplayScore(); delay(200);
  BlinkScore(); delay(3000);
  score = 123; DisplayScore(); delay(200);
  BlinkScore(); delay(3000);
  score = 12345; DisplayScore(); delay(200);
  BlinkScore(); delay(3000);
  
  score = 0; DisplayScore();
}

void BlinkScore(){
  Wire.beginTransmission(1);
  Wire.write(1); Wire.write(0); Wire.write(0); Wire.write(0);
  Wire.endTransmission();
}
void EnableIncrementalScore(){
  Wire.beginTransmission(1);
  Wire.write(4); Wire.write(0); Wire.write(0); Wire.write(0);
  Wire.endTransmission();
}
void DisableIncrementalScore(){
  Wire.beginTransmission(1);
  Wire.write(2); Wire.write(0); Wire.write(0); Wire.write(0);
  Wire.endTransmission();
}
void DisplayScore(){
  byte byte0 = score & 0xFF;
  byte byte1 = (score & 0xFF00)>>8;
  byte byte2 = (score & 0xFF0000)>>16;
  byte byte3 = (score & 0xFF000000)>>24;
  
  Wire.beginTransmission(1);
  Wire.write(byte3); Wire.write(byte2); Wire.write(byte1); Wire.write(byte0);
  Wire.endTransmission();
}
