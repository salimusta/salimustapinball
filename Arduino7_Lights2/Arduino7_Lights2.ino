#include <Wire.h>

#define ANIM_ALL 1
#define ALL_ANIM_OFF 2
#define VERT_SNAKE_ALL 81
#define ALL_IDLE 82
#define VERT_SNAKE_KEEP_ALL 83

#define RAMPGATE_OFF 10
#define RAMPGATE_SNAKE 11
#define RAMPGATE_BLINK 12
#define RAMPGATE_ON 13
#define RAMPGATE_DUAL_SNAKE 14
#define RAMPGATE_ALTERNATE 15

#define RAMP_OFF 20
#define RAMP_ON 21
#define RAMP_BLUE 22
#define RAMP_YELLOW 23
#define RAMP_SNAKE_BLUE 24
#define RAMP_SNAKE_YELLOW 25
#define RAMP_SNAKE 26
#define RAMP_BLINK 27
#define RAMP_ALTERNATE 28


int latchPinM = 13;
int latchPinN = 12;

int dataPin = 2;
int clockPin = 3;

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPinM, OUTPUT);
  pinMode(latchPinN, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  Serial.begin(9600); 
  
  Wire.begin(7);
  Wire.onReceive(receiveEvent);
  
 
}

//ALL param
byte allAnimModeState = 1;
byte allAnimMode = ALL_IDLE;
byte allAnimModeFrame = 0;
bool allAnim = false;
       
//RAMP GATE --------------------
byte RampGateAnim = 1;
byte RampGateAnimMode = RAMPGATE_DUAL_SNAKE;
byte RampGateAnimMode_Old = RAMPGATE_DUAL_SNAKE;
int RampGateAnimTime = 0;
byte RampGateData = 0;
bool RampGateSide = true; 
       
//RAMP-------------------------------
byte RampAnim = 1;
byte RampAnimMode = RAMP_SNAKE;
byte RampAnimMode_Old = RAMP_SNAKE;
int RampAnimTime = 0;
byte RampData = 0;

void ManageRampGateMode(byte duration){
  if(duration > 0){ 
    if(RampGateAnimTime == 0) RampGateAnimMode_Old = RampGateAnimMode;
    RampGateAnimTime = duration;
  }else RampGateAnimTime = 0;
}

void ManageRampMode(byte duration){
  if(duration > 0){ 
    if(RampAnimTime == 0) RampAnimMode_Old = RampAnimMode;
    RampAnimTime = duration;
  }else RampAnimTime = 0;
}

void SetAllAnim(){
  RampGateAnim = 1;
  RampGateAnimMode = RAMPGATE_SNAKE;
  
  RampAnim = 1;
  RampAnimMode = RAMP_SNAKE;
}

void SetAllOff(){
  RampGateAnim = 0;
  RampGateAnimMode = RAMPGATE_OFF;
  
  RampAnim = 0;
  RampAnimMode = RAMP_OFF;
}

void receiveEvent(int howMany) {
  byte duration = 0;
  byte data = 0;
  allAnim = false;
  //If 3 byte received, the third byte is the exact data to set.
  if(howMany == 1 || howMany == 2 || howMany == 3){
    byte byte0 = Wire.read();
    
    if(howMany > 1) duration = Wire.read();
    if(howMany > 2) data = Wire.read();
    
    allAnimMode = ALL_IDLE;
    
    if(byte0 == ALL_ANIM_OFF || byte0 == VERT_SNAKE_ALL || byte0 == VERT_SNAKE_KEEP_ALL){
      SetAllOff();
      
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
      allAnimMode = ALL_IDLE;
      SetAllAnim();

    //RAMP GATE MODE------------------------------------------------------
    }else if(byte0 == RAMPGATE_OFF){
      ManageRampGateMode(duration);
      
      RampGateAnim = 0;
      RampGateAnimMode = RAMPGATE_OFF;
      
    }else if(byte0 == RAMPGATE_SNAKE){
      ManageRampGateMode(duration);
      
      RampGateAnim = 1;
      RampGateAnimMode = RAMPGATE_SNAKE;
      
    }else if(byte0 == RAMPGATE_BLINK){
      ManageRampGateMode(duration);
      
      RampGateAnim = 0;
      RampGateAnimMode = RAMPGATE_BLINK;
      
    }else if(byte0 == RAMPGATE_ON){
      ManageRampGateMode(duration);
      
      RampGateAnim = 0b11111;
      RampGateAnimMode = RAMPGATE_ON;
      
    }else if(byte0 == RAMPGATE_DUAL_SNAKE){
      ManageRampGateMode(duration);
      
      RampGateAnim = 1;
      RampGateSide = true;
      RampGateAnimMode = RAMPGATE_DUAL_SNAKE;
      
    }else if(byte0 == RAMPGATE_ALTERNATE){
      ManageRampGateMode(duration);
      
      RampGateAnim = 0b01010;
      RampGateAnimMode = RAMPGATE_ALTERNATE;
    
    //RAMP MODE--------------------------------------------------
    }else if(byte0 == RAMP_OFF){
      ManageRampMode(duration);
      
      RampAnim = 0;
      RampAnimMode = RAMP_OFF;
      
    }else if(byte0 == RAMP_ON){
      ManageRampMode(duration);
      
      RampAnim = 0b11111111;
      RampAnimMode = RAMP_ON;
      
    }else if(byte0 == RAMP_BLUE){
      ManageRampMode(duration);
      
      RampAnim = 0b10101010;
      RampAnimMode = RAMP_BLUE;
      
    }else if(byte0 == RAMP_YELLOW){
      ManageRampMode(duration);
      
      RampAnim = 0b01010101;
      RampAnimMode = RAMP_YELLOW;
      
    }else if(byte0 == RAMP_SNAKE_BLUE){
      ManageRampMode(duration);
      
      RampAnim = 10;
      RampAnimMode = RAMP_SNAKE_BLUE;
      
    }else if(byte0 == RAMP_SNAKE_YELLOW){
      ManageRampMode(duration);
      
      RampAnim = 1;
      RampAnimMode = RAMP_SNAKE_YELLOW;
      
    }else if(byte0 == RAMP_SNAKE){
      ManageRampMode(duration);
      
      RampAnim = 1;
      RampAnimMode = RAMP_SNAKE;
      
    }else if(byte0 == RAMP_BLINK){
      ManageRampMode(duration);
      
      RampAnim = 0;
      RampAnimMode = RAMP_BLINK;
      
    }else if(byte0 == RAMP_ALTERNATE){
      ManageRampMode(duration);
      
      RampAnim = 0b10101010;
      RampAnimMode = RAMP_ALTERNATE;
      
    }
  }
}

       
int time = 0;


void loop() {
    time++;
    
    byte dataToShifterM = RampAnim;
    digitalWrite(latchPinM, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, dataToShifterM);  
    digitalWrite(latchPinM, HIGH);
    
    byte dataToShifterN = RampGateAnim;
    digitalWrite(latchPinN, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, dataToShifterN);  
    digitalWrite(latchPinN, HIGH);
    
    delay(50);
    
    //Managing the anim mode frames
    if(allAnim){
      if(time%80 == 0){
        allAnimModeFrame++;
        allAnimModeState = 1;
        if(allAnimModeFrame == 4) allAnimModeFrame = 1;
        
        if(allAnimModeFrame == 1) {
          allAnimMode = ALL_IDLE;
          SetAllAnim();
        }else if(allAnimModeFrame == 2) allAnimMode = VERT_SNAKE_ALL;
        else if(allAnimModeFrame == 3) allAnimMode = VERT_SNAKE_KEEP_ALL;

      }
    }
    
    //ALL
    if(allAnimMode == VERT_SNAKE_ALL){
      if(allAnimModeState == 1){
      }else if(allAnimModeState == 2){
      }else if(allAnimModeState == 3){
      }else if(allAnimModeState == 4){
      }else if(allAnimModeState == 5){
      }else if(allAnimModeState == 6){
      }else if(allAnimModeState == 7){
        RampAnim = 0b11111111;
      }else if(allAnimModeState == 8){
        RampAnim = 0;
        RampGateAnim = 0b11111;
      }else if(allAnimModeState == 9){
        RampGateAnim = 0;
      }else if(allAnimModeState == 10){
      }else if(allAnimModeState == 11){
      }else if(allAnimModeState == 12){
        
      }
      
      if(time%1 == 0){
        allAnimModeState++;
        if(allAnimModeState == 13) allAnimModeState = 1; 
      }
    }else if(allAnimMode == VERT_SNAKE_KEEP_ALL){
      if(allAnimModeState == 1){
        SetAllOff();
      }else if(allAnimModeState == 3){
      }else if(allAnimModeState == 4){
      }else if(allAnimModeState == 5){
      }else if(allAnimModeState == 6){
      }else if(allAnimModeState == 7){
        RampAnim = 0b11111111;
      }else if(allAnimModeState == 8){
        RampGateAnim = 0b11111; 
      }else if(allAnimModeState == 9){
      }else if(allAnimModeState == 10){
      }else if(allAnimModeState == 11){
      }
      
      if(time%1 == 0){
        allAnimModeState++;
        if(allAnimModeState == 13) allAnimModeState = 1; 
      }
      
    //All mode management
    }else if(allAnimMode == ALL_IDLE){
        
      //RAMP GATE MODE MANAGEMENT------------------------------------
      if(RampGateAnimMode == RAMPGATE_OFF){
        RampGateAnim = 0;
        
      }else if(RampGateAnimMode == RAMPGATE_SNAKE){
        RampGateAnim = RampGateAnim << 1;
        if(RampGateAnim == 0) RampGateAnim = 1;

      }else if(RampGateAnimMode == RAMPGATE_BLINK){
        if(time%1 == 0 ) RampGateAnim = ~RampGateAnim;
        
      }else if(RampGateAnimMode == RAMPGATE_ON){
        RampGateAnim = 0b11111;
        
      }else if(RampGateAnimMode == RAMPGATE_DUAL_SNAKE){
        if(RampGateSide) RampGateAnim = RampGateAnim << 1;
        else RampGateAnim = RampGateAnim >> 1;
        if(RampGateAnim == 0b10000000 || RampGateAnim == 1) RampGateSide = !RampGateSide;
        
      }else if(RampGateAnimMode == RAMPGATE_ALTERNATE){
        if(time%10 == 0 ) RampGateAnim = ~RampGateAnim;
      }
      
      if(RampGateAnimTime > 0){
         RampGateAnimTime--;
         if(RampGateAnimTime == 0){
           RampGateAnimMode = RampGateAnimMode_Old;
           if(RampGateAnimMode == RAMPGATE_ALTERNATE) RampGateAnim = 0b01010;
           else if(RampGateAnimMode == RAMPGATE_DUAL_SNAKE){
             RampGateAnim = 1;
             RampGateSide = true;
           }
         } 
      }
      
      //RAMP MODE MANAGEMENT -----------------------------------
  
      if(RampAnimMode == RAMP_OFF){
        RampAnim = 0;
        
      }else if(RampAnimMode == RAMP_ON){
        RampAnim = 0b11111111;
        
      }else if(RampAnimMode == RAMP_BLUE){
        RampAnim = 0b10101010;
        
      }else if(RampAnimMode == RAMP_YELLOW){
        RampAnim = 0b01010101;
        
      }else if(RampAnimMode == RAMP_SNAKE_BLUE){
        if(time%2 == 0) RampAnim = RampAnim << 2;
        if(RampAnim == 0) RampAnim = 10;
        
      }else if(RampAnimMode == RAMP_SNAKE_YELLOW){
        if(time%2 == 0)RampAnim = RampAnim << 2;
        if(RampAnim == 0) RampAnim = 1;
        
      }else if(RampAnimMode == RAMP_SNAKE){
        RampAnim = RampAnim << 1;
        if(RampAnim == 0) RampAnim = 1;
        
      }else if(RampAnimMode == RAMP_BLINK){
        if(time%1 == 0 ) RampAnim = ~RampAnim;
        
      }else if(RampAnimMode == RAMP_ALTERNATE){
        if(time%10 == 0 ) RampAnim = ~RampAnim;
        
      }         
    
      if(RampAnimTime > 0){
         RampAnimTime--;
         if(RampAnimTime == 0){
           RampAnimMode = RampAnimMode_Old;
         } 
      }  
    }
}

