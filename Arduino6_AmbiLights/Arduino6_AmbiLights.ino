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

void setup() {
  // put your setup code here, to run once:
  
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  
  Wire.begin(6);
  Wire.onReceive(receiveEvent);
  
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(9, HIGH);
  
}
bool modeAnim = false;
unsigned long time = 0;
short animMode = 0;

void Red(bool activate){
  if(activate) digitalWrite(12, LOW);
  else digitalWrite(12, HIGH);
}
void Green(bool activate){
  if(activate) digitalWrite(11, LOW);
  else digitalWrite(11, HIGH);
}
void Yellow(bool activate){
  if(activate) digitalWrite(10, LOW);
  else digitalWrite(10, HIGH);
}
void Blue(bool activate){
  if(activate) digitalWrite(9, LOW);
  else digitalWrite(9, HIGH);
}
void receiveEvent(int howMany) {
  modeAnim = false;
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
    else if(byte0 == ALL_ON){
      Red(true);
      Green(true);
      Yellow(true);
      Blue(true);
    }else if(byte0 == ALL_OFF){
      Red(false);
      Green(false);
      Yellow(false);
      Blue(false);
    }else if(byte0 == ANIME_ALL){
      modeAnim = true;
      time = 0;
      animMode = 0;
    }
    
  }
}
void All(bool activate){
  if(activate){
    Red(true);
    Green(true);
    Yellow(true);
    Blue(true);
  }else{
    Red(false);
    Green(false);
    Yellow(false);
    Blue(false);
  }
}

int randomTime = 0;
void loop() {
  
  if(modeAnim){
    delay(20);
    time++;
    if(time == 20 + randomTime){
      time = 0;
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
     
    
    
  }
 
  
}
