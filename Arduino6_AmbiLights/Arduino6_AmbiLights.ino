#include <Wire.h>

#define RED_ON 1
#define RED_OFF 2
#define GREEN_ON 3
#define GREEN_OFF 4
#define YELLOW_ON 5
#define YELLOW_OFF 6
#define BLUE_ON 7
#define BLUE_OFF 8
#define ALL_ON 9
#define ALL_OFF 10
#define ANIME_ALL 11

#define WHITE_ON 12
#define WHITE_OFF 13
#define BOOST_ON 14
#define BOOST_OFF 15

#define FLASH_WHITE 100
#define SNAKE_ALL_COLORS 101


void setup() {
  // put your setup code here, to run once:
  
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  
  Wire.begin(6);
  Wire.onReceive(receiveEvent);
  
  Serial.begin(9600); 
  
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(7, HIGH);
  
  Boost(true);
  /*
  delay(1000);
  All(true); delay(2000);
  All(false); delay(2000);
  
  Red(true); delay(2000);
  Red(false); delay(2000);
  
  Green(true); delay(2000);
  Green(false); delay(2000);
  
  Yellow(true); delay(2000);
  Yellow(false); delay(2000);
  
  Blue(true); delay(2000);
  Blue(false); delay(2000);
  
  White(true); delay(2000);
  White(false); delay(2000);
  
  Blue(true); Red(true);delay(2000);
  Blue(false); Red(false);delay(2000);
  
  Blue(true); Yellow(true);delay(2000);
  Blue(false); Yellow(false);delay(2000);
  
  Red(true); Yellow(true);delay(2000);
  Red(false); Yellow(false);delay(2000);
  
  Red(true); Green(true);delay(2000);
  Red(false); Green(false);delay(2000);
  
  Yellow(true); Green(true);delay(2000);
  Yellow(false); Green(false);delay(2000);
  
  Boost(true);
  
  All(true); delay(2000);
  All(false); delay(2000);
  
  Red(true); delay(2000);
  Red(false); delay(2000);
  
  Green(true); delay(2000);
  Green(false); delay(2000);
  
  Yellow(true); delay(2000);
  Yellow(false); delay(2000);
  
  Blue(true); delay(2000);
  Blue(false); delay(2000);
  
  White(true); delay(2000);
  White(false); delay(2000);
  
  Blue(true); Red(true);delay(2000);
  Blue(false); Red(false);delay(2000);
  
  Blue(true); Yellow(true);delay(2000);
  Blue(false); Yellow(false);delay(2000);
  
  Red(true); Yellow(true);delay(2000);
  Red(false); Yellow(false);delay(2000);
  
  Red(true); Green(true);delay(2000);
  Red(false); Green(false);delay(2000);
  
  Yellow(true); Green(true);delay(2000);
  Yellow(false); Green(false);delay(2000);
 
  */

  
}
bool modeAnim = false;
bool modeSnake = false;
unsigned long time = 0;
short animMode = 0;

bool redState, blueState, greenState, yellowState, whiteState, boostState, animState;
bool redOldState, blueOldState, greenOldState, yellowOldState, whiteOldState, boostOldState, animOldState;

void Boost(bool activate){
  if(activate) digitalWrite(7, LOW);
  else digitalWrite(7, HIGH);
  boostState = activate;
}
void White(bool activate){
  if(activate) digitalWrite(8, LOW);
  else digitalWrite(8, HIGH);
  whiteState = activate;
}
void Red(bool activate){
  if(activate) digitalWrite(12, LOW);
  else digitalWrite(12, HIGH);
  redState = activate;
}
void Green(bool activate){
  if(activate) digitalWrite(11, LOW);
  else digitalWrite(11, HIGH);
  greenState = activate;
}
void Yellow(bool activate){
  if(activate) digitalWrite(10, LOW);
  else digitalWrite(10, HIGH);
  yellowState = activate;
}
void Blue(bool activate){
  if(activate) digitalWrite(9, LOW);
  else digitalWrite(9, HIGH);
  blueState = activate;
}
void receiveEvent(int howMany) {
  Serial.print("Event\n");
  animOldState = modeAnim;
  modeAnim = false;
  modeSnake = false;
  if(howMany == 1){
    byte byte0 = Wire.read();
    
    if(byte0 == RED_ON) Red(true);
    else if(byte0 == RED_OFF) Red(false);
    else if(byte0 == GREEN_ON) Green(true);
    else if(byte0 == GREEN_OFF) Green(false);
    else if(byte0 == YELLOW_ON) Yellow(true);
    else if(byte0 == YELLOW_OFF) Yellow(false);
    else if(byte0 == BLUE_ON) Blue(true);
    else if(byte0 == BLUE_OFF) Blue(false);
    else if(byte0 == WHITE_ON) White(true);
    else if(byte0 == WHITE_OFF) White(false);
    else if(byte0 == BOOST_ON) Boost(true);
    else if(byte0 == BOOST_OFF) Boost(false);
    else if(byte0 == ALL_ON){
      Red(true);
      Green(true);
      Yellow(true);
      Blue(true);
      White(true);
    }else if(byte0 == ALL_OFF){
      Red(false);
      Green(false);
      Yellow(false);
      Blue(false);
      White(false);
    }else if(byte0 == ANIME_ALL){
      modeAnim = true;
      time = 0;
      animMode = 0;
    }else if(byte0 == FLASH_WHITE){
      modeAnim = false;
      redOldState = redState; blueOldState = blueState; greenOldState = greenState; yellowOldState; whiteOldState = whiteState; boostOldState = boostState;
      
      
      byte flashNb = 20;
      
      All(false);
      Boost(true);
      while(flashNb > 1){
        if(flashNb%2 == 0) White(true);
        else White(false);
        delay(5000);
        flashNb --; 
      }
      
      //Restore previous State
      Boost(boostOldState);
      Red(redOldState);
      Green(greenOldState);
      Yellow(yellowOldState);
      Blue(blueOldState);
      White(whiteOldState);
      modeAnim = animOldState;
      
    }else if(byte0 == SNAKE_ALL_COLORS){
      modeSnake = true;
      
      animMode = 0;

      Boost(true);
      All(false);
      Red(true);
      
    }
    
  }
}
void All(bool activate){
  if(activate){
    Red(true);
    Green(true);
    Yellow(true);
    Blue(true);
    White(true);
  }else{
    Red(false);
    Green(false);
    Yellow(false);
    Blue(false);
    White(false);
  }
}

int randomTime = 0;
void loop() {
  
  if(modeAnim){
    delay(20);
    time++;
    if(time == 20 + randomTime){
      time = 0;
      if( animMode%2 ==0) Boost(true);
      else Boost(false);
      if(animMode == 0){
        All(true);
      }else if(animMode == 1){
        Green(false);
      }else if(animMode == 2){
        Green(true);
      }else if(animMode == 3){
        All(false);
        Green(true);
      }else if(animMode == 4){
        All(false);
        Red(true);
      }else if(animMode == 5){
        All(true);
      }else if(animMode == 6){
        All(false);
        Blue(true);
      }else if(animMode == 7){
        All(false);
        Yellow(true);
      }
      
      animMode = random(8);
      randomTime = 20 + random(100);
      //if(animMode == 8) animMode = 0;
    }
     
    
    
  }else if(modeSnake){
    time++;
    
    if(time%7000 == 0){
      animMode++;
      if(animMode == 5) animMode = 0;
    }
    if(animMode == 0){
      All(false);
      Red(true);
    }else if(animMode == 1){
      All(false);
      Blue(true);
    }else if(animMode == 2){
      All(false);
      Green(true);
    }else if(animMode == 3){
      All(false);
      Yellow(true);
    }else if(animMode == 4){
      All(false);
      White(true);
    }
    
  }
 
  
  }
