#include <Wire.h>

#define ANIM_ALL 1
#define ALL_OFF 2
#define VERT_SNAKE_ALL 81
#define ALL_IDLE 82
#define VERT_SNAKE_KEEP_ALL 83

#define FLASH_TOP_LIGHTS 3
#define LIGHT_TOP_LIGHTS 4
#define ALTERN_TOP_LIGHTS 5
#define OFF_TOP_LIGHTS 6
#define DUAL_SNAKE_TOP_LIGHTS 79

#define SNAKE_RIGHT_GREEN_TARGET 7
#define BLINK_RIGHT_GREEN_TARGET 8
#define OFF_RIGHT_GREEN_TARGET 9

#define SNAKE_LEFT_GREEN_TARGET 10
#define BLINK_LEFT_GREEN_TARGET 11
#define OFF_LEFT_GREEN_TARGET 12

#define SNAKE_RIGHT_RED_TARGET 13
#define BLINK_RIGHT_RED_TARGET 14
#define OFF_RIGHT_RED_TARGET 15

#define SNAKE_LEFT_RED_TARGET 16
#define BLINK_LEFT_RED_TARGET 17
#define OFF_LEFT_RED_TARGET 18

#define SNAKE_YELLOW_TARGET 19
#define BLINK_YELLOW_TARGET 20
#define OFF_YELLOW_TARGET 21

#define ALL_MODE_OFF 22
#define ALL_MODE_ON 77
#define MODE_3_BUMPERS 23
#define MODE_5_MIDDLE 24
#define MODE_GREEN_TARGETS 25
#define MODE_EXTRA_BALL 26
#define MODE_ALL_TARGETS 27
#define MODE_DOUBLE 28
#define MODE_RED_TARGETS 29
#define MODE_PSIT 30
#define SNAKE_MODES 31
#define BLINK_MODES 32

#define ALL_LETTERS_OFF 33
#define ALL_LETTERS_ON 34
#define LETTER_P_ON 35
#define LETTER_S_ON 36
#define LETTER_I_ON 37
#define LETTER_T_ON 38

#define BLINK_LETTER_P 39
#define BLINK_LETTER_S 40
#define BLINK_LETTER_I 41
#define BLINK_LETTER_T 42

#define LETTER_P_OFF 43
#define LETTER_S_OFF 44
#define LETTER_I_OFF 45
#define LETTER_T_OFF 46
#define SNAKE_LETTERS 47

#define ALL_BUMPERS_OFF 48
#define BUMPER_1_ON 49
#define BUMPER_2_ON 50
#define BUMPER_3_ON 51
#define BLINK_BUMPER_1 52
#define BLINK_BUMPER_2 53
#define BLINK_BUMPER_3 54
#define BUMPER_1_OFF 55
#define BUMPER_2_OFF 56
#define BUMPER_3_OFF 57
#define ALL_BUMPERS_ON 58
#define SNAKE_BUMPERS 80

#define ALL_GATES_ON 59
#define ALL_GATES_OFF 60
#define GATE_1_ON 61
#define GATE_2_ON 62
#define GATE_3_ON 63
#define GATE_1_OFF 64
#define GATE_2_OFF 65
#define GATE_3_OFF 66

#define SNAKE_LAUNCHER 67
#define LAUNCHER_OFF 68

#define LOOSE_OFF 69
#define BLINK_LOOSE 70

#define KO1_OFF 71
#define BLINK_KO1 72
#define SNAKE_KO1 73

#define KO2_OFF 74
#define BLINK_KO2 75
#define SNAKE_KO2 76


int latchPinA = 13; int latchPinB = 12;
int latchPinC = 11; int latchPinD = 10;
int latchPinE = 9; int latchPinF = 8;
int latchPinG = 7; int latchPinH = 6;
int latchPinI = 5; int latchPinJ = 4;

int dataPin = 2; int clockPin = 3;

//ALL param
byte allAnimModeState = 1;
byte allAnimMode = ALL_IDLE;
byte allAnimModeFrame = 0;
bool allAnim = false;

//LEFT RED TARGET
byte LeftRedAnim = 0;
byte LeftRedTargetAnimMode = OFF_LEFT_RED_TARGET;
byte LeftRedTargetAnimMode_Old = OFF_LEFT_RED_TARGET;
int LeftRedTargetAnimTime = 0;

//RIGHT RED TARGET
byte RightRedAnim = 0;
byte RightRedTargetAnimMode = OFF_RIGHT_RED_TARGET;
byte RightRedTargetAnimMode_Old = OFF_RIGHT_RED_TARGET;
int RightRedTargetAnimTime = 0;

//LEFT GREEN TARGET
byte LeftGreenAnim = 0;
byte LeftGreenTargetAnimMode = OFF_LEFT_GREEN_TARGET;
byte LeftGreenTargetAnimMode_Old = OFF_LEFT_GREEN_TARGET;
int LeftGreenTargetAnimTime = 0;

//RIGHT GREEN TARGET
byte RightGreenAnim = 0;
byte RightGreenTargetAnimMode = OFF_RIGHT_GREEN_TARGET;
byte RightGreenTargetAnimMode_Old = OFF_RIGHT_GREEN_TARGET;
int RightGreenTargetAnimTime = 0;

//MIDDLE YELLOW TARGET
byte MiddleYellowAnim = 0;
byte YellowTargetAnimMode = OFF_YELLOW_TARGET;
byte YellowTargetAnimMode_Old = OFF_YELLOW_TARGET;
byte YellowTargetAnimTime = 0;

//MODES ANIM
byte ModesAnim = 0;
byte ModesAnimMode = ALL_MODE_OFF;
byte ModesAnimMode_Old = ALL_MODE_OFF;
byte ModesAnimTime = 0;

//Launcher Anim
byte LauncherAnim = 0;
byte LauncherAnimMode = LAUNCHER_OFF;
byte LauncherAnimMode_Old = LAUNCHER_OFF;
byte LauncherAnimTime = 0;

//LOOSE anim
byte LooseAnim = 0;
byte LooseAnimMode = LOOSE_OFF;
byte LooseAnimMode_Old = LOOSE_OFF;
byte LooseAnimTime = 0;

//Flash Anim
byte FlashAnim = 0;
byte FlashAnimMode = OFF_TOP_LIGHTS;
byte FlashAnimMode_Old = OFF_TOP_LIGHTS;
byte FlashAnimTime = 0;
byte FlashAnimSide = true;

//Letters
byte LettersAnimMode = ALL_LETTERS_OFF;
byte LettersAnimMode_Old = ALL_LETTERS_OFF;
byte LettersAnimTime = 0;

//Letter P
byte Pletter = 0;
byte PletterAnimMode = LETTER_P_OFF;
byte PletterAnimMode_Old = LETTER_P_OFF;
byte PletterAnimTime = 0;

//Letter S
byte Sletter = 0;
byte SletterAnimMode = LETTER_S_OFF;
byte SletterAnimMode_Old = LETTER_S_OFF;
byte SletterAnimTime = 0;

//Letter I
byte Iletter = 0;
byte IletterAnimMode = LETTER_I_OFF;
byte IletterAnimMode_Old = LETTER_I_OFF;
byte IletterAnimTime = 0;

//Letter T
byte Tletter = 0;
byte TletterAnimMode = LETTER_T_OFF;
byte TletterAnimMode_Old = LETTER_T_OFF;
byte TletterAnimTime = 0;

//KO1
byte KO1Anim = 0;
byte KO1AnimMode = KO1_OFF;
byte KO1AnimMode_Old = KO1_OFF;
byte KO1AnimTime = 0;

//KO2
byte KO2Anim = 0;
byte KO2AnimMode = KO2_OFF;
byte KO2AnimMode_Old = KO2_OFF;
byte KO2AnimTime = 0;

//Gates
byte Gate1Light = 0;
byte Gate2Light = 0;
byte Gate3Light = 0;


//BUMPER 1
byte Bumper1Light = 0;
byte Bumper1Mode = BUMPER_1_OFF;
byte Bumper1Mode_Old = BUMPER_1_OFF;
byte Bumper1Time = 0;
byte BumperModeState = 1;

//BUMPER 1
byte Bumper2Light = 0;
byte Bumper2Mode = BUMPER_2_OFF;
byte Bumper2Mode_Old = BUMPER_2_OFF;
byte Bumper2Time = 0;

//Bumper 3
byte Bumper3Light = 0;
byte Bumper3Mode = BUMPER_3_OFF;
byte Bumper3Mode_Old = BUMPER_3_OFF;
byte Bumper3Time = 0;

int time = 0;

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPinA, OUTPUT); pinMode(latchPinB, OUTPUT);
  pinMode(latchPinC, OUTPUT); pinMode(latchPinD, OUTPUT);
  pinMode(latchPinE, OUTPUT); pinMode(latchPinF, OUTPUT);
  pinMode(latchPinG, OUTPUT); pinMode(latchPinH, OUTPUT);
  pinMode(latchPinI, OUTPUT); pinMode(latchPinJ, OUTPUT);
  
  pinMode(clockPin, OUTPUT); pinMode(dataPin, OUTPUT);
  
  Serial.begin(9600); 
  
  Wire.begin(5);
  Wire.onReceive(receiveEvent);
  
  //Starting value
//allAnimModeState = 1;
//allAnimMode = VERT_SNAKE_ALL;
}


void SetAllAnim(){
 LeftRedAnim = 1;
  LeftRedTargetAnimMode = SNAKE_LEFT_RED_TARGET;
  
  RightRedAnim = 1;
  RightRedTargetAnimMode = SNAKE_RIGHT_RED_TARGET;
  
  LeftGreenAnim = 1;
  LeftGreenTargetAnimMode = SNAKE_LEFT_GREEN_TARGET;
  
  RightGreenAnim = 1;
  RightGreenTargetAnimMode = SNAKE_RIGHT_GREEN_TARGET;
  
  MiddleYellowAnim = 1;
  YellowTargetAnimMode = SNAKE_YELLOW_TARGET;
  
  ModesAnim = 1;
  ModesAnimMode = SNAKE_MODES;
  
  LauncherAnim = 1;
  LauncherAnimMode = SNAKE_LAUNCHER;
  LooseAnim = 0;
  
  FlashAnim = 0b01010101;
  FlashAnimMode = ALTERN_TOP_LIGHTS;
  
  LettersAnimMode = SNAKE_LETTERS;
  Pletter = 1;
  Sletter = Iletter = Tletter = 0;
  
  KO1Anim = 1;
  KO1AnimMode = SNAKE_KO1;
  
  KO2Anim = 1;
  KO2AnimMode = SNAKE_KO2;
  
  Bumper1Time = Bumper2Time = Bumper3Time = 0;
  Bumper1Light = 1;
  Bumper1Mode = Bumper2Mode = Bumper3Mode = SNAKE_BUMPERS;
  
  Gate1Light = Gate2Light = Gate3Light = 1; 
}


void receiveEvent(int howMany) {
  byte duration = 0;
  allAnim = false;
  if(howMany == 1 || howMany == 2){
    byte byte0 = Wire.read();
    //TOP LIGHT--------------------------------------------------------------
    if(howMany == 2) duration = Wire.read();
    
    if(byte0 == ALL_OFF || byte0 == VERT_SNAKE_ALL || byte0 == VERT_SNAKE_KEEP_ALL){
      LeftRedAnim = 0;
      LeftRedTargetAnimMode = OFF_LEFT_RED_TARGET;
      LeftRedTargetAnimMode_Old = LeftRedTargetAnimMode;
      
      RightRedAnim = 0;
      RightRedTargetAnimMode = OFF_RIGHT_RED_TARGET;
      RightRedTargetAnimMode_Old = RightRedTargetAnimMode;
      
      LeftGreenAnim = 0;
      LeftGreenTargetAnimMode = OFF_LEFT_GREEN_TARGET;
      LeftGreenTargetAnimMode_Old = LeftGreenTargetAnimMode;
      
      RightGreenAnim = 0;
      RightGreenTargetAnimMode = OFF_RIGHT_GREEN_TARGET;
      RightGreenTargetAnimMode_Old = RightGreenTargetAnimMode;
      
      MiddleYellowAnim = 0;
      YellowTargetAnimMode = OFF_YELLOW_TARGET;
      YellowTargetAnimMode_Old = YellowTargetAnimMode;
      
      ModesAnim = 0;
      ModesAnimMode = ALL_MODE_OFF;
      ModesAnimMode_Old = ModesAnimMode;
      
      LauncherAnim = 0;
      LauncherAnimMode = LAUNCHER_OFF;
      LauncherAnimMode_Old = LauncherAnimMode;
      
      LooseAnim = 0;
      LooseAnimMode = LOOSE_OFF;
      LooseAnimMode_Old = LooseAnimMode;
      
      FlashAnim = 0;
      FlashAnimMode = OFF_TOP_LIGHTS;
      FlashAnimMode_Old = FlashAnimMode;
      
      LettersAnimMode = ALL_LETTERS_OFF;
      Pletter = Sletter = Iletter = Tletter = 0;
      LettersAnimMode_Old = LettersAnimMode;
      PletterAnimMode = 0; PletterAnimMode_Old = 0;
      SletterAnimMode = 0; SletterAnimMode_Old = 0;
      IletterAnimMode = 0; IletterAnimMode_Old = 0;
      TletterAnimMode = 0; TletterAnimMode_Old = 0;
      
      KO1Anim = 0;
      KO1AnimMode = KO1_OFF;
      KO1AnimMode_Old = KO1AnimMode;
      
      KO2Anim = 0;
      KO2AnimMode = KO2_OFF;
      KO2AnimMode_Old = KO2AnimMode;
      
      Bumper1Light = Bumper2Light = Bumper3Light = 0;
      Bumper1Mode = BUMPER_1_OFF;
      Bumper2Mode = BUMPER_2_OFF;
      Bumper3Mode = BUMPER_3_OFF;
      
      Bumper1Mode_Old = Bumper1Mode;
      Bumper2Mode_Old = Bumper2Mode;
      Bumper3Mode_Old = Bumper3Mode;
      
      Gate1Light = Gate2Light = Gate3Light = 0;
      
      if(byte0 == VERT_SNAKE_ALL){
        allAnimModeState = 1;
        allAnimMode = VERT_SNAKE_ALL;
      }else if(byte0 == VERT_SNAKE_KEEP_ALL){
        allAnimModeState = 1;
        allAnimMode = VERT_SNAKE_KEEP_ALL;
      }
    }else if(byte0 == ANIM_ALL){
      allAnim = true;
      allAnimModeFrame = 1;
      allAnimMode = ANIM_ALL;
      SetAllAnim();

      
    }else if(byte0 == FLASH_TOP_LIGHTS){
      if(duration > 0){ 
        if(FlashAnimTime == 0) FlashAnimMode_Old = FlashAnimMode;
        FlashAnimTime = duration;
       }
      else FlashAnimTime = 0;
      FlashAnim = 0b11111111;
      FlashAnimMode = FLASH_TOP_LIGHTS;
    }else if(byte0 == LIGHT_TOP_LIGHTS){
      if(duration > 0){ 
        if(FlashAnimTime == 0) FlashAnimMode_Old = FlashAnimMode;
        FlashAnimTime = duration;
       }
      else FlashAnimTime = 0;
      FlashAnim = 0b11111111;
      FlashAnimMode = LIGHT_TOP_LIGHTS;
    }else if(byte0 == ALTERN_TOP_LIGHTS){
      if(duration > 0){ 
        if(FlashAnimTime == 0) FlashAnimMode_Old = FlashAnimMode;
        FlashAnimTime = duration;
       }
      else FlashAnimTime = 0;
      FlashAnim = 0b01010101;
      FlashAnimMode = ALTERN_TOP_LIGHTS;
    }else if(byte0 == OFF_TOP_LIGHTS){
      if(duration > 0){ 
        if(FlashAnimTime == 0) FlashAnimMode_Old = FlashAnimMode;
        FlashAnimTime = duration;
       }
      else FlashAnimTime = 0;
      FlashAnim = 0;
      FlashAnimMode = OFF_TOP_LIGHTS;
      FlashAnimSide = true;
    
    }else if(byte0 == DUAL_SNAKE_TOP_LIGHTS){
      if(duration > 0){ 
        if(FlashAnimTime == 0) FlashAnimMode_Old = FlashAnimMode;
        FlashAnimTime = duration;
       }
      else FlashAnimTime = 0;
      FlashAnim = 1;
      FlashAnimMode = DUAL_SNAKE_TOP_LIGHTS;
      
      //LEFT GREEN TARGET--------------------------------------------------------
    }else if(byte0 == SNAKE_LEFT_GREEN_TARGET){
      if(duration > 0){LeftGreenTargetAnimMode_Old = LeftGreenTargetAnimMode;LeftGreenTargetAnimTime = duration;}
      else LeftGreenTargetAnimTime = 0;
      LeftGreenAnim = 1;
      LeftGreenTargetAnimMode = SNAKE_LEFT_GREEN_TARGET;
    }else if(byte0 == BLINK_LEFT_GREEN_TARGET){
      if(duration > 0){LeftGreenTargetAnimMode_Old = LeftGreenTargetAnimMode;LeftGreenTargetAnimTime = duration;}
      else LeftGreenTargetAnimTime = 0;
      LeftGreenAnim = 0;
      LeftGreenTargetAnimMode = BLINK_LEFT_GREEN_TARGET;
    }else if(byte0 == OFF_LEFT_GREEN_TARGET){
      if(duration > 0){LeftGreenTargetAnimMode_Old = LeftGreenTargetAnimMode;LeftGreenTargetAnimTime = duration;}
      else LeftGreenTargetAnimTime = 0;
      LeftGreenAnim = 0;
      LeftGreenTargetAnimMode = OFF_LEFT_GREEN_TARGET;
      
    //RIGHT GREEN TARGET--------------------------------------------------------
    }else if(byte0 == SNAKE_RIGHT_GREEN_TARGET){
      if(duration > 0){RightGreenTargetAnimMode_Old = RightGreenTargetAnimMode;RightGreenTargetAnimTime = duration;}
      else RightGreenTargetAnimTime = 0;
      RightGreenAnim = 1;
      RightGreenTargetAnimMode = SNAKE_RIGHT_GREEN_TARGET;
    }else if(byte0 == BLINK_RIGHT_GREEN_TARGET){
      if(duration > 0){RightGreenTargetAnimMode_Old = RightGreenTargetAnimMode;RightGreenTargetAnimTime = duration;}
      else RightGreenTargetAnimTime = 0;
      RightGreenAnim = 0;
      RightGreenTargetAnimMode = BLINK_RIGHT_GREEN_TARGET;
    }else if(byte0 == OFF_RIGHT_GREEN_TARGET){
      if(duration > 0){RightGreenTargetAnimMode_Old = RightGreenTargetAnimMode;RightGreenTargetAnimTime = duration;}
      else RightGreenTargetAnimTime = 0;
      RightGreenAnim = 0;
      RightGreenTargetAnimMode = OFF_RIGHT_GREEN_TARGET;
      
      //LEFT RED TARGETS--------------------------------------------------------------------
    }else if(byte0 == SNAKE_LEFT_RED_TARGET){
      if(duration > 0){LeftRedTargetAnimMode_Old = LeftRedTargetAnimMode; LeftRedTargetAnimTime = duration;}
      else LeftRedTargetAnimTime = 0;
      LeftRedAnim = 1;
      LeftRedTargetAnimMode = SNAKE_LEFT_RED_TARGET;
    }else if(byte0 == BLINK_LEFT_RED_TARGET){
      if(duration > 0){LeftRedTargetAnimMode_Old = LeftRedTargetAnimMode; LeftRedTargetAnimTime = duration;}
      else LeftRedTargetAnimTime = 0;
      LeftRedAnim = 0;
      LeftRedTargetAnimMode = BLINK_LEFT_RED_TARGET;
    }else if(byte0 == OFF_LEFT_RED_TARGET){
      if(duration > 0){LeftRedTargetAnimMode_Old = LeftRedTargetAnimMode; LeftRedTargetAnimTime = duration;}
      else LeftRedTargetAnimTime = 0;
      LeftRedAnim = 0;
      LeftRedTargetAnimMode = OFF_LEFT_RED_TARGET;
      
      //RIGHT RED TARGETS--------------------------------------------------------------------
    }else if(byte0 == SNAKE_RIGHT_RED_TARGET){
      if(duration > 0){RightRedTargetAnimMode_Old = RightRedTargetAnimMode; RightRedTargetAnimTime = duration;}
      else RightRedTargetAnimTime = 0;
      RightRedAnim = 1;
      RightRedTargetAnimMode = SNAKE_RIGHT_RED_TARGET;
    }else if(byte0 == BLINK_RIGHT_RED_TARGET){
      if(duration > 0){RightRedTargetAnimMode_Old = RightRedTargetAnimMode; RightRedTargetAnimTime = duration;}
      else RightRedTargetAnimTime = 0;
      RightRedAnim = 0;
      RightRedTargetAnimMode = BLINK_RIGHT_RED_TARGET;
    }else if(byte0 == OFF_RIGHT_RED_TARGET){
      if(duration > 0){RightRedTargetAnimMode_Old = RightRedTargetAnimMode; RightRedTargetAnimTime = duration;}
      else RightRedTargetAnimTime = 0;
      RightRedAnim = 0;
      RightRedTargetAnimMode = OFF_RIGHT_RED_TARGET;
      
      //YELLOW TARGETS-------------------------------------------------------------------
    }else if(byte0 == SNAKE_YELLOW_TARGET){
      if(duration > 0){YellowTargetAnimMode_Old = YellowTargetAnimMode; YellowTargetAnimTime = duration;}
      else YellowTargetAnimTime = 0;
      MiddleYellowAnim = 1;
      YellowTargetAnimMode = SNAKE_YELLOW_TARGET;
    }else if(byte0 == BLINK_YELLOW_TARGET){
      if(duration > 0){YellowTargetAnimMode_Old = YellowTargetAnimMode; YellowTargetAnimTime = duration;}
      else YellowTargetAnimTime = 0;
      MiddleYellowAnim = 0;
      YellowTargetAnimMode = BLINK_YELLOW_TARGET;
    }else if(byte0 == OFF_YELLOW_TARGET){
      if(duration > 0){YellowTargetAnimMode_Old = YellowTargetAnimMode; YellowTargetAnimTime = duration;}
      else YellowTargetAnimTime = 0;
      MiddleYellowAnim = 0;
      YellowTargetAnimMode = OFF_YELLOW_TARGET;
    
      //MODES-----------------------------------------------------------------------------------
    }else if(byte0 == ALL_MODE_OFF){
      if(duration > 0){ModesAnimMode_Old = ModesAnimMode; ModesAnimTime = duration;}
      else ModesAnimTime = 0;
      ModesAnim = 0;
      ModesAnimMode = ALL_MODE_OFF;
    }else if(byte0 == ALL_MODE_ON){
      if(duration > 0){ModesAnimMode_Old = ModesAnimMode; ModesAnimTime = duration;}
      else ModesAnimTime = 0;
      ModesAnim = 0b11111111;
      ModesAnimMode = ALL_MODE_ON;
    }else if(byte0 == MODE_3_BUMPERS){
      if(duration > 0){ModesAnimMode_Old = ModesAnimMode; ModesAnimTime = duration;}
      else ModesAnimTime = 0;
      ModesAnim = 64;
      ModesAnimMode = MODE_3_BUMPERS;      
    }else if(byte0 == MODE_5_MIDDLE){
      if(duration > 0){ModesAnimMode_Old = ModesAnimMode; ModesAnimTime = duration;}
      else ModesAnimTime = 0;
      ModesAnim = 32;
      ModesAnimMode = MODE_5_MIDDLE;      
    }else if(byte0 == MODE_GREEN_TARGETS){
      if(duration > 0){ModesAnimMode_Old = ModesAnimMode; ModesAnimTime = duration;}
      else ModesAnimTime = 0;
      ModesAnim = 16;
      ModesAnimMode = MODE_GREEN_TARGETS;      
    }else if(byte0 == MODE_EXTRA_BALL){
      if(duration > 0){ModesAnimMode_Old = ModesAnimMode; ModesAnimTime = duration;}
      else ModesAnimTime = 0;
      ModesAnim = 8;
      ModesAnimMode = MODE_EXTRA_BALL;      
    }else if(byte0 == MODE_ALL_TARGETS){
      if(duration > 0){ModesAnimMode_Old = ModesAnimMode; ModesAnimTime = duration;}
      else ModesAnimTime = 0;
      ModesAnim = 4;
      ModesAnimMode = MODE_ALL_TARGETS;      
    }else if(byte0 == MODE_DOUBLE){
      if(duration > 0){ModesAnimMode_Old = ModesAnimMode; ModesAnimTime = duration;}
      else ModesAnimTime = 0;
      ModesAnim = 2;
      ModesAnimMode = MODE_DOUBLE;     
    }else if(byte0 == MODE_RED_TARGETS){
      if(duration > 0){ModesAnimMode_Old = ModesAnimMode; ModesAnimTime = duration;}
      else ModesAnimTime = 0;
      ModesAnim = 1;
      ModesAnimMode = MODE_RED_TARGETS;      
    }else if(byte0 == MODE_PSIT){
      if(duration > 0){ModesAnimMode_Old = ModesAnimMode; ModesAnimTime = duration;}
      else ModesAnimTime = 0;
      ModesAnim = 128;
      ModesAnimMode = MODE_PSIT;      
    }else if(byte0 == SNAKE_MODES){
      if(duration > 0){ModesAnimMode_Old = ModesAnimMode; ModesAnimTime = duration;}
      else ModesAnimTime = 0;
      ModesAnim = 1;
      ModesAnimMode = SNAKE_MODES;     
    }else if(byte0 == BLINK_MODES){
      if(duration > 0){ModesAnimMode_Old = ModesAnimMode; ModesAnimTime = duration;}
      else ModesAnimTime = 0;
      ModesAnim = 0;
      ModesAnimMode = BLINK_MODES;
    
    //PSIT LETTERS
    }else if(byte0 == ALL_LETTERS_OFF){
      if(duration > 0){LettersAnimMode_Old = LettersAnimMode; LettersAnimTime = duration;}
      else LettersAnimTime = 0;
      Pletter = Sletter = Iletter = Tletter = 0;
      LettersAnimMode = ALL_LETTERS_OFF;
      
      PletterAnimMode = 0; PletterAnimMode_Old = 0;
      SletterAnimMode = 0; SletterAnimMode_Old = 0;
      IletterAnimMode = 0; IletterAnimMode_Old = 0;
      TletterAnimMode = 0; TletterAnimMode_Old = 0;
      
    }else if(byte0 == ALL_LETTERS_ON){
      if(duration > 0){LettersAnimMode_Old = LettersAnimMode; LettersAnimTime = duration;}
      else LettersAnimTime = 0;
      Pletter = Sletter = Iletter = Tletter = 1;
      LettersAnimMode = ALL_LETTERS_ON;
      
      PletterAnimMode = 0; PletterAnimMode_Old = 0;
      SletterAnimMode = 0; SletterAnimMode_Old = 0;
      IletterAnimMode = 0; IletterAnimMode_Old = 0;
      TletterAnimMode = 0; TletterAnimMode_Old = 0;
      
    }else if(byte0 == LETTER_P_ON){
      if(duration > 0){PletterAnimMode_Old = PletterAnimMode; PletterAnimTime = duration;}
      else PletterAnimTime = 0;
      Pletter = 1;
      PletterAnimMode = LETTER_P_ON;
      LettersAnimMode = 0; LettersAnimMode_Old = 0;
    }else if(byte0 == LETTER_S_ON){
      if(duration > 0){SletterAnimMode_Old = SletterAnimMode; SletterAnimTime = duration;}
      else SletterAnimTime = 0;
      Sletter = 1;
      SletterAnimMode = LETTER_S_ON;
      LettersAnimMode = 0; LettersAnimMode_Old = 0;
    }else if(byte0 == LETTER_I_ON){
      if(duration > 0){IletterAnimMode_Old = IletterAnimMode; IletterAnimTime = duration;}
      else IletterAnimTime = 0;
      Iletter = 1;
      IletterAnimMode = LETTER_I_ON;
      LettersAnimMode = 0; LettersAnimMode_Old = 0;
    }else if(byte0 == LETTER_T_ON){
      if(duration > 0){TletterAnimMode_Old = TletterAnimMode; TletterAnimTime = duration;}
      else TletterAnimTime = 0;
      Tletter = 1;
      TletterAnimMode = LETTER_T_ON;
      LettersAnimMode = 0; LettersAnimMode_Old = 0;
    }else if(byte0 == LETTER_P_OFF){
      if(duration > 0){PletterAnimMode_Old = PletterAnimMode; PletterAnimTime = duration;}
      else PletterAnimTime = 0;
      Pletter = 0;
      PletterAnimMode = LETTER_P_OFF;
      LettersAnimMode = 0; LettersAnimMode_Old = 0;
    }else if(byte0 == LETTER_S_OFF){
      if(duration > 0){SletterAnimMode_Old = SletterAnimMode; SletterAnimTime = duration;}
      else SletterAnimTime = 0;
      Sletter = 0;
      SletterAnimMode = LETTER_P_OFF;
      LettersAnimMode = 0; LettersAnimMode_Old = 0;
    }else if(byte0 == LETTER_I_OFF){
      if(duration > 0){IletterAnimMode_Old = IletterAnimMode; IletterAnimTime = duration;}
      else IletterAnimTime = 0;
      Iletter = 0;
      IletterAnimMode = LETTER_P_OFF;
      LettersAnimMode = 0; LettersAnimMode_Old = 0;
    }else if(byte0 == LETTER_T_OFF){
      if(duration > 0){TletterAnimMode_Old = TletterAnimMode; TletterAnimTime = duration;}
      else TletterAnimTime = 0;
      Tletter = 0;
      TletterAnimMode = LETTER_P_OFF;
      LettersAnimMode = 0; LettersAnimMode_Old = 0;
    }else if(byte0 == BLINK_LETTER_P){
      if(duration > 0){PletterAnimMode_Old = PletterAnimMode; PletterAnimTime = duration;}
      else PletterAnimTime = 0;
      Pletter = 1;
      PletterAnimMode = BLINK_LETTER_P;
      LettersAnimMode = 0; LettersAnimMode_Old = 0;
    }else if(byte0 == BLINK_LETTER_S){
      if(duration > 0){SletterAnimMode_Old = SletterAnimMode; SletterAnimTime = duration;}
      else SletterAnimTime = 0;
      Sletter = 1;
      SletterAnimMode = BLINK_LETTER_S;
      LettersAnimMode = 0; LettersAnimMode_Old = 0;
    }else if(byte0 == BLINK_LETTER_I){
      if(duration > 0){IletterAnimMode_Old = IletterAnimMode; IletterAnimTime = duration;}
      else IletterAnimTime = 0;
      Iletter = 1;
      IletterAnimMode = BLINK_LETTER_I;
      LettersAnimMode = 0; LettersAnimMode_Old = 0;
    }else if(byte0 == BLINK_LETTER_T){
      if(duration > 0){TletterAnimMode_Old = TletterAnimMode; TletterAnimTime = duration;}
      else TletterAnimTime = 0;
      Tletter = 1;
      TletterAnimMode = BLINK_LETTER_T;
      LettersAnimMode = 0; LettersAnimMode_Old = 0;
    }else if(byte0 == SNAKE_LETTERS){
      if(duration > 0){LettersAnimMode_Old = LettersAnimMode; LettersAnimTime = duration;}
      else LettersAnimTime = 0;
      LettersAnimMode = SNAKE_LETTERS;
      Pletter = 1;
      Sletter = Iletter = Tletter = 0;
     
      PletterAnimMode = 0; PletterAnimMode_Old = 0;
      SletterAnimMode = 0; SletterAnimMode_Old = 0;
      IletterAnimMode = 0; IletterAnimMode_Old = 0;
      TletterAnimMode = 0; TletterAnimMode_Old = 0;
     
    //BUMPER LIGHTS
    }else if(byte0 == ALL_BUMPERS_OFF){
      Bumper1Light = Bumper2Light = Bumper3Light = 0;
      Bumper1Mode = Bumper2Mode = Bumper3Mode = 0;
      Bumper1Mode_Old = Bumper2Mode_Old = Bumper3Mode_Old = 0;
      
    }else if(byte0 == ALL_BUMPERS_ON){
      Bumper1Light = Bumper2Light = Bumper3Light = 1;
      Bumper1Mode = 0; Bumper2Mode = 0; Bumper3Mode = 0;
      Bumper1Mode_Old = Bumper2Mode_Old = Bumper3Mode_Old = 0;    
      
    }else if(byte0 == BUMPER_1_ON){
      if(duration > 0){Bumper1Mode_Old = Bumper1Mode; Bumper1Time = duration;}
      else Bumper1Time = 0;
      Bumper1Light = 1;
      Bumper1Mode = BUMPER_1_ON;
    }else if(byte0 == BUMPER_2_ON){
      if(duration > 0){Bumper2Mode_Old = Bumper2Mode; Bumper2Time = duration;}
      else Bumper2Time = 0;
      Bumper2Light = 1;
      Bumper2Mode = BUMPER_2_ON;     
    }else if(byte0 == BUMPER_3_ON){
      if(duration > 0){Bumper3Mode_Old = Bumper3Mode; Bumper3Time = duration;}
      else Bumper3Time = 0;
      Bumper3Light = 1;
      Bumper3Mode = BUMPER_3_ON;    
    }else if(byte0 == BUMPER_1_OFF){
      if(duration > 0){Bumper1Mode_Old = Bumper1Mode; Bumper1Time = duration;}
      else Bumper1Time = 0;
      Bumper1Light = 0;
      Bumper1Mode = 0;
    }else if(byte0 == BUMPER_2_OFF){
      if(duration > 0){Bumper2Mode_Old = Bumper2Mode; Bumper2Time = duration;}
      else Bumper2Time = 0;
      Bumper2Light = 0;
      Bumper2Mode = 0;
    }else if(byte0 == BUMPER_3_OFF){
      if(duration > 0){Bumper3Mode_Old = Bumper3Mode; Bumper3Time = duration;}
      else Bumper3Time = 0;
      Bumper3Light = 0;
      Bumper3Mode = 0;      
    }else if(byte0 == BLINK_BUMPER_1){
      if(duration > 0){Bumper1Mode_Old = Bumper1Mode; Bumper1Time = duration;}
      else Bumper1Time = 0;
      Bumper1Light = 1;
      Bumper1Mode = BLINK_BUMPER_1;
    }else if(byte0 == BLINK_BUMPER_2){
      if(duration > 0){Bumper2Mode_Old = Bumper2Mode; Bumper2Time = duration;}
      else Bumper2Time = 0;
      Bumper2Light = 1;
      Bumper2Mode = BLINK_BUMPER_2;
    }else if(byte0 == BLINK_BUMPER_3){
      if(duration > 0){Bumper3Mode_Old = Bumper3Mode; Bumper3Time = duration;}
      else Bumper3Time = 0;
      Bumper3Light = 1;
      Bumper3Mode = BLINK_BUMPER_3;
      
    }else if(byte0 == SNAKE_BUMPERS){
      Bumper1Time = Bumper2Time = Bumper3Time = 0;
      Bumper1Light = 1;
      Bumper1Mode = Bumper2Mode = Bumper3Mode = SNAKE_BUMPERS;
      
     //GATE LIGHTS
    }else if(byte0 == ALL_GATES_ON){
      Gate1Light = Gate2Light = Gate3Light = 1;
    }else if(byte0 == ALL_GATES_OFF){
      Gate1Light = Gate2Light = Gate3Light = 0;
    }else if(byte0 == GATE_1_ON){
      Gate1Light = 1;
    }else if(byte0 == GATE_2_ON){
      Gate2Light = 1;
    }else if(byte0 == GATE_3_ON){
      Gate3Light = 1;
    }else if(byte0 == GATE_1_OFF){
      Gate1Light = 0;
    }else if(byte0 == GATE_2_OFF){
      Gate2Light = 0;
    }else if(byte0 == GATE_3_OFF){
      Gate3Light = 0;
      
    //LAUNCHER----------------------------------------------------------
    }else if(byte0 == LAUNCHER_OFF){
      if(duration > 0){ LauncherAnimMode_Old = LauncherAnimMode; LauncherAnimTime = duration;}
      else LauncherAnimTime = 0;
      LauncherAnim = 0;
      LauncherAnimMode = LAUNCHER_OFF;
    }else if(byte0 == SNAKE_LAUNCHER){
      if(duration > 0){ LauncherAnimMode_Old = LauncherAnimMode; LauncherAnimTime = duration;}
      else LauncherAnimTime = 0;
      LauncherAnim = 1;
      LauncherAnimMode = SNAKE_LAUNCHER;
      
    //LOOSE--------------------------------------------------------
    }else if(byte0 == LOOSE_OFF){
      if(duration > 0){ LooseAnimMode_Old = LooseAnimMode; LooseAnimTime = duration;}
      else LooseAnimTime = 0;
      LooseAnim = 0;
      LooseAnimMode = LOOSE_OFF;
    }else if(byte0 == BLINK_LOOSE){
      if(duration > 0){ LooseAnimMode_Old = LooseAnimMode; LooseAnimTime = duration;}
      else LooseAnimTime = 0;
      LooseAnim = 0;
      LooseAnimMode = BLINK_LOOSE;
      
    //KO1--------------------------------------------------
    }else if(byte0 == KO1_OFF){
      if(duration > 0){ KO1AnimMode_Old = KO1AnimMode; KO1AnimTime = duration;}
      else KO1AnimTime = 0;
      KO1Anim = 0;
      KO1AnimMode = KO1_OFF;
    }else if(byte0 == BLINK_KO1){
      if(duration > 0){ KO1AnimMode_Old = KO1AnimMode; KO1AnimTime = duration;}
      else KO1AnimTime = 0;
      KO1Anim = 0;
      KO1AnimMode = BLINK_KO1;
    }else if(byte0 == SNAKE_KO1){
      if(duration > 0){ KO1AnimMode_Old = KO1AnimMode; KO1AnimTime = duration;}
      else KO1AnimTime = 0;
      KO1Anim = 1;
      KO1AnimMode = SNAKE_KO1;
      
    //KO2--------------------------------------------------
    }else if(byte0 == KO2_OFF){
      if(duration > 0){ KO2AnimMode_Old = KO2AnimMode; KO2AnimTime = duration;}
      else KO2AnimTime = 0;
      KO2Anim = 0;
      KO2AnimMode = KO2_OFF;
    }else if(byte0 == BLINK_KO2){
      if(duration > 0){ KO2AnimMode_Old = KO2AnimMode; KO2AnimTime = duration;}
      else KO2AnimTime = 0;
      KO2Anim = 0;
      KO2AnimMode = BLINK_KO2;
    }else if(byte0 == SNAKE_KO2){
      if(duration > 0){ KO2AnimMode_Old = KO2AnimMode; KO2AnimTime = duration;}
      else KO2AnimTime = 0;
      KO2Anim = 1;
      KO2AnimMode = SNAKE_KO2;
    }
  }
}


void loop() {
    time++;

    byte dataToShifterA = (LeftGreenAnim & 0b00011111) | (Pletter << 5);
    digitalWrite(latchPinA, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, dataToShifterA);  
    digitalWrite(latchPinA, HIGH);
    
    byte dataToShifterB = (LeftRedAnim & 0b00011111) | (Sletter << 5);
    digitalWrite(latchPinB, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, dataToShifterB);  
    digitalWrite(latchPinB, HIGH);
    
    byte dataToShifterC = (MiddleYellowAnim & 0b00011111) | (Bumper1Light << 5) | (Bumper2Light << 6) | (Bumper3Light << 7);
    digitalWrite(latchPinC, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, dataToShifterC);  
    digitalWrite(latchPinC, HIGH);
    
    byte dataToShifterD = (RightRedAnim & 0b00011111) | (Iletter << 5);
    digitalWrite(latchPinD, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, dataToShifterD);  
    digitalWrite(latchPinD, HIGH);
    
    byte dataToShifterE = (RightGreenAnim & 0b00011111) | (Tletter << 5);
    digitalWrite(latchPinE, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, dataToShifterE);  
    digitalWrite(latchPinE, HIGH);
    
    digitalWrite(latchPinF, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, ModesAnim);  
    digitalWrite(latchPinF, HIGH);
    
    byte dataToShifterG = (LauncherAnim & 0b00011111) | (LooseAnim << 5);
    digitalWrite(latchPinG, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, dataToShifterG);  
    digitalWrite(latchPinG, HIGH);
    
    digitalWrite(latchPinH, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, FlashAnim);  
    digitalWrite(latchPinH, HIGH);
    
    byte dataToShifterI = (KO1Anim & 0b00011111) | (Gate1Light << 5) | (Gate2Light << 6) | (Gate3Light << 7);
    digitalWrite(latchPinI, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, dataToShifterI);  
    digitalWrite(latchPinI, HIGH);
    
    digitalWrite(latchPinJ, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, KO2Anim);  
    digitalWrite(latchPinJ, HIGH);
    
    delay(50);
    
    //Managing the anim mode frames
    if(allAnim){
      if(time%50 == 0){
        allAnimModeFrame++;
        allAnimModeState = 1;
        if(allAnimModeFrame == 4) allAnimModeFrame = 1;
        
        if(allAnimModeFrame == 1) SetAllAnim();
        else if(allAnimModeFrame == 2) allAnimMode = VERT_SNAKE_ALL;
        else if(allAnimModeFrame == 3) allAnimMode = VERT_SNAKE_KEEP_ALL;

      }
    }
    
    
    //ALL
    if(allAnimMode == VERT_SNAKE_ALL){
      if(allAnimModeState == 1){
        LooseAnim = 0b111;
      }else if(allAnimModeState == 2){
        LooseAnim = 0;
      }else if(allAnimModeState == 3){
        ModesAnim = 14;
      }else if(allAnimModeState == 4){
        ModesAnim = 241;
        KO2Anim = 0b11;
      }else if(allAnimModeState == 5){
        ModesAnim = 0;
        KO2Anim = 0b11100;
        MiddleYellowAnim = 1;
        LeftGreenAnim = RightGreenAnim = 0b111;
        LeftRedAnim = RightRedAnim = 0b1;
        Pletter = Sletter = Iletter = Tletter = 1;
        
      }else if(allAnimModeState == 6){
        KO2Anim = 0;
        MiddleYellowAnim = 0b11110;
        LeftGreenAnim = RightGreenAnim = 0b11000;
        LeftRedAnim = RightRedAnim = 0b11110;
        Pletter = Sletter = Iletter = Tletter = 0;
        
      }else if(allAnimModeState == 7){
        MiddleYellowAnim = 0;
        LeftGreenAnim = RightGreenAnim = 0;
        LeftRedAnim = RightRedAnim = 0;
        
      }else if(allAnimModeState == 8){
       Bumper2Light = Bumper3Light = 1;
        KO1Anim = 0b10000;
        
      }else if(allAnimModeState == 9){
        Bumper2Light = Bumper3Light = 0;
        Bumper1Light = 1;
        KO1Anim = 0b1111;
        
      }else if(allAnimModeState == 10){
        Bumper1Light = 0;
        KO1Anim = 0;
        Gate1Light = Gate2Light = Gate3Light = 1;
        
      }else if(allAnimModeState == 11){
        Gate1Light = Gate2Light = Gate3Light = 0;
        FlashAnim = 0b11111111;
      }else if(allAnimModeState == 12){
        FlashAnim = 0;
      }
      
      if(time%1 == 0){
        allAnimModeState++;
        if(allAnimModeState == 13) allAnimModeState = 1; 
      }
    }else if(allAnimMode == VERT_SNAKE_KEEP_ALL){
      if(allAnimModeState == 1){
        LooseAnim = 0b111;
      }else if(allAnimModeState == 3){
        ModesAnim = 14;
      }else if(allAnimModeState == 4){
        ModesAnim = 255;
        KO2Anim = 0b11;
      }else if(allAnimModeState == 5){
        KO2Anim = 0b11111;
        MiddleYellowAnim = 1;
        LeftGreenAnim = RightGreenAnim = 0b111;
        LeftRedAnim = RightRedAnim = 0b1;
        Pletter = Sletter = Iletter = Tletter = 1;
        
      }else if(allAnimModeState == 6){
        MiddleYellowAnim = 0b11111;
        LeftGreenAnim = RightGreenAnim = 0b11111;
        LeftRedAnim = RightRedAnim = 0b11111;
        
      }else if(allAnimModeState == 8){
       Bumper2Light = Bumper3Light = 1;
        KO1Anim = 0b10000;
        
      }else if(allAnimModeState == 9){
        Bumper1Light = 1;
        KO1Anim = 0b11111;
        
      }else if(allAnimModeState == 10){
        Gate1Light = Gate2Light = Gate3Light = 1;
        
      }else if(allAnimModeState == 11){
        FlashAnim = 0b11111111;
      }
      
      if(time%1 == 0){
        allAnimModeState++;
        if(allAnimModeState == 13) allAnimModeState = 1; 
      }
    }else if(allAnimMode == ALL_IDLE){
        
      //LAUNCHER---------------------------------------
      if(LauncherAnimMode == SNAKE_LAUNCHER){
          LauncherAnim = LauncherAnim << 1;
          if(LauncherAnim == 0) LauncherAnim = 1;
      }else if(LauncherAnimMode == LAUNCHER_OFF){
          LauncherAnim = 0;
      }
      if(LauncherAnimTime > 0){
         LauncherAnimTime--;
         if(LauncherAnimTime == 0){
           LauncherAnimMode = LauncherAnimMode_Old;
         } 
      }
  
      //LOOSE------------------------------------------------
      if(LooseAnimMode == BLINK_LOOSE ){
        if(time%1 == 0 ) LooseAnim = ~LooseAnim;
      }else if(LooseAnimMode == LOOSE_OFF ){
        LooseAnim = 0;
      }
      if(LooseAnimTime > 0){
         LooseAnimTime--;
         if(LooseAnimTime == 0){
           LooseAnimMode = LooseAnimMode_Old;
         } 
      }
      
      //GATES-----------------------------------------------------------------------
      
  
      
      //BUMPERS-----------------------------------------------------------------------
      if(Bumper1Mode == BUMPER_1_OFF) Bumper1Light = 0;
      else if(Bumper1Mode == BUMPER_1_ON) Bumper1Light = 1;
      else if(Bumper1Mode == BLINK_BUMPER_1){
        if(time%1 == 0) Bumper1Light = !Bumper1Light;
      }else if(Bumper1Mode == SNAKE_BUMPERS){
        if(BumperModeState == 1) Bumper1Light = 1;
        else Bumper1Light = 0;
      }
      if(Bumper1Time > 0){
         Bumper1Time--;
         if(Bumper1Time == 0){
           Bumper1Mode = Bumper1Mode_Old;
         } 
      }
      
      if(Bumper2Mode == BUMPER_2_OFF) Bumper2Light = 0;
      else if(Bumper2Mode == BUMPER_2_ON) Bumper2Light = 1;
      else if(Bumper2Mode == BLINK_BUMPER_2 && time%1 == 0) Bumper2Light = !Bumper2Light;
      else if(Bumper2Mode == SNAKE_BUMPERS){
        if(BumperModeState == 2) Bumper2Light = 1;
        else Bumper2Light = 0;
      }
      if(Bumper2Time > 0){
         Bumper2Time--;
         if(Bumper2Time == 0){
           Bumper2Mode = Bumper2Mode_Old;
         } 
      }
      
      if(Bumper3Mode == BUMPER_3_OFF) Bumper3Light = 0;
      else if(Bumper3Mode == BUMPER_3_ON) Bumper3Light = 1;
      else if(Bumper3Mode == BLINK_BUMPER_3 && time%1 == 0) Bumper3Light = !Bumper3Light;
      else if(Bumper3Mode == SNAKE_BUMPERS){
        if(BumperModeState == 3) Bumper3Light = 1;
        else Bumper3Light = 0;
      }
      if(Bumper3Time > 0){
         Bumper3Time--;
         if(Bumper3Time == 0){
           Bumper3Mode = Bumper3Mode_Old;
         } 
      }
      
      //Bumper Snake management
      if(time%2 == 0){
        BumperModeState++;
        if(BumperModeState == 4) BumperModeState = 1; 
      }
      // MODES----------------------------------------------------------------------
      if(ModesAnimMode == SNAKE_MODES){
        if(time%2 == 0 ) ModesAnim = ModesAnim << 1;
        if(ModesAnim == 0) ModesAnim = 1;
      }else if(ModesAnimMode == BLINK_MODES){
        if(time%2 == 0 ){
          ModesAnim = ~ModesAnim;
        }
      }else if(ModesAnimMode == MODE_3_BUMPERS){
        ModesAnim = 64;    
      }else if(ModesAnimMode == MODE_5_MIDDLE){
        ModesAnim = 32;     
      }else if(ModesAnimMode == MODE_GREEN_TARGETS){
        ModesAnim = 16;      
      }else if(ModesAnimMode == MODE_EXTRA_BALL){
        ModesAnim = 8;     
      }else if(ModesAnimMode == MODE_ALL_TARGETS){
        ModesAnim = 4;    
      }else if(ModesAnimMode == MODE_DOUBLE){
        ModesAnim = 2;    
      }else if(ModesAnimMode == MODE_RED_TARGETS){
        ModesAnim = 1;     
      }else if(ModesAnimMode == MODE_PSIT){
        ModesAnim = 128;
      }else if(ModesAnimMode == ALL_MODE_ON){
        ModesAnim = 0b11111111; 
      }else if(ModesAnimMode == ALL_MODE_OFF){
        ModesAnim = 0; 
      }
      if(ModesAnimTime > 0){
         ModesAnimTime--;
         if(ModesAnimTime == 0){
           ModesAnimMode = ModesAnimMode_Old;
         } 
      }
      
      //MIDDLE YELLOW --------------------------------------------------------------
      if(YellowTargetAnimMode == OFF_YELLOW_TARGET){
        MiddleYellowAnim = 0;   
      }else if(YellowTargetAnimMode == SNAKE_YELLOW_TARGET){
        MiddleYellowAnim = MiddleYellowAnim << 1;
        if(MiddleYellowAnim == 0) MiddleYellowAnim = 1;
      }else if(YellowTargetAnimMode == BLINK_YELLOW_TARGET){
        if(time%2 == 0 ) MiddleYellowAnim = ~MiddleYellowAnim;
      }
      if(YellowTargetAnimTime > 0){
         YellowTargetAnimTime--;
         if(YellowTargetAnimTime == 0){
           YellowTargetAnimMode = YellowTargetAnimMode_Old;
         } 
      }
      
      //LEFT GREEN TARGETS------------------------------------------------------------------
      if(LeftGreenTargetAnimMode == 0 || LeftGreenTargetAnimMode == OFF_LEFT_GREEN_TARGET){
        LeftGreenAnim = 0;
      }else if(LeftGreenTargetAnimMode == SNAKE_LEFT_GREEN_TARGET){
        LeftGreenAnim = LeftGreenAnim << 1;
        if(LeftGreenAnim == 0) LeftGreenAnim = 1;
      }else if(LeftGreenTargetAnimMode == BLINK_LEFT_GREEN_TARGET){
        if(time%2 == 0 ){
          LeftGreenAnim = ~LeftGreenAnim;
        }  
      }
      if(LeftGreenTargetAnimTime > 0){
         LeftGreenTargetAnimTime--;
         if(LeftGreenTargetAnimTime == 0){
           LeftGreenTargetAnimMode = LeftGreenTargetAnimMode_Old;
         } 
      }
      
      //RIGHT GREEN TARGETS------------------------------------------------------------------
      if(RightGreenTargetAnimMode == 0 || RightGreenTargetAnimMode == OFF_RIGHT_GREEN_TARGET){
        RightGreenAnim = 0;
      }else if(RightGreenTargetAnimMode == SNAKE_RIGHT_GREEN_TARGET){
        RightGreenAnim = RightGreenAnim << 1;
        if(RightGreenAnim == 0) RightGreenAnim = 1;
      }else if(RightGreenTargetAnimMode == BLINK_RIGHT_GREEN_TARGET){
        if(time%2 == 0 ){
          RightGreenAnim = ~RightGreenAnim;
        }  
      }
      if(RightGreenTargetAnimTime > 0){
         RightGreenTargetAnimTime--;
         if(RightGreenTargetAnimTime == 0){
           RightGreenTargetAnimMode = RightGreenTargetAnimMode_Old;
         } 
      }
      
      //LEFT RED TARGETS-------------------------------------------------------------------
      if(LeftRedTargetAnimMode == 0 || LeftRedTargetAnimMode == OFF_LEFT_RED_TARGET){
        LeftRedAnim = 0;
      }else if(LeftRedTargetAnimMode == SNAKE_LEFT_RED_TARGET){
        LeftRedAnim = LeftRedAnim << 1;
        if(LeftRedAnim == 0) LeftRedAnim = 1;
      }else if(LeftRedTargetAnimMode == BLINK_LEFT_RED_TARGET){
        if(time%2 == 0 ){
          LeftRedAnim = ~LeftRedAnim;
        }  
      }
      if(LeftRedTargetAnimTime > 0){
         LeftRedTargetAnimTime--;
         if(LeftRedTargetAnimTime == 0){
           LeftRedTargetAnimMode = LeftRedTargetAnimMode_Old;
         } 
      }
      
      //RIGHT RED TARGETS-------------------------------------------------------------------
      if(RightRedTargetAnimMode == 0 || RightRedTargetAnimMode == OFF_RIGHT_RED_TARGET){
        RightRedAnim = 0;
      }else if(RightRedTargetAnimMode == SNAKE_RIGHT_RED_TARGET){
        RightRedAnim = RightRedAnim << 1;
        if(RightRedAnim == 0) RightRedAnim = 1;
      }else if(RightRedTargetAnimMode == BLINK_RIGHT_RED_TARGET){
        if(time%2 == 0 ){
          RightRedAnim = ~RightRedAnim;
        }  
      }
      if(RightRedTargetAnimTime > 0){
         RightRedTargetAnimTime--;
         if(RightRedTargetAnimTime == 0){
           RightRedTargetAnimMode = RightRedTargetAnimMode_Old;
         } 
      }
  
      //FLASH ANIM-----------------------------------------------------------------
      if(FlashAnimMode == 0){
        FlashAnim = 0;
      }else if(FlashAnimMode == FLASH_TOP_LIGHTS){
        FlashAnim = ~FlashAnim;
      }else if(FlashAnimMode == ALTERN_TOP_LIGHTS){
        if(time%10 == 0 ) FlashAnim = ~FlashAnim;
      }else if(FlashAnimMode == LIGHT_TOP_LIGHTS){
        FlashAnim = 0b11111111;
      }else if(FlashAnimMode == DUAL_SNAKE_TOP_LIGHTS){
        if(FlashAnimSide) FlashAnim = FlashAnim << 1;
        else FlashAnim = FlashAnim >> 1;
        if(FlashAnim == 0b10000000 || FlashAnim == 1) FlashAnimSide = !FlashAnimSide;
      }else if(FlashAnimMode == OFF_TOP_LIGHTS){
        FlashAnim = 0;
      }
      if(FlashAnimTime > 0){
         FlashAnimTime--;
         if(FlashAnimTime == 0){
           FlashAnimMode = FlashAnimMode_Old;
         } 
      }
      
      //KO1 ---------------------------------------
      if(KO1AnimMode == BLINK_KO1 && time%1 == 0){
        KO1Anim = ~KO1Anim;
      }else if(KO1AnimMode == SNAKE_KO1){
        KO1Anim = KO1Anim << 1;
        if(KO1Anim == 0) KO1Anim = 1;
      }else if(KO1AnimMode == KO1_OFF){
        KO1Anim = 0;
      }
      if(KO1AnimTime > 0){
         KO1AnimTime--;
         if(KO1AnimTime == 0){
           KO1AnimMode = KO1AnimMode_Old;
         } 
      }
      
      //KO2 ---------------------------------------
      if(KO2AnimMode == BLINK_KO2 && time%1 == 0){
        KO2Anim = ~KO2Anim;
      }else if(KO2AnimMode == SNAKE_KO2){
        KO2Anim = KO2Anim << 1;
        if(KO2Anim == 0) KO2Anim = 1;
      }else if(KO2AnimMode == KO2_OFF){
        KO2Anim = 0;
      }
      if(KO2AnimTime > 0){
         KO2AnimTime--;
         if(KO2AnimTime == 0){
           KO2AnimMode = KO2AnimMode_Old;
         } 
      }
      
      //LETTERS---------------------------------------------------------------------
      if(LettersAnimMode == SNAKE_LETTERS){
        if(time%10 == 0){
          if(Pletter == 1){ Pletter = 0; Sletter = 1;}
          else if(Sletter == 1){ Sletter = 0; Iletter = 1;}
          else if(Iletter == 1){ Iletter = 0; Tletter = 1;}
          else if(Tletter == 1){ Tletter = 0; Pletter = 1;}
        }
      }else if(LettersAnimMode == ALL_LETTERS_ON){
        Pletter = Sletter = Iletter = Tletter = 1;
      }else if(LettersAnimMode == ALL_LETTERS_OFF){
        Pletter = Sletter = Iletter = Tletter = 0;
      }
      if(LettersAnimTime > 0){
         LettersAnimTime--;
         if(LettersAnimTime == 0){
           LettersAnimMode = LettersAnimMode_Old;
         } 
      }
      
      //LETTER P--------------------------------------------------
      if(PletterAnimMode == LETTER_P_ON){
        Pletter = 1;
      }else if(PletterAnimMode == LETTER_P_OFF){
        Pletter = 0;
      }else if(PletterAnimMode == BLINK_LETTER_P){
        if(time%10 == 0) Pletter = !Pletter;
      }
      if(PletterAnimTime > 0){
         PletterAnimTime--;
         if(PletterAnimTime == 0){
           PletterAnimMode = PletterAnimMode_Old;
         } 
      }
      
      //LETTER S--------------------------------------------------
      if(SletterAnimMode == LETTER_S_ON){
        Sletter = 1;
      }else if(SletterAnimMode == LETTER_S_OFF){
        Sletter = 0;
      }else if(SletterAnimMode == BLINK_LETTER_S){
        if(time%10 == 0) Sletter = !Sletter;
      }
      if(SletterAnimTime > 0){
         SletterAnimTime--;
         if(SletterAnimTime == 0){
           SletterAnimMode = SletterAnimMode_Old;
         } 
      }
      
      //LETTER I--------------------------------------------------
      if(IletterAnimMode == LETTER_I_ON){
        Iletter = 1;
      }else if(IletterAnimMode == LETTER_I_OFF){
        Iletter = 0;
      }else if(IletterAnimMode == BLINK_LETTER_I){
        if(time%10 == 0) Iletter = !Iletter;
      }
      if(IletterAnimTime > 0){
         IletterAnimTime--;
         if(IletterAnimTime == 0){
           IletterAnimMode = IletterAnimMode_Old;
         } 
      }
      
      //LETTER T--------------------------------------------------
      if(TletterAnimMode == LETTER_T_ON){
        Tletter = 1;
      }else if(TletterAnimMode == LETTER_T_OFF){
        Tletter = 0;
      }else if(TletterAnimMode == BLINK_LETTER_T){
        if(time%10 == 0) Tletter = !Tletter;
      }
      if(TletterAnimTime > 0){
         TletterAnimTime--;
         if(TletterAnimTime == 0){
           TletterAnimMode = TletterAnimMode_Old;
         } 
      }
    }
}

