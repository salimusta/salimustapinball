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
bool LEFT_FLIPPER = false; bool RIGHT_FLIPPER = false; bool START = false; bool TILT = false;

bool BSW1_Old = false; bool BSW2_Old = false; bool BSW3_Old = false; bool ROSW1_Old = false; bool ROSW2_Old = false; bool ROSW3_Old = false; bool KO1_Old = false;
bool TRIEUR_Old = false; bool KO2_Old = false; bool RKSW_Old = false; bool LKSW_Old = false; bool LOSW_Old = false; bool RLOSW_Old = false; bool LLOSW_Old = false;
bool CT_Old = false; bool CTP_Old = false; bool RT1_Old = false; bool RT1P_Old = false; bool RT2_Old = false; bool LT1_Old = false; bool LT2_Old = false; bool LT2P_Old = false;
bool RAMP1_Old = false; bool RAMP2_Old = false;
bool LEFT_FLIPPER_Old = false; bool RIGHT_FLIPPER_Old = false; bool START_Old = false; bool TILT_Old = false;

long scoreTab[10];
char highscoreName1[11]; 
char highscoreName2[11]; 
char highscoreName3[11]; 
char highscoreName4[11]; 
char highscoreName5[11];
char highscoreName6[11]; 
char highscoreName7[11]; 
char highscoreName8[11]; 
char highscoreName9[11]; 
char highscoreName10[11]; 

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
  
  delay(100);
  
  //If there are balls caught in holes at the beginning, empty them and wait
  ReadSwitches();
  delay(1000);
  if(KO1 || KO1_Old) FireKickout1();
  delay(500);
  if(KO2 || KO2_Old) FireKickout2();
  
  if(KO1 || KO1_Old || KO2 || KO2_Old){
    delay(5000); 
  }
}

void loop() {
  SendHighScores();

  /*---------*/
  /*DisplayScreen(SCREEN_SALIMUSTAPINBALL, PRIORITY_LOW);

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
  */
  delay(1000);
  maintenanceMode = digitalRead(leftBoutonPin) == HIGH;

  delay(100);
  if(maintenanceMode){
    AmbiLight(ALL_OFF);
    AnimLight(ALL_ANIM_OFF);
    AnimLight2(ALL_ANIM_OFF);
    PlaySound(DESIREHEY);
    //while(1) ManageMaintenanceMode(); 
  }else{
    DisplayScreen(SCREEN_HIGHSCORES, PRIORITY_LOW);
    WaitForRestart();
    PlaySound(PIECE);
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
