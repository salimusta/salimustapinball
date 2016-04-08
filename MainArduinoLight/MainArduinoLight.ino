#include <LiquidCrystal.h>
#include <Wire.h>
#include "defines.h"
#include "wavTrigger.h"
#include <EEPROM.h>

byte leftButton_State = 0;
byte rightButton_State = 0;
byte OkButton_State = 0;
byte BackButton_State = 0;
byte leftButton_State_Old = 0;
byte rightButton_State_Old = 0;
byte OkButton_State_Old = 0;
byte BackButton_State_Old = 0;

bool BSW1 = false; bool BSW2 = false; bool BSW3 = false; bool ROSW1 = false; bool ROSW2 = false; bool ROSW3 = false; bool TRIEUR = false; bool KO2 = false;
bool RKSW = false; bool LKSW = false; bool LOSW = false; bool RLOSW = false; bool LLOSW = false; bool CT = false; bool CTP = false;
bool RT1 = false; bool RT1P = false; bool RT2 = false; bool LT1 = false; bool LT2 = false; bool LT2P = false; bool KO1 = false;
bool RAMP1 = false; bool RAMP2 = false;
bool LEFT_FLIPPER = false; bool RIGHT_FLIPPER = false; bool START = false;

bool BSW1_Old = false; bool BSW2_Old = false; bool BSW3_Old = false; bool ROSW1_Old = false; bool ROSW2_Old = false; bool ROSW3_Old = false; bool KO1_Old = false;
bool TRIEUR_Old = false; bool KO2_Old = false; bool RKSW_Old = false; bool LKSW_Old = false; bool LOSW_Old = false; bool RLOSW_Old = false; bool LLOSW_Old = false;
bool CT_Old = false; bool CTP_Old = false; bool RT1_Old = false; bool RT1P_Old = false; bool RT2_Old = false; bool LT1_Old = false; bool LT2_Old = false; bool LT2P_Old = false;
bool RAMP1_Old = false; bool RAMP2_Old = false;
bool LEFT_FLIPPER_Old = false; bool RIGHT_FLIPPER_Old = false; bool START_Old = false;

long scoreTab[5];
char highscoreName1[11]; 
char highscoreName2[11]; 
char highscoreName3[11]; 
char highscoreName4[11]; 
char highscoreName5[11]; 

bool maintenanceMode = true;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

wavTrigger wTrig;

void setup() {
  Serial.begin(9600); 
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("SalimUstaPinball");
  lcd.setCursor(0, 1);
  lcd.print("----------------");
  Wire.begin(); 
  pinMode(leftBoutonPin, INPUT);  
  pinMode(rightBoutonPin, INPUT);
  pinMode(OkBoutonPin, INPUT);
  pinMode(BackBoutonPin, INPUT);
  
  //Initialize the serial communication
  wTrig.start();
  
  delay(1000);
  AmbiLight(ANIME_ALL);
  AnimLight(ANIM_ALL);
  AnimLight2(ANIM_ALL);
  wTrig.stopAllTracks();
  
  //ResetScoreMemory();
  ReadScoreMemory();
}

void loop() {
  SendHighScores();
  

  //Boucle
  int nbIteration = 0;
  while(1){
    Serial.print("Lancement d'une balle...\n");
    ShootABall();
    delay(5000);
    
    ReadSwitches();
    while( !LOSW ){
      ReadSwitches();
      delay(10);
    }
    nbIteration++;
    Serial.print("Succes = "); Serial.print(nbIteration); Serial.print("\n");
  }
  
  /*
  AmbiLight(ALL_OFF);
    AnimLight(ALL_ANIM_OFF);
    AnimLight2(ALL_ANIM_OFF);
  
  delay(3000);
  
  AnimLight2(RAMPGATE_SNAKE); delay(3000);
  AnimLight2(RAMPGATE_BLINK); delay(3000);
  AnimLight2(RAMPGATE_ON); delay(3000);
  AnimLight2(RAMPGATE_DUAL_SNAKE); delay(3000);
  AnimLight2(RAMPGATE_ALTERNATE); delay(3000);
  AnimLight2(RAMPGATE_OFF); delay(3000);
  
  AnimLight2(RAMP_ON); delay(3000);
  AnimLight2(RAMP_BLUE); delay(3000);
  AnimLight2(RAMP_YELLOW); delay(3000);
  AnimLight2(RAMP_SNAKE_BLUE); delay(3000);
  AnimLight2(RAMP_SNAKE_YELLOW); delay(3000);
  AnimLight2(RAMP_SNAKE); delay(3000);
  AnimLight2(RAMP_BLINK); delay(3000);
  AnimLight2(RAMP_ALTERNATE); delay(3000);
  AnimLight2(RAMP_OFF); delay(3000);
  delay(30000);
  /*TESTING LIGHTS 
  
  AmbiLight(ALL_OFF);
  AnimLight(ALL_ANIM_OFF);
  
  delay(2000);
  PlaySound(DESIREHEY);
  
  AnimLightData(DATA_YELLOW_TARGET, 0b1);
  AnimLightFor(BLINK_YELLOW_TARGET, 30);
  delay(2000);
  AnimLightData(DATA_YELLOW_TARGET, 0b11);
  AnimLightFor(BLINK_YELLOW_TARGET, 30);
  delay(2000);
  AnimLightData(DATA_YELLOW_TARGET, 0b111);
  delay(2000);
  AnimLightFor(BLINK_YELLOW_TARGET, 30);
  delay(2000);
  AnimLightData(DATA_YELLOW_TARGET, 0b1111);
  delay(2000);
  AnimLightData(DATA_YELLOW_TARGET, 0b11111);
  delay(200000);
  */
  
/*
  DisplayScreen(SCREEN_STARWARS_GAME, PRIORITY_LOW);
  while(1){
  
    byte flippers_state = digitalRead(rightBoutonPin);;
    flippers_state = (flippers_state << 1) | digitalRead(leftBoutonPin);
    SendScreenData(FLIPPERS_STATE, flippers_state);
    delay(20);
  }
  /*---------*/
  DisplayScreen(SCREEN_SALIMUSTAPINBALL, PRIORITY_LOW);

  printLine("<- MAINTENANCE", "    GAME MODE ->");

  leftButton_State = digitalRead(leftBoutonPin);
  rightButton_State = digitalRead(rightBoutonPin);
  while(leftButton_State == LOW && rightButton_State == LOW){
    leftButton_State = digitalRead(leftBoutonPin);
    rightButton_State = digitalRead(rightBoutonPin);
  }
  maintenanceMode = (leftButton_State == HIGH);
  
  if(maintenanceMode){
    printLine("--MAINTENANCE---", "------MODE------");
  }else{
    printLine("------GAME------", "------MODE------");
  }
  
  //maintenanceMode = false;
  delay(100);
  if(maintenanceMode){
    AmbiLight(ALL_OFF);
    AnimLight(ALL_ANIM_OFF);
    AnimLight2(ALL_ANIM_OFF);
    PlaySound(DESIREHEY);
    while(1) ManageMaintenanceMode(); 
  }else{
    DisplayScreen(SCREEN_HIGHSCORES, PRIORITY_LOW);
    WaitForRestart();
    while(1) ManageGame();
  }
}


void printLine(char *str1, char *str2){
  short str1Length;
  for(str1Length=0; str1[str1Length]!='\0'; ++str1Length);
  short str2Length;
  for(str2Length=0; str2[str2Length]!='\0'; ++str2Length);
  
  lcd.setCursor(0, 0); lcd.print(str1);
  for(byte i = str1Length; i < 16; i++) lcd.print(" ");
  lcd.setCursor(0, 1); lcd.print(str2);
  for(byte i = str2Length; i < 16; i++) lcd.print(" ");
}
