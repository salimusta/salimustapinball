
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
  WriteName(100, "BOB       ");
  WriteName(150, "JAMES     ");
  WriteName(200, "MOHAMMED  ");
  WriteName(250, "CHING     ");
  WriteName(300, "ABDEL     ");
  
  WriteScore(0, 1000);
  WriteScore(5, 800);
  WriteScore(10, 555);
  WriteScore(15, 320);
  WriteScore(20, 2);
}

void ReadScoreMemory(){
  scoreTab[0] = ReadScore(0);
  scoreTab[1] = ReadScore(5);
  scoreTab[2] = ReadScore(10);
  scoreTab[3] = ReadScore(15);
  scoreTab[4] = ReadScore(20);
  
  ReadName(100, highscoreName1);
  ReadName(150, highscoreName2);
  ReadName(200, highscoreName3);
  ReadName(250, highscoreName4);
  ReadName(300, highscoreName5);
  
}

void WriteScoreMemory(){
  WriteName(100, highscoreName1);
  WriteName(150, highscoreName2);
  WriteName(200, highscoreName3);
  WriteName(250, highscoreName4);
  WriteName(300, highscoreName5);
  
  WriteScore(0, scoreTab[0]);
  WriteScore(5, scoreTab[1]);
  WriteScore(10, scoreTab[2]);
  WriteScore(15, scoreTab[3]);
  WriteScore(20, scoreTab[4]);
}

long getMinScore(){
  return scoreTab[4];
}

void addHighScore(long newScore, char *newPlayer){
  byte insertionIndex = 0;
  
  while( newScore < scoreTab[insertionIndex]){
    insertionIndex++; 
  }
  //Decalage des scores
  if(insertionIndex == 0){
    scoreTab[4] = scoreTab[3]; strncpy(highscoreName5, highscoreName4, 11);
    scoreTab[3] = scoreTab[2]; strncpy(highscoreName4, highscoreName3, 11);
    scoreTab[2] = scoreTab[1]; strncpy(highscoreName3, highscoreName2, 11);
    scoreTab[1] = scoreTab[0]; strncpy(highscoreName2, highscoreName1, 11);
    scoreTab[0] = newScore; strncpy(highscoreName1, newPlayer, 11);
    
  }else if(insertionIndex == 1){
    scoreTab[4] = scoreTab[3]; strncpy(highscoreName5, highscoreName4, 11);
    scoreTab[3] = scoreTab[2]; strncpy(highscoreName4, highscoreName3, 11);
    scoreTab[2] = scoreTab[1]; strncpy(highscoreName3, highscoreName2, 11);
    scoreTab[1] = newScore; strncpy(highscoreName2, newPlayer, 11);
    
  }else if(insertionIndex == 2){
    scoreTab[4] = scoreTab[3]; strncpy(highscoreName5, highscoreName4, 11);
    scoreTab[3] = scoreTab[2]; strncpy(highscoreName4, highscoreName3, 11);
    scoreTab[2] = newScore; strncpy(highscoreName3, newPlayer, 11);
    
  }else if(insertionIndex == 3){
    scoreTab[4] = scoreTab[3]; strncpy(highscoreName5, highscoreName4, 11);
    scoreTab[3] = newScore; strncpy(highscoreName4, newPlayer, 11);
    
  }else if(insertionIndex == 4){
    scoreTab[4] = newScore; strncpy(highscoreName5, newPlayer, 11);
  }
  
}
