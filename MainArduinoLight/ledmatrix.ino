

void TestLedMatrix(){
  printLine("Led Matrix test", "On going...");
  DisplayScreen(SCREEN_SALIMUSTAPINBALL, PRIORITY_LOW); delay(2000); 
  DisplayScreen(SCREEN_FULL, PRIORITY_LOW); delay(2000);  
  DisplayScreen(SCREEN_GETREADY, PRIORITY_LOW); delay(2000);  
  DisplayScreen(SCREEN_MULTIBALL, PRIORITY_LOW); delay(2000);
  DisplayScreen(SCREEN_GAMEOVER, PRIORITY_LOW); delay(2000);
}

void DisplayScreen(byte screen, byte priority){
  Wire.beginTransmission(4);
  Wire.write(screen); Wire.write(nbBall); Wire.write(priority);
  Wire.endTransmission();
}

void SendScreenData(byte type, byte data){
  Wire.beginTransmission(4);
  Wire.write(type);
  Wire.write(data);
  Wire.endTransmission();
}
byte ReadBallGameStatus() {
  byte command = 0;
  Wire.requestFrom(4, 1);
  while (Wire.available()) {
    command = Wire.read();
  }
  return command;
}

void ReadPlayerName(char buf[11]) {
  Wire.requestFrom(4, 11);
  byte index = 0;
  while (Wire.available()) {
    byte data = Wire.read();
    buf[index] = data;
    index++;
  }
}

byte ReadPlayerNumber(){
  Wire.requestFrom(4, 1);
  byte nbPlayer = 0;
  while (Wire.available()) {
    nbPlayer = Wire.read();
  }
  return nbPlayer;
}

void SendLedMatrixScore(){
  byte byte0 = score & 0xFF;
  byte byte1 = (score & 0xFF00)>>8;
  byte byte2 = (score & 0xFF0000)>>16;
  byte byte3 = (score & 0xFF000000)>>24;
  
  Wire.beginTransmission(4);
  Wire.write(byte3); Wire.write(byte2); Wire.write(byte1); Wire.write(byte0);
  Wire.endTransmission();
}

void SendLedMatrixScore(byte playerId){
  byte byte0 = score & 0xFF;
  byte byte1 = (score & 0xFF00)>>8;
  byte byte2 = (score & 0xFF0000)>>16;
  byte byte3 = (score & 0xFF000000)>>24;
  
  Wire.beginTransmission(4);
  Wire.write(playerId); Wire.write(byte3); Wire.write(byte2); Wire.write(byte1); Wire.write(byte0);
  Wire.endTransmission();
}

void SendHighScores() {
  byte i = 0;
  
  Wire.beginTransmission(4);
  //Send scores from 0 to 4
  //it is 4 x 5 = 20 bytes
  for(i = 0; i < 5; i++){
    byte byte0 = scoreTab[i] & 0xFF;
    byte byte1 = (scoreTab[i] & 0xFF00)>>8;
    byte byte2 = (scoreTab[i] & 0xFF0000)>>16;
    byte byte3 = (scoreTab[i] & 0xFF000000)>>24;
    
    Wire.write(byte3); Wire.write(byte2); Wire.write(byte1); Wire.write(byte0);
  }
  Wire.endTransmission();
  
  delay(100);
  Wire.beginTransmission(4);
  //Send next 5 highscores, 5 to 9
  for(i = 5; i < 10; i++){
    byte byte0 = scoreTab[i] & 0xFF;
    byte byte1 = (scoreTab[i] & 0xFF00)>>8;
    byte byte2 = (scoreTab[i] & 0xFF0000)>>16;
    byte byte3 = (scoreTab[i] & 0xFF000000)>>24;
    
    Wire.write(byte3); Wire.write(byte2); Wire.write(byte1); Wire.write(byte0);
  }
  Wire.endTransmission();
  
  //Send Player names
  Wire.beginTransmission(4);
  Wire.write(highscoreName1, 11);
  Wire.write(1);
  Wire.endTransmission();
  
  Wire.beginTransmission(4);
  Wire.write(highscoreName2, 11);
  Wire.write(2);
  Wire.endTransmission();

  Wire.beginTransmission(4);
  Wire.write(highscoreName3, 11);
  Wire.write(3);
  Wire.endTransmission();

  Wire.beginTransmission(4);
  Wire.write(highscoreName4, 11);
  Wire.write(4);
  Wire.endTransmission();

  Wire.beginTransmission(4);
  Wire.write(highscoreName5, 11);
  Wire.write(5);
  Wire.endTransmission();
  
  Wire.beginTransmission(4);
  Wire.write(highscoreName6, 11);
  Wire.write(6);
  Wire.endTransmission();
  
  Wire.beginTransmission(4);
  Wire.write(highscoreName7, 11);
  Wire.write(7);
  Wire.endTransmission();
  
  Wire.beginTransmission(4);
  Wire.write(highscoreName8, 11);
  Wire.write(8);
  Wire.endTransmission();
  
  Wire.beginTransmission(4);
  Wire.write(highscoreName9, 11);
  Wire.write(9);
  Wire.endTransmission();
  
  Wire.beginTransmission(4);
  Wire.write(highscoreName10, 11);
  Wire.write(10);
  Wire.endTransmission();
}


