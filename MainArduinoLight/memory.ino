
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

*/

//This function write a score to a specific memory adress
void WriteScore(int adress, long score){
  byte byte0 = score & 0xFF;
  byte byte1 = (score & 0xFF00)>>8;
  byte byte2 = (score & 0xFF0000)>>16;
  byte byte3 = (score & 0xFF000000)>>24;
  
  EEPROM.write(adress, byte0);
  EEPROM.write(adress + 1, byte1);
  EEPROM.write(adress + 2, byte2);
  EEPROM.write(adress + 3, byte3);
}

long ReadScore(int adress){
  long score = 0;

  byte byte0 = EEPROM.read(adress);
  byte byte1 = EEPROM.read(adress + 1);
  byte byte2 = EEPROM.read(adress + 2);
  byte byte3 = EEPROM.read(adress + 3);
  
  score = byte3;
  score = score<<8;
  score = score | byte2;
  score = score << 8;
  score = score | byte1;
  score = score << 8;
  score = score | byte0;
  
  return score;
 
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
  
  WriteScore(0, 50);
  WriteScore(5, 0);
  WriteScore(10, 0);
  WriteScore(15, 0);
  WriteScore(20, 0);
  WriteScore(25, 0);
  WriteScore(30, 0);
  WriteScore(35, 0);
  WriteScore(40, 0);
  WriteScore(45, 0);
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
  scoreTab[0] = ReadScore(0);
  scoreTab[1] = ReadScore(5);
  scoreTab[2] = ReadScore(10);
  scoreTab[3] = ReadScore(15);
  scoreTab[4] = ReadScore(20);
  scoreTab[5] = ReadScore(25);
  scoreTab[6] = ReadScore(30);
  scoreTab[7] = ReadScore(35);
  scoreTab[8] = ReadScore(40);
  scoreTab[9] = ReadScore(45);
  
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
  
  WriteScore(0, scoreTab[0]);
  WriteScore(5, scoreTab[1]);
  WriteScore(10, scoreTab[2]);
  WriteScore(15, scoreTab[3]);
  WriteScore(20, scoreTab[4]);
  WriteScore(25, scoreTab[5]);
  WriteScore(30, scoreTab[6]);
  WriteScore(35, scoreTab[7]);
  WriteScore(40, scoreTab[8]);
  WriteScore(45, scoreTab[9]);
}

long getMinScore(){
  return scoreTab[9];
}

void addHighScore(long newScore, char *newPlayer){
  byte insertionIndex = 0;
  
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
  
}
