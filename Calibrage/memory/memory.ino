#include <EEPROM.h>


/*EEPROM memory adress

TOTAL 1000 Byte

1 index = 1 Byte

LONGS (4 Bytes)
0: Score 1
5: Score 2
10: Score 3
15: Score 4
20: Score 5


CHAR ( 10 caractere par nom)
100: Nom 1
150: Nom 2
200: Nom 3
250: Nom 4
300: Nom 5

*/


int addr = 0;

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

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600); 
  
  /*long score1 = 12345;
  long score2 = 54321;
  
  WriteScore(0, score1);
  
  WriteScore(5, score2);
  */
  
  //WriteName(100, "SALIM");
  //WriteName(150, "AbCdEfGhIj");
  
  char name2[11];
  ReadName(150, name2);
  
  char name1[11];
  ReadName(100, name1);
  
  
  
  Serial.print("\nName1 = ");
  Serial.print(name1);
  Serial.print("\nName2 = ");
  Serial.print(name2);
}



void loop() {

  long score1 = ReadScore(0);
  Serial.print("\nscore = ");
  Serial.print(score1);
  
  long score2 = ReadScore(10);
  Serial.print("\nscore = ");
  Serial.print(score2);
  
  
  
  delay(50000);
}
