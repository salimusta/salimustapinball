
/*EEPROM memory adress

TOTAL 1000 Byte

1 index = 1 Byte

LONGS (4 Bytes)
0: Score 1
5: Score 2
10: Score 3
15: Score 4
20: Score 5

25: Score 6
30: Score 7
35: Score 8
40: Score 9
45: Score 10


CHAR ( 10 caractere par nom)
100: Nom 1
150: Nom 2
200: Nom 3
250: Nom 4
300: Nom 5

350: Nom 6
400: Nom 7
450: Nom 8
500: Nom 9
550: Nom 10

//Maintenance Data

600: Total Ball Fired
650: Total Bumper Fired
700: Total Target Reached
750: Total Game played

*/

void WritePinballData(long ballFired, long bumperFired, long targets, long games){
  long ballFiredTotal = ReadNumber(600) + ballFired;
  long bumperFiredTotal = ReadNumber(650) + bumperFired;
  long targetsTotal = ReadNumber(700) + targets;
  long gamesTotal = ReadNumber(750) + games;
  
  WriteNumber(600, ballFiredTotal);
  WriteNumber(650, bumperFiredTotal);
  WriteNumber(700, targetsTotal);
  WriteNumber(750, gamesTotal);
}

//This function write a score to a specific memory adress
void WriteNumber(int adress, long number){
  byte byte0 = number & 0xFF;
  byte byte1 = (number & 0xFF00)>>8;
  byte byte2 = (number & 0xFF0000)>>16;
  byte byte3 = (number & 0xFF000000)>>24;
  
  EEPROM.write(adress, byte0);
  EEPROM.write(adress + 1, byte1);
  EEPROM.write(adress + 2, byte2);
  EEPROM.write(adress + 3, byte3);
}

long ReadNumber(int adress){
  long number = 0;

  byte byte0 = EEPROM.read(adress);
  byte byte1 = EEPROM.read(adress + 1);
  byte byte2 = EEPROM.read(adress + 2);
  byte byte3 = EEPROM.read(adress + 3);
  
  number = byte3;
  number = number<<8;
  number = number | byte2;
  number = number << 8;
  number = number | byte1;
  number = number << 8;
  number = number | byte0;
  
  return number;
 
}

void WriteName(int adress, char *name){
  char *p = name;
  int adressInc = adress;
  while(*p){
    EEPROM.write(adressInc++, *p++);
  }
}

void ReadName(int adress, char buf[10]){
  for(byte i = 0; i < 10 ; i++){
    buf[i] = EEPROM.read(adress + i);
  }
  buf[10] = '\0';
}

void ResetScoreMemory(){
  WriteName(100, "SALIMUSTA");
  WriteName(150, " ");
  WriteName(200, " ");
  WriteName(250, " ");
  WriteName(300, " ");
  WriteName(350, " ");
  WriteName(400, " ");
  WriteName(450, " ");
  WriteName(500, " ");
  WriteName(550, " ");
  
  WriteNumber(0, 50);
  WriteNumber(5, 0);
  WriteNumber(10, 0);
  WriteNumber(15, 0);
  WriteNumber(20, 0);
  WriteNumber(25, 0);
  WriteNumber(30, 0);
  WriteNumber(35, 0);
  WriteNumber(40, 0);
  WriteNumber(45, 0);
}

void printHighScores(){

  for(byte i = 0; i < 10; i++){
    Serial.print(i); Serial.print(" :");
    if(i == 0) Serial.print(highscoreName1);
    else if(i == 1) Serial.print(highscoreName2);
    else if(i == 2) Serial.print(highscoreName3);
    else if(i == 3) Serial.print(highscoreName4);
    else if(i == 4) Serial.print(highscoreName5);
    else if(i == 5) Serial.print(highscoreName6);
    else if(i == 6) Serial.print(highscoreName7);
    else if(i == 7) Serial.print(highscoreName8);
    else if(i == 8) Serial.print(highscoreName9);
    else if(i == 9) Serial.print(highscoreName10);
    
    Serial.print("-");
    
    Serial.print(scoreTab[i]);
    Serial.print("\n");
  } 
  
}
void ReadScoreMemory(){
  scoreTab[0] = ReadNumber(0);
  scoreTab[1] = ReadNumber(5);
  scoreTab[2] = ReadNumber(10);
  scoreTab[3] = ReadNumber(15);
  scoreTab[4] = ReadNumber(20);
  scoreTab[5] = ReadNumber(25);
  scoreTab[6] = ReadNumber(30);
  scoreTab[7] = ReadNumber(35);
  scoreTab[8] = ReadNumber(40);
  scoreTab[9] = ReadNumber(45);
  
  ReadName(100, highscoreName1);
  ReadName(150, highscoreName2);
  ReadName(200, highscoreName3);
  ReadName(250, highscoreName4);
  ReadName(300, highscoreName5);
  ReadName(350, highscoreName6);
  ReadName(400, highscoreName7);
  ReadName(450, highscoreName8);
  ReadName(500, highscoreName9);
  ReadName(550, highscoreName10);
  
  printHighScores();
}

void WriteScoreMemory(){
  WriteName(100, highscoreName1);
  WriteName(150, highscoreName2);
  WriteName(200, highscoreName3);
  WriteName(250, highscoreName4);
  WriteName(300, highscoreName5);
  WriteName(350, highscoreName6);
  WriteName(400, highscoreName7);
  WriteName(450, highscoreName8);
  WriteName(500, highscoreName9);
  WriteName(550, highscoreName10);
  
  WriteNumber(0, scoreTab[0]);
  WriteNumber(5, scoreTab[1]);
  WriteNumber(10, scoreTab[2]);
  WriteNumber(15, scoreTab[3]);
  WriteNumber(20, scoreTab[4]);
  WriteNumber(25, scoreTab[5]);
  WriteNumber(30, scoreTab[6]);
  WriteNumber(35, scoreTab[7]);
  WriteNumber(40, scoreTab[8]);
  WriteNumber(45, scoreTab[9]);
}

long getMinScore(){
  return scoreTab[9];
}

void addHighScore(long newScore, char *newPlayer){
  byte insertionIndex = 0;
  printHighScores();
  while( newScore < scoreTab[insertionIndex]){
    insertionIndex++; 
  }
  //Decalage des scores
  
  
  if(insertionIndex == 0){
    scoreTab[9] = scoreTab[8]; strncpy(highscoreName10, highscoreName9, 11);
    scoreTab[8] = scoreTab[7]; strncpy(highscoreName9, highscoreName8, 11);
    scoreTab[7] = scoreTab[6]; strncpy(highscoreName8, highscoreName7, 11);
    scoreTab[6] = scoreTab[5]; strncpy(highscoreName7, highscoreName6, 11);
    scoreTab[5] = scoreTab[4]; strncpy(highscoreName6, highscoreName5, 11);
    scoreTab[4] = scoreTab[3]; strncpy(highscoreName5, highscoreName4, 11);
    scoreTab[3] = scoreTab[2]; strncpy(highscoreName4, highscoreName3, 11);
    scoreTab[2] = scoreTab[1]; strncpy(highscoreName3, highscoreName2, 11);
    scoreTab[1] = scoreTab[0]; strncpy(highscoreName2, highscoreName1, 11);
    scoreTab[0] = newScore; strncpy(highscoreName1, newPlayer, 11);
    
  }else if(insertionIndex == 1){
    scoreTab[9] = scoreTab[8]; strncpy(highscoreName10, highscoreName9, 11);
    scoreTab[8] = scoreTab[7]; strncpy(highscoreName9, highscoreName8, 11);
    scoreTab[7] = scoreTab[6]; strncpy(highscoreName8, highscoreName7, 11);
    scoreTab[6] = scoreTab[5]; strncpy(highscoreName7, highscoreName6, 11);
    scoreTab[5] = scoreTab[4]; strncpy(highscoreName6, highscoreName5, 11);
    scoreTab[4] = scoreTab[3]; strncpy(highscoreName5, highscoreName4, 11);
    scoreTab[3] = scoreTab[2]; strncpy(highscoreName4, highscoreName3, 11);
    scoreTab[2] = scoreTab[1]; strncpy(highscoreName3, highscoreName2, 11);
    scoreTab[1] = newScore; strncpy(highscoreName2, newPlayer, 11);
    
  }else if(insertionIndex == 2){
    scoreTab[9] = scoreTab[8]; strncpy(highscoreName10, highscoreName9, 11);
    scoreTab[8] = scoreTab[7]; strncpy(highscoreName9, highscoreName8, 11);
    scoreTab[7] = scoreTab[6]; strncpy(highscoreName8, highscoreName7, 11);
    scoreTab[6] = scoreTab[5]; strncpy(highscoreName7, highscoreName6, 11);
    scoreTab[5] = scoreTab[4]; strncpy(highscoreName6, highscoreName5, 11);
    scoreTab[4] = scoreTab[3]; strncpy(highscoreName5, highscoreName4, 11);
    scoreTab[3] = scoreTab[2]; strncpy(highscoreName4, highscoreName3, 11);
    scoreTab[2] = newScore; strncpy(highscoreName3, newPlayer, 11);
    
  }else if(insertionIndex == 3){
    scoreTab[9] = scoreTab[8]; strncpy(highscoreName10, highscoreName9, 11);
    scoreTab[8] = scoreTab[7]; strncpy(highscoreName9, highscoreName8, 11);
    scoreTab[7] = scoreTab[6]; strncpy(highscoreName8, highscoreName7, 11);
    scoreTab[6] = scoreTab[5]; strncpy(highscoreName7, highscoreName6, 11);
    scoreTab[5] = scoreTab[4]; strncpy(highscoreName6, highscoreName5, 11);
    scoreTab[4] = scoreTab[3]; strncpy(highscoreName5, highscoreName4, 11);
    scoreTab[3] = newScore; strncpy(highscoreName4, newPlayer, 11);
    
  }else if(insertionIndex == 4){
    scoreTab[9] = scoreTab[8]; strncpy(highscoreName10, highscoreName9, 11);
    scoreTab[8] = scoreTab[7]; strncpy(highscoreName9, highscoreName8, 11);
    scoreTab[7] = scoreTab[6]; strncpy(highscoreName8, highscoreName7, 11);
    scoreTab[6] = scoreTab[5]; strncpy(highscoreName7, highscoreName6, 11);
    scoreTab[5] = scoreTab[4]; strncpy(highscoreName6, highscoreName5, 11);
    scoreTab[4] = newScore; strncpy(highscoreName5, newPlayer, 11);
    
  }else if(insertionIndex == 5){
    scoreTab[9] = scoreTab[8]; strncpy(highscoreName10, highscoreName9, 11);
    scoreTab[8] = scoreTab[7]; strncpy(highscoreName9, highscoreName8, 11);
    scoreTab[7] = scoreTab[6]; strncpy(highscoreName8, highscoreName7, 11);
    scoreTab[6] = scoreTab[5]; strncpy(highscoreName7, highscoreName6, 11);
    scoreTab[5] = newScore; strncpy(highscoreName6, newPlayer, 11);
    
  }else if(insertionIndex == 6){
    scoreTab[9] = scoreTab[8]; strncpy(highscoreName10, highscoreName9, 11);
    scoreTab[8] = scoreTab[7]; strncpy(highscoreName9, highscoreName8, 11);
    scoreTab[7] = scoreTab[6]; strncpy(highscoreName8, highscoreName7, 11);
    scoreTab[6] = newScore; strncpy(highscoreName7, newPlayer, 11);
    
  }else if(insertionIndex == 7){
    scoreTab[9] = scoreTab[8]; strncpy(highscoreName10, highscoreName9, 11);
    scoreTab[8] = scoreTab[7]; strncpy(highscoreName9, highscoreName8, 11);
    scoreTab[7] = newScore; strncpy(highscoreName8, newPlayer, 11);
    
  }else if(insertionIndex == 8){
    scoreTab[9] = scoreTab[8]; strncpy(highscoreName10, highscoreName9, 11);
    scoreTab[8] = newScore; strncpy(highscoreName9, newPlayer, 11);
    
  }else if(insertionIndex == 9){
    scoreTab[9] = newScore; strncpy(highscoreName10, newPlayer, 11);
  }
  printHighScores();
}
