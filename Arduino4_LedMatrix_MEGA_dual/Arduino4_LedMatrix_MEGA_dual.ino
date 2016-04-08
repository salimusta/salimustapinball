#include <Wire.h>
#include "defines.h"
#include "letters.h"

byte requestedScreen = SCREEN_SALIMUSTAPINBALL;
byte lowPriorityScreen = SCREEN_SALIMUSTAPINBALL;

unsigned char  tmpBmp[512];


unsigned long scoresTab[5] = {1000, 500, 133, 50, 5};
char highscoreName1[11] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', '\0'}; 
char highscoreName2[11] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', '\0'}; 
char highscoreName3[11] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', '\0'}; 
char highscoreName4[11] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', '\0'}; 
char highscoreName5[11] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', '\0'}; 
char name[11];
bool nameEntered = false;
bool nameEnterCanceled = false;
byte commandToSend = 0;
byte receivedBallNb = 0;
byte countdown = 0;
byte bumpersStatus = 0;
byte bumpersStatus_Old = 0;
byte psit_state = 0;
byte nb_hits = 0;
byte nb_hits_Old = 0;
byte flippers_state = 0;
byte start_state = 0;
byte currentPlayer = 0;
unsigned long score = 0;
unsigned long playersScore[4];
bool Old_leftFlipper = 0;
bool Old_rightFlipper = 0;

void setup()
{
  pinMode(LATCH_PIN,OUTPUT);
  pinMode(CLOCK_PIN,OUTPUT);
  pinMode(DATA_PIN,OUTPUT);
  
  pinMode(LATCH_PIN_2,OUTPUT);
  pinMode(CLOCK_PIN_2,OUTPUT);
  pinMode(DATA_PIN_2,OUTPUT);
  
  pinMode(en_74138,OUTPUT);
  pinMode(la_74138,OUTPUT);
  pinMode(lb_74138,OUTPUT);
  pinMode(lc_74138,OUTPUT);
  pinMode(ld_74138,OUTPUT);
  
  pinMode(en_74138_2,OUTPUT);
  pinMode(la_74138_2,OUTPUT);
  pinMode(lb_74138_2,OUTPUT);
  pinMode(lc_74138_2,OUTPUT);
  pinMode(ld_74138_2,OUTPUT);
  
  Serial.begin(9600); 
  
  Wire.begin(4);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  
  digitalWrite(en_74138, LOW);
  digitalWrite(en_74138_2, LOW);
  
}



short time = 0;
byte freq = 3;
short number = 0;
short x = 2;
short x2 = 2;
short y = 0;
short y2 = 0;
bool sensY;
bool flag;
short i;
byte nbPlayer = 1;

void loop(){
  
  //SCREEN_KO1_MULTIBALL
  time = 0;
  while(requestedScreen == SCREEN_KO1_MULTIBALL){
    time++;
    centerString(tmpBmp, "START MODE FOR", 3);
    centerString(tmpBmp, "MULTIBALL!", 19);
    
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
    if(time > 200) requestedScreen = lowPriorityScreen;
  }
  
  //SCREEN_SUPER_PSIT_COMPLETE
  time = 0;
  flag = true;
  while(requestedScreen == SCREEN_SUPER_PSIT_COMPLETE){
    time++;
  
    drawString(tmpBmp, "SUPER PSIT!", 1, 3, 50);
    if(flag) drawInvertRect(tmpBmp, 0, 0, 64, 16);
    if(time %3 == 0) flag = !flag;
    centerString(tmpBmp, "+10 000", 19);
    
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
    if(time > 200) requestedScreen = lowPriorityScreen;
  }
  //SCREEN_SUPER_PSIT
  while(requestedScreen == SCREEN_SUPER_PSIT){
    copyFrames(SuperPsit, tmpBmp);
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
  }
  
  //SCREEN_PLAYER_SELECTION
  if(requestedScreen == SCREEN_PLAYER_SELECTION) nbPlayer = 1;
  while(requestedScreen == SCREEN_PLAYER_SELECTION){
    drawSmallString(tmpBmp, "INSERT  CREDIT", 2, 4, 50); 
    
    drawString(tmpBmp, "1", 5, 19, 50);
    drawString(tmpBmp, "2", 21, 19, 50);
    drawString(tmpBmp, "3", 37, 19, 50);
    drawString(tmpBmp, "4", 53, 19, 50);

    bool leftFlipper = flippers_state & 1;
    bool rightFlipper = (flippers_state & 2) >> 1;
    
    if(leftFlipper == 0 && leftFlipper != Old_leftFlipper){
      if(nbPlayer > 1) nbPlayer--;
    }
    if(rightFlipper == 0 && rightFlipper != Old_rightFlipper){
      if(nbPlayer < 4) nbPlayer++;
    }
    
    drawInvertRect(tmpBmp, 3+(nbPlayer-1)*16, 16, 11, 15);

    Old_leftFlipper = leftFlipper;
    Old_rightFlipper = rightFlipper;
    
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
  }
  
  EmptyMatrix(tmpBmp);
  //nbPlayer = 4;
  //playersScore[0]=12345;
  while(requestedScreen == SCREEN_PLAYER_SCORES){
    for(byte k = 0; k < nbPlayer ; k++){
      char bufPlayer[8];
      char bufScore[5];
      sprintf(bufPlayer, "PLAYER %d", k + 1);
      sprintf(bufScore, "%lu", playersScore[k]);
      drawSmallString(tmpBmp, bufPlayer, 0, k*8, 50);
      drawSmallString(tmpBmp, bufScore, 40, k*8, 50);
    }
    
    byte best = 0;
    for(byte k = 0; k < nbPlayer ; k++){
      if(playersScore[k] > playersScore[best]) best = k;
    }
    
    //Highlist winning player
    //drawInvertRect(tmpBmp, 0, 0, 64, 9);
     
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
  }
  
  //SCREEN_PLAYER_WIN--------------------------------------
  EmptyMatrix(tmpBmp);
  while(requestedScreen == SCREEN_PLAYER_WIN){
    byte best = 0;
    for(byte k = 0; k < nbPlayer ; k++){
      if(playersScore[k] > playersScore[best]) best = k;
    }
    char buf[8];
    sprintf(buf, "PLAYER %d", best + 1);
    centerString(tmpBmp, buf, 2);
    centerString(tmpBmp, "WIN!", 19);
     
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
  }
  
  
  EmptyMatrix(tmpBmp);
  time = 0;
  flag = false;
  while(requestedScreen == SCREEN_STARWARS_WIN){
    time++;
    centerString(tmpBmp, "YOU WIN!", 3);
    centerString(tmpBmp, "+3000", 19);
    if(time%5 == 0) flag = !flag; 
    if(flag) drawInvertRect(tmpBmp, 0, 0, 64, 32);
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
    if(time > 100) requestedScreen = lowPriorityScreen;
  }
  
  //FRAME SCREEN_STARWARS_LOST
  while(requestedScreen == SCREEN_STARWARS_LOST){
    copyFrames(StarWarsLoose, tmpBmp);
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
  }
  
  //FRAME SCREEN_STARWARS_INTRO_2
  while(requestedScreen == SCREEN_STARWARS_INTRO_2){
    drawSmallString(tmpBmp, "A  LONG  TIME", 0, 0, 50);
    drawSmallString(tmpBmp, "AGO  IN  A", 0, 8, 50);
    drawSmallString(tmpBmp, "GALAXY  FAR", 0, 16, 50);
    drawSmallString(tmpBmp, "FAR  AWAY...", 0, 24, 50);
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
  }
  
  short explosionFrameIndex = 0;
  short shipExplosionFrameIndex = 0;
  time = 0;
  short ship_y = 16, ship_x = 0;
  short enemi_x = 130;
  short enemi_y = 16;
  short enemi_vy = 1;
  short laser_x = -5, laser_y = 16;
  short exploding = false;
  short shipExploding = false;
  short starsX[10];
  short starsY[10];
  commandToSend = 0;
  short nbShips = 3;
  short nbEnemiDestroyed = 0;
  bool gameWin = false;
  for(i = 0; i < 10; i++){
    randomSeed(analogRead(0));
    starsX[i] = random(64);
    starsY[i] = random(32);
  }
  //FRAME STAR WARS INTRO-------------------------------
  while(requestedScreen == SCREEN_STARWARS_GAME){
    time++;
    
    //Read the Button States
    bool leftFlipper = flippers_state & 1;
    bool rightFlipper = (flippers_state & 2) >> 1;
    
    if(time%5 == 0) explosionFrameIndex++;
    if(explosionFrameIndex == 5) explosionFrameIndex = 0;
    
    //Star moves
    
    for(short i = 0; i < 10; i++){
      starsX[i]--;
      if(starsX[i] < 0 ){
        randomSeed(analogRead(0));
        starsX[i] = 64+ random(20);
        starsY[i] = random(32);
      }
    }
  
    //enemi move
     if(!exploding && !shipExploding && !gameWin){
       enemi_x--;
       //if(time%2 ==0 ) enemi_y += enemi_vy;
       if(enemi_x < -10){
         enemi_x = 70;
         randomSeed(analogRead(0));
         enemi_y = 4 + random(25);
       }
     }
       
    //Move the main ship
    if(time%2 == 0 && !gameWin){
       if(leftFlipper == 1) ship_y--;
       if(rightFlipper == 1) ship_y++;
       
       if(ship_y > 32) ship_y = 32;
       if(ship_y < 0) ship_y = 0;
       
       
       if(enemi_y < 4){
         enemi_vy = enemi_vy*-1;
         enemi_y = 4;
       }
       if(enemi_y > 28){
         enemi_vy = enemi_vy*-1;
         enemi_y = 28;
       }
       
       //move the laser
       if(laser_x < 80) laser_x+=5;
    }
    
    //Fire a laser
    if(time%30 == 0 && !exploding && !shipExploding && !gameWin){
      laser_x = 10;
      laser_y = ship_y-1;
      SendCommandToMaster(LASER_SHOT);
    }
    
    //Colisions management
    if( !exploding && enemi_x < 64 && laser_x + 3 >= enemi_x-5 && laser_x <= enemi_x+5 && laser_y >= enemi_y-5 && laser_y < enemi_y+5){
      exploding = true;
      laser_y = -20;
      explosionFrameIndex = 0;
      shipExplosionFrameIndex = 0;
      SendCommandToMaster(ENEMI_DESTROYED);
      nbEnemiDestroyed++;
    }else if(!shipExploding && enemi_x-5 < 14 && enemi_y+5 > ship_y-8 && enemi_y-5 < ship_y +8){
      shipExploding = true;
      exploding = true;
      explosionFrameIndex = 0;
      shipExplosionFrameIndex = 0;
      nbShips--;
      SendCommandToMaster(SHIP_DESTROYED);
    } 
    
    if(time%5 == 0 && exploding ){
      explosionFrameIndex++;
      if(explosionFrameIndex == 5){
        if(nbEnemiDestroyed < 10){
          explosionFrameIndex = 0;
          enemi_x = 100;
          exploding = false;
          randomSeed(analogRead(0));
          enemi_y = 4 + random(25);
        }else{
          SendCommandToMaster(GAME_WIN);
          gameWin = true;
          exploding = false;
          explosionFrameIndex = 0;
          enemi_x = 100;
          time = 0;
        }
        
      }
    }
    
    if(time%5 == 0 && shipExploding){
      shipExplosionFrameIndex++;
      if(shipExplosionFrameIndex == 30){
        if(nbShips > 0){
          shipExplosionFrameIndex = 0;
          enemi_x = 100;
          ship_y = 16;
          shipExploding = false;
          randomSeed(analogRead(0));
          enemi_y = 4 + random(25);
        }else{
          SendCommandToMaster(GAME_LOST);
        }
      }
    }
    
    //Screen out
    if(gameWin && time > 50){
      if(time%2 ==0){
        if(ship_y < 16) ship_y--;
        if(ship_y > 16) ship_y++;
        if(ship_x < 80) ship_x+=2;
      }
    }
    
    //Draw the gameplay
    if(leftFlipper || rightFlipper) drawBigMotif(tmpBmp, ship[1], 0, ship_y - 8, 16, 15);
    else if(!shipExploding) drawBigMotif(tmpBmp, ship[0], ship_x, ship_y - 8, 16, 15);
    else if(shipExplosionFrameIndex < 7) drawVeryBigMotif(tmpBmp, shipExplosion[shipExplosionFrameIndex], 0, ship_y - 16, 32, 32);
    
    drawMotif(tmpBmp, laser, laser_x, laser_y, 3, 1);
    
    if(!exploding) drawBigMotif(tmpBmp, enemi, enemi_x-5, enemi_y-5, 10, 10);
    else if(explosionFrameIndex < 5) drawBigMotif(tmpBmp, explosion[explosionFrameIndex], enemi_x-10, enemi_y-10, 20, 20);
    
    for(short i = 0; i < 10; i++){
      drawMotif(tmpBmp, star, starsX[i], starsY[i], 1, 1);
    }

    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
  }
  
  time = 0;
  y = 34;
  x = -50;
  flag = true;
  //FRAME STAR WARS INTRO-------------------------------
  while(requestedScreen == SCREEN_STARWARS_INTRO){
    time++;
    if(flag){
      if(time < 600){
        copyFrames(StarWarsScreen, tmpBmp);
      }else{
        if(time%8 == 0) y--;
        drawSmallString(tmpBmp, "THE FORCE IS", 0, y, 50);
        drawSmallString(tmpBmp, "BACK. USE THE", 0, y+9, 50);
        drawSmallString(tmpBmp, "LEFT AND RIGHT", 0, y+18, 50);
        drawSmallString(tmpBmp, "BUTTONS TO", 0, y+27, 50);
        drawSmallString(tmpBmp, "MOVE YOUR SHIP", 0, y+36, 50);
        drawSmallString(tmpBmp, "YOU HAVE 3LIVES", 0, y+45, 50);
        drawSmallString(tmpBmp, "DESTROY", 0, y+54, 50);
        drawSmallString(tmpBmp, "10  ENEMIES...", 0, y+63, 50);
        if(flag && y < -80){
          flag = false;
          time = 0;
        }
      }
    }else{
      randomSeed(analogRead(0));
      for(short i = 0; i < 10; i++){
        starsX[i]--;
        if(starsX[i] < 0 ){
          starsX[i] = 64+ random(20);
          starsY[i] = random(32);
        }
      }
    
      for(short i = 0; i < 10; i++){
        drawMotif(tmpBmp, star, starsX[i], starsY[i], 1, 1);
      }
      
      if(time > 20){
        drawBigMotif(tmpBmp, ship[0], x, 8, 16, 15);
        if(x < 0 && time%3 == 0) x++;
      }
    }
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
  }
  
  //FRAME SALIMUSTA PINBALL
  time = 0;
  short floconX[3], floconY[3];
  randomSeed(analogRead(0));
  for(i = 0; i < 3 ; i++){
    floconX[i] = random(64);
    floconY[i] = 0 - random(80);
  }
  while(requestedScreen == SCREEN_SALIMUSTAPINBALL){
    time ++;
    if(time < 200){
      copyFrames(SalimUstaPinballFullBmp, tmpBmp);
    }else{
      centerString(tmpBmp, "JOYEUX",2);
      centerString(tmpBmp, "NOEL!",19);
      
      if(time%2 == 0){
        for(i = 0; i < 3 ; i++){
          floconY[i]++;
          if( floconY[i] > 40){
            floconX[i] = random(64);
            floconY[i] = 0 - random(80);
          }
        }
      }
      
      drawBigMotif(tmpBmp, flocons[0], floconX[0]-5, floconY[0]-5, 11, 11);
      drawBigMotif(tmpBmp, flocons[1], floconX[1]-5, floconY[1]-5, 11, 11);
      drawBigMotif(tmpBmp, flocons[2], floconX[2]-5, floconY[2]-5, 11, 11);
      
    }
    
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
  }
  

  //FRAME GET READY !--------------------------------------------------
  x = -64;
  time = 0;
  while(requestedScreen == SCREEN_GETREADY){
    time++;
    if(nbPlayer > 1){
      char buf[8];
      sprintf(buf, "PLAYER %d", currentPlayer + 1 );
      centerString(tmpBmp, buf, 2);
    }
    if(nbPlayer > 1) drawString(tmpBmp, "GET READY", x, 19, 50);
    else drawString(tmpBmp, "GET READY", x, 11, 50);
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
    if(x < 5 && time < 200) x++;
    else if(x < 65 && time > 200) x++;
    else if(time >= 400){
     time = 0;
      x = -64; 
    }
  }
  
  //FRAME GO!!!----------------------------------------------------------------
  flag = true;
  time = 0;
  while(requestedScreen == SCREEN_GO){
    time++;
    if(nbPlayer > 1){
      char buf[8];
      sprintf(buf, "PLAYER %d", currentPlayer + 1 );
      centerString(tmpBmp, buf, 2);
    }else drawString(tmpBmp, "START !", 10, 3, 50);
    
    drawString(tmpBmp, "START !", 10, 19, 50);
    if(flag) drawInvertRect(tmpBmp, 0, 0, 64, 32);
    if(time > 2){
      time = 0;
      flag = !flag;
    }
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
  }
  
  //FRAME MULTIBALL-----------------------------------------------------------------
  time = 0;
  flag = true;
  while(requestedScreen == SCREEN_MULTIBALL){
    time++;
    drawString(tmpBmp, "M U L T I", 11, 3, 50);
    drawString(tmpBmp, "B A L L", 14, 19, 50);
    if(flag) drawInvertRect(tmpBmp, 0, 0, 64, 32);
    if(time %3 == 0) flag = !flag;
    
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
    if(time > 100) requestedScreen = lowPriorityScreen;
  }
  
 
  //FRAME x ball left------------------------------------------------------------
  while(requestedScreen == SCREEN_BALLLEFT){
    if(receivedBallNb == 0) drawString(tmpBmp, "0", 16, 3, 50);
    else if(receivedBallNb == 1) drawString(tmpBmp, "1", 16, 3, 50);
    else if(receivedBallNb == 2) drawString(tmpBmp, "2", 16, 3, 50);
    else if(receivedBallNb == 3) drawString(tmpBmp, "3", 16, 3, 50);
    if(receivedBallNb > 1) drawString(tmpBmp, " BALLS", 25, 3, 50);
    else drawString(tmpBmp, " BALL", 25, 3, 50);
    centerString(tmpBmp, "LEFT", 19);
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
  }
  
  //FRAME GAME OVER------------------------------------------------------------------------
  while(requestedScreen == SCREEN_GAMEOVER){
    centerString(tmpBmp, "GAME OVER", 3);
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
  }
  
  //FRAME FULL------------------------------------------------------------------------------
  while(requestedScreen == SCREEN_FULL){
    for(short i = 0; i<512; i++){
      tmpBmp[i] = 0xFF;
    }
    DisplayMatrix(tmpBmp);
  }
  
  //FRAME YOU HAVE----------------------------------------------------------------------------------
  y = 33;
  while(requestedScreen == SCREEN_YOUHAVE){
    centerString(tmpBmp, "YOU HAVE", y);
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
    if(y > 11) y--;
    
  }
  
  //FRAME X BALLS-----------------------------------------------------------------------------
  y = -20;
  while(requestedScreen == SCREEN_XBALLS){
    centerString(tmpBmp, "3 BALLS", y);
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
    if(y < 11) y++; 
  }
  
  
  //FRAME SCORE--------------------------------------------------------------------------
  while(requestedScreen == SCREEN_SCORE){
    if(nbPlayer == 1) centerString(tmpBmp, "SCORE", 11);
    else{
      char buf[8];
      sprintf(buf, "PLAYER %d", currentPlayer + 1 );
      centerString(tmpBmp, buf, 2);
      centerString(tmpBmp, "SCORE", 19);
    }
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
  }
  
  //SCREEN_BALL_INTO_HOLE----------------------------------------------------------------------
  x = -20;
  time = 0;
  short nbLetterShown = 0;
  while(requestedScreen == SCREEN_BALL_INTO_HOLE){
    drawString(tmpBmp, "BALL LOST", 4, 3, nbLetterShown);
    drawMotif(tmpBmp, ball, x, 20, 7, 7);
    drawMotif(tmpBmp, hole, 55, 19, 8, 8);
    
    if(time > 10){
     time = 0;
     nbLetterShown++;
    }
    if(x < 55) x++;
    else time++;
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
  }
  
  //FRAME SCREEN_ROSW1---------------------------------------------------------------------------------
  time = 0;
  EmptyMatrix(tmpBmp);
  y = -10;
  while(requestedScreen == SCREEN_ROSW1){
    time++;

    drawMotif(tmpBmp, ball, 17, y, 7, 7);
    drawMotif(tmpBmp, gate, 12, 19, 5, 10);
    drawMotif(tmpBmp, gate, 24, 19, 5, 10);
    drawMotif(tmpBmp, gate, 36, 19, 5, 10);
    drawMotif(tmpBmp, gate, 48, 19, 5, 10);
    if(time%2 == 0 ) y++;

    if(time<70) centerString(tmpBmp, "GATE 1!", 2);
    else centerString(tmpBmp, "100 POINTS", 2);

    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
    if(time > 100) requestedScreen = lowPriorityScreen;
  }
  
  //FRAME SCREEN_ROSW2---------------------------------------------------------------------------
  time = 0;
  EmptyMatrix(tmpBmp);
  y = -10;
  while(requestedScreen == SCREEN_ROSW2){
    time++;

    drawMotif(tmpBmp, ball, 29, y, 7, 7);
    drawMotif(tmpBmp, gate, 12, 19, 5, 10);
    drawMotif(tmpBmp, gate, 24, 19, 5, 10);
    drawMotif(tmpBmp, gate, 36, 19, 5, 10);
    drawMotif(tmpBmp, gate, 48, 19, 5, 10);
    if(time%2 == 0 ) y++;

    if(time<70) centerString(tmpBmp, "GATE 2!", 2);
    else centerString(tmpBmp, "200 POINTS", 2);

    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
    if(time > 100) requestedScreen = lowPriorityScreen;
  }
  
  //FRAME SCREEN_ROSW3---------------------------------------------------------------------
  time = 0;
  EmptyMatrix(tmpBmp);
  y = -10;
  while(requestedScreen == SCREEN_ROSW3){
    time++;

    drawMotif(tmpBmp, ball, 41, y, 7, 7);
    drawMotif(tmpBmp, gate, 12, 19, 5, 10);
    drawMotif(tmpBmp, gate, 24, 19, 5, 10);
    drawMotif(tmpBmp, gate, 36, 19, 5, 10);
    drawMotif(tmpBmp, gate, 48, 19, 5, 10);
    if(time%2 == 0 ) y++;

    if(time<70) centerString(tmpBmp, "GATE 3!", 2);
    else centerString(tmpBmp, "300 POINTS", 2);

    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
    if(time > 100) requestedScreen = lowPriorityScreen;
  }
  
  //SCREEN_MIDDLE_SHOT-------------------------------------------------------------------
  EmptyMatrix(tmpBmp);
  x = 0;
  time = 0;
  flag = false;
  while(requestedScreen == SCREEN_MIDDLE_SHOT){
    time++;
    if(x < 30){
      drawMotif(tmpBmp, targetLeft, 25-x, 9, 7, 14);
      drawMotif(tmpBmp, targetRight, 32+x, 9, 7, 14);
      if(time > 10){
       if(x < 50) x++; 
      }
    }else{
      centerString(tmpBmp, "MIDDLE", 3);  
      centerString(tmpBmp, "! SHOT !", 19);  
      if(time%3 == 0) flag = !flag; 
    }
    if(flag) drawInvertRect(tmpBmp, 0, 0, 64, 32);
    
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
    if(time > 80) requestedScreen = lowPriorityScreen;
  }
  
  //RED SHOT----------------------------------------------------------------------------
  EmptyMatrix(tmpBmp);
  time = 0;
  flag = false;
  while(requestedScreen == SCREEN_RED_SHOT){
    time++;
    centerString(tmpBmp, "RED SHOT!", 11);  
    if(time%4 == 0) flag = !flag; 
    if(flag) drawInvertRect(tmpBmp, 0, 0, 64, 32);
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
    if(time > 80) requestedScreen = lowPriorityScreen;
  }
  
  //GREEN SHOT--------------------------------------------------------------------
  EmptyMatrix(tmpBmp);
  time = 0;
  flag = false;
  while(requestedScreen == SCREEN_GREEN_SHOT){
    time++;
    centerString(tmpBmp, "GREEN", 3);  
    centerString(tmpBmp, "SHOT!", 19);  
    if(time%3 == 0) flag = !flag; 
    if(flag) drawInvertRect(tmpBmp, 0, 0, 64, 32);
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
    if(time > 80) requestedScreen = lowPriorityScreen;
  }
  
  //3 BUMPERS MODE----------------------------------------------
  EmptyMatrix(tmpBmp);
  x = -64;
  x2 = 82;
  time = 0;
  while(requestedScreen == SCREEN_3BUMPERS_MODE){
    time++;
    drawString(tmpBmp, "3 BUMPERS", x, 3, 50);
    drawString(tmpBmp, "MODE", x2, 19, 50);
    
    if(x < 3) x++;
    if(x2 > 15) x2--;
    
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
    if(time > 250) requestedScreen = lowPriorityScreen;
  }
  
  time = 50;
  flag = false;
  while(requestedScreen == SCREEN_3BUMPERS_MODE_STATE){
    
    if(bumpersStatus != bumpersStatus_Old){
      time = 0;
    }
    bumpersStatus_Old = bumpersStatus;
    if(time < 50){
      time++;
      if(time%3 == 0) flag = !flag;
    }else flag = false;
    
    char buf[2];
    sprintf(buf, "%d", countdown);
    drawString(tmpBmp, buf, 2, 3, 50);
    
    if((bumpersStatus & 0b010) >> 1 == 1){
      drawMotif(tmpBmp, bigHoleLeft, 20, 17, 7, 14);
      drawMotif(tmpBmp, bigHoleRight, 27, 17, 7, 14);
    }else{
      drawMotif(tmpBmp, bigCercleLeft, 20, 17, 7, 14);
      drawMotif(tmpBmp, bigCercleRight, 27, 17, 7, 14);
      drawMotif(tmpBmp, number2, 24, 18, 7, 11);
    }
    
    if(bumpersStatus & 0b001 == 1){
      drawMotif(tmpBmp, bigHoleLeft, 35, 1, 7, 14);
      drawMotif(tmpBmp, bigHoleRight, 42, 1, 7, 14);
    }else{
      drawMotif(tmpBmp, bigCercleLeft, 35, 1, 7, 14);
      drawMotif(tmpBmp, bigCercleRight, 42, 1, 7, 14);
      drawMotif(tmpBmp, number1, 39, 2, 7, 11);
    }
    
    if((bumpersStatus & 0b100) >> 2 == 1){
      drawMotif(tmpBmp, bigHoleLeft, 50, 17, 7, 14);
      drawMotif(tmpBmp, bigHoleRight, 57, 17, 7, 14);
    }else{
      drawMotif(tmpBmp, bigCercleLeft, 50, 17, 7, 14);
      drawMotif(tmpBmp, bigCercleRight, 57, 17, 7, 14);
      drawMotif(tmpBmp, number3, 53, 18, 7, 11);
    }
    if(flag) drawInvertRect(tmpBmp, 0, 0, 64, 32);
    
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
    
  }
  
  //3 BUMPERS SUCCESS-----------------------------------------------------------------------------
  EmptyMatrix(tmpBmp);
  time = 0;
  flag = false;
  while(requestedScreen == SCREEN_3BUMPERS_MODE_SUCCESS){
    time++;
    centerString(tmpBmp, "COMPLETE", 3);
    centerString(tmpBmp, "1000", 19);
    if(time%5 == 0) flag = !flag; 
    if(flag) drawInvertRect(tmpBmp, 0, 0, 64, 32);
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
    if(time > 100) requestedScreen = lowPriorityScreen;
  }
  
  //GREEN TARGET MODE----------------------------------------------
  EmptyMatrix(tmpBmp);
  time = 0;
  x = -30;
  x2 = 60;
  while(requestedScreen == SCREEN_GREEN_TARGET_MODE){
    time++;
    drawString(tmpBmp, "GREEN", x, 3, 50);
    drawString(tmpBmp, "TARGET", x2, 19, 50);
    if(x < 15) x++;
    if(x2 >12) x2--;
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
    if(time > 250) requestedScreen = lowPriorityScreen;
  }
  
  EmptyMatrix(tmpBmp);
  time = 50;
  flag = false;
  while(requestedScreen == SCREEN_GREEN_TARGET_MODE_STATE || requestedScreen == SCREEN_RED_TARGET_MODE_STATE || requestedScreen == SCREEN_MIDDLE_TARGET_MODE_STATE){
    if(nb_hits != nb_hits_Old) time = 0;
    nb_hits_Old = nb_hits;
    if(time < 50){
      time++;
      if(time%3 == 0) flag = !flag;
    }else flag = false;
    
    if(countdown < 3 && time%3 == 0) flag = !flag;
    
    char buf[2];
    sprintf(buf, "TIME: %d", countdown);
    centerString(tmpBmp, buf, 19);
    
    char bufHits[2];
    sprintf(bufHits, "HITS: %d", nb_hits);
    centerString(tmpBmp, bufHits, 3);
    
    if(flag) drawInvertRect(tmpBmp, 0, 0, 64, 32);
    
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
    
  }
  
  //RED TARGET MODE----------------------------------------------
  EmptyMatrix(tmpBmp);
  time = 0;
  x = -64;
  x2 = 82;
  while(requestedScreen == SCREEN_RED_TARGET_MODE){
    time++;
    drawString(tmpBmp, "RED TARGET", x, 3, 50);
    drawString(tmpBmp, "MODE", x2, 19, 50);
    if(x < 1) x++;
    if(x2 >18) x2--;
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
    if(time > 250) requestedScreen = lowPriorityScreen;
  }
  
  
  
  //MIDDLE TARGET MODE----------------------------------------------
  EmptyMatrix(tmpBmp);
  time = 0;
  x = -30;
  x2 = 55;
  while(requestedScreen == SCREEN_MIDDLE_TARGET_MODE){
    time++;
    drawString(tmpBmp, "MIDDLE", x, 3, 50);
    drawString(tmpBmp, "TARGET", x2, 19, 50);
    if(x < 15) x++;
    if(x2 >12) x2--;
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
    if(time > 250) requestedScreen = lowPriorityScreen;
  }
  
  
  //ALL TARGETS MODE----------------------------------------------
  EmptyMatrix(tmpBmp);
  time = 0;
  x = -64;
  x2 = 80;
  while(requestedScreen == SCREEN_ALL_TARGET_MODE){
    time++;
    drawString(tmpBmp, "ALL TARGET", x, 3, 50);
    drawString(tmpBmp, "MODE", x2, 19, 50);
    if(x < 1) x++;
    if(x2 >19) x2--;
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
    if(time > 250) requestedScreen = lowPriorityScreen;
  }
  
  //SCREEN_ALL_GATES-------------------------------------------------------
  EmptyMatrix(tmpBmp);
  time = 0;
  flag = false;
  while(requestedScreen == SCREEN_ALL_GATES){
    time++;
    centerString(tmpBmp, "GATE BONUS!", 3);
    centerString(tmpBmp, "+1000", 20);   
    if(time%3 == 0) flag = !flag; 
    if(flag) drawInvertRect(tmpBmp, 0, 0, 64, 32);
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
    if(time > 50) requestedScreen = lowPriorityScreen;
  }
  
  //SCREEN_BALL_GAME-------------------------------------------------------
  EmptyMatrix(tmpBmp);
  time = 0; flag = false;
  x = 32; y = -10;
  int vit_x = 0; int vit_y = 1;
  vit_x = 1 - random(3);
  int floorX = 32;
  flag = false;
  int time2 = 0;
  byte nbWin = 0, nbTry = 0;
  commandToSend = 0;

  while(requestedScreen == SCREEN_BALL_GAME){
    time++;
    bool leftFlipper = flippers_state & 1;
    bool rightFlipper = (flippers_state & 2) >> 1;
    
    if(time2 > 0){
      time2--;
      if(time2%3 == 0) flag = !flag;
    }else flag = false;
    
    //Moving the Floor X position
    if(time%2 == 0){
      if(leftFlipper && floorX > 5) floorX--;
      if(rightFlipper && floorX < 64-5) floorX++;
    }
    //Moving and testing the ball
    if(time%2 == 0){
      y += vit_y;
      x += vit_x;
      
      if(x+7 >= 64){
        vit_x = vit_x*-1;
        x = 57;
      }
      if(x <= 0){
        vit_x = vit_x*-1;
        x = 0;
      }
      //When the ball hits the floor
      if(y+7 >= 31 && vit_y == 1){
        nbTry++;
        //Check if the ball is in the hole
        short ballPos = x + 4;
        if( (floorX > ballPos && floorX - ballPos < 3) || (floorX < ballPos && ballPos - floorX < 4) || floorX == ballPos){
          time2 = 10;
          y = -20;
          randomSeed(analogRead(0));
          vit_x = 1 - random(3);
          randomSeed(analogRead(0));
          x = 20 + random(50);
          vit_y = 1;
          nbWin++;
          //If it is the third Catch, game in won
          if(nbWin == 3){
            SendCommandToMaster(GAME_WIN);
          }else SendCommandToMaster(BALL_CATCHED);
          
        //If the ball is not in the hole, we make it bounce
        }else{
           vit_y = -1;
           SendCommandToMaster(BALL_BOUNCE);
           if(nbTry == 10){
             SendCommandToMaster(GAME_LOST);
           }
        }
      //One ce ball goes back up the screen, we relaunch it 
      }else if(y < 0 && vit_y == -1){
        randomSeed(analogRead(0));
        vit_x = 1 - random(3);
        
        vit_y = vit_y*-1;
        y = 0;
      }
    }
    //ball
    drawMotif(tmpBmp, ball, x, y, 7, 7);
    //line2
    drawRect(tmpBmp, 0, 31, floorX-3, 1);
    drawRect(tmpBmp, floorX+3, 31, 64, 1);
    //line3
    drawRect(tmpBmp, 0, 30, floorX-4, 1);
    drawRect(tmpBmp, floorX+4, 30, 64, 1);
    
    if(flag) drawInvertRect(tmpBmp, 0, 0, 64, 32);
    
    
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
  }
  
  //FRAME SCREEN_BALL_GAME_INTRO--------------------------------------------------
  x = -64;
  y = 100;
  while(requestedScreen == SCREEN_BALL_GAME_INTRO){
    drawString(tmpBmp, "EXTRA BALL", x, 3, 50);
    centerString(tmpBmp, "ROUND", y);
    if(x < 2) x++;
    if(y > 20) y--;
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
  }
  
   //FRAME SCREEN_BUMPERS_RESULT--------------------------------------------------
  x = -64;
  time = 0;
  byte nbHitDisplayed = 0;
  y = 33;
  while(requestedScreen == SCREEN_BUMPERS_RESULT){
    time++;
    drawString(tmpBmp, "BUMPERS", x, 3, 50);
    if(x < 8 && time < 200) x++;
    if(y > 20) y--;
    
    if(nbHitDisplayed < nb_hits) nbHitDisplayed++;
    char bufHits[2];
    sprintf(bufHits, "%d", nbHitDisplayed);
    centerString(tmpBmp, bufHits, y);
    
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
  }
  
  //FRAME SCREEN_TARGETS_RESULT--------------------------------------------------
  x = -64;
  time = 0;
  y = 33;
  nbHitDisplayed = 0;
  while(requestedScreen == SCREEN_TARGETS_RESULT){
    time++;
    drawString(tmpBmp, "TARGETS", x, 3, 50);
    if(x < 8 && time < 200) x++;
    if(y > 20) y--;
    
    if(nbHitDisplayed < nb_hits) nbHitDisplayed++;
    char bufHits[2];
    sprintf(bufHits, "%d", nbHitDisplayed);
    centerString(tmpBmp, bufHits, y);
    
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
  }
  
  //FRAME SCREEN_SCORE_RESULT--------------------------------------------------
  x = -64;
  time = 0;
  unsigned long scoreDisplayed = 0;
  //score = 12305;
  while(requestedScreen == SCREEN_SCORE_RESULT){
    time++;
    int scoreInc = score / 20;
    if(scoreDisplayed < score) scoreDisplayed += scoreInc;
    else scoreDisplayed = score;
    
    char bufHits[5];
    sprintf(bufHits, "%lu", scoreDisplayed);
    centerString(tmpBmp, bufHits, 11);
    
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
  }
  
  //FRAME SCREEN_PSIT_MODE_ACTIVE--------------------------------------------------
  time = 0;
  nbLetterShown = 0;
  while(requestedScreen == SCREEN_PSIT_MODE_ACTIVE){
    time++;
    
    drawString(tmpBmp, "P S I T", 18, 3, nbLetterShown);
    if(time%5 == 0 && nbLetterShown < 7){
      nbLetterShown++;
    }
    if(time > 80) centerString(tmpBmp, "ACTIVATED", 19);
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
  }
  
  //FRAME SCREEN_PSIT_MODE_STATE--------------------------------------------------
  time = 0;
  //psit_state = 0b0101;
  while(requestedScreen == SCREEN_PSIT_MODE_STATE){
    time++;
    
    drawString(tmpBmp, "P S  I  T", 15, 3, 50);
    
    if((psit_state & 0b1000) >> 3) drawInvertRect(tmpBmp, 14, 2, 8, 11);
    if((psit_state & 0b0100) >> 2) drawInvertRect(tmpBmp, 23, 2, 8, 11);
    if((psit_state & 0b0010) >> 1) drawInvertRect(tmpBmp, 32, 2, 8, 11);
    if(psit_state & 0b0001) drawInvertRect(tmpBmp, 41, 2, 8, 11);
    
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
    if(time > 50) requestedScreen = lowPriorityScreen;
  }
  
  //FRAME SCREEN_PSIT_MODE_COMPLETE-----------------------------------------------------------------
  time = 0;
  flag = true;
  while(requestedScreen == SCREEN_PSIT_MODE_COMPLETE){
    time++;
    if(time < 70){
      drawString(tmpBmp, "P S  I  T", 15, 3, 50);
      drawInvertRect(tmpBmp, 14, 2, 35, 11);
    }else{
      drawString(tmpBmp, "P S I T !", 14, 3, 50);
      if(flag) drawInvertRect(tmpBmp, 0, 0, 64, 16);
      if(time %3 == 0) flag = !flag;
      centerString(tmpBmp, "+5000", 19);
    }
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
    if(time > 120) requestedScreen = lowPriorityScreen;
  }
  
  //SCREEN_HIGHSCORES-----------------------------------------------------------------
  time = 0; time2 = 0;
  y = 33; y2 = 33; x = 0;
  byte x2 = 0; short i = 0; flag = true; bool flag2 = false;
  scoreDisplayed = 0;
  bool displayHighScore = true;
  //using scoresTab
  while(requestedScreen == SCREEN_HIGHSCORES){
    time++;
    if(time > 150 && !flag || time > 50 && flag){
      time = 0;
      //Displaying next rank
      if(!flag){
        i++;
        y = 33;
        scoreDisplayed = 0;
      }
      if(i == 6){
        //i = 0;
        displayHighScore = false;
      }
      flag = !flag; 
    }
    
    if(!displayHighScore){
      if(flag2){
        centerString(tmpBmp, "PRESS", 1);
        centerString(tmpBmp, "START", 17);
      }
      if(time%5 == 0) flag2 = !flag2;
      if(time > 200){
        displayHighScore = true;
        i = 0;
      }
    }else{
      if(i == 0){
        if( y > 11 && flag) y--;
        else if( y > -20 && !flag && time > 50 && time%5==0) y--;
        centerString(tmpBmp, "HIGHSCORES", y);
      }else{
        
        //Display Score Rank
        char buf[1];
        sprintf(buf, "%d", i);
        if( y > 3 && flag) y--;
        else if(!flag && y > -20 && time > 130) y--;
        if(!flag && time > 130) y2++;
        else y2 = 19;
        drawString(tmpBmp, buf, 0, y, 50);
        
        //Display Name
        
        if(i == 1) drawString(tmpBmp, highscoreName1, 10, y, 50);
        else if(i == 2) drawString(tmpBmp, highscoreName2, 10, y, 50);
        else if(i == 3) drawString(tmpBmp, highscoreName3, 10, y, 50);
        else if(i == 4) drawString(tmpBmp, highscoreName4, 10, y, 50);
        else if(i == 5) drawString(tmpBmp, highscoreName5, 10, y, 50);
          
        //Display Score
        if(!flag){
          char bufScore[5];
          int scoreInc = scoresTab[i-1] / 20;
          if(scoreDisplayed < scoresTab[i-1] ) scoreDisplayed += scoreInc;
          else scoreDisplayed = scoresTab[i-1];
          sprintf(bufScore, "%lu", scoreDisplayed);
          
          centerString(tmpBmp, bufScore, y2);
        }
      }
    }
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
  }
  
  //SCREEN_ENTER_NAME-----------------------------------------------------------------
  time = 0;
  time2 = 0;
  flag = true;
  short instructionsIndex = 0;
  y = 0;
  
  name[0] = name[1] = name[2] =name[3] = name[4] =name[5]=name[6]=name[7]=name[8]=name[9]=' ';
  name[10] = '\0';
  
  short index = 0;
  char currentChar = 'A';
  Old_leftFlipper = 0;
  Old_rightFlipper = 0;
  nameEntered = false;
  nameEnterCanceled = false;
  while(requestedScreen == SCREEN_ENTER_NAME){
    bool leftFlipper = flippers_state & 1;
    bool rightFlipper = (flippers_state & 2) >> 1;
    
    time++;
    if(time%10 == 0) flag = !flag;
    if(time%100 == 0){
      instructionsIndex++;
      if(instructionsIndex == 3) instructionsIndex = 0; 
    }
    
    if(!nameEntered && leftFlipper == 0 && leftFlipper != Old_leftFlipper){
       if(currentChar == ' ') currentChar = 'A';
       else{
         currentChar++;
         if(currentChar == 91) currentChar = '0';
         if(currentChar == 58) currentChar = ' ';
       }
    }
    if(!nameEntered && rightFlipper == 0 && rightFlipper != Old_rightFlipper){
      if(index >= 9){
        nameEntered = true;
      }else{
        name[index] = currentChar;
        index++;
        currentChar = ' ';
      } 
    }
    if(start_state == 1){
      if(index == 0 && currentChar == 'A') nameEnterCanceled = true;
      else nameEntered = true;
      //if(index > 1 ) nameEntered = true;
    }
    
    byte nameLength = getStringLengthAt(name, index, FONT_NORMAL);
    byte currentCharLength = getCharLength(currentChar, FONT_NORMAL);
    
    if(flag){
      drawMotif(tmpBmp, curseur, 1 + nameLength - (currentCharLength/2) - 4, 29, 5, 3); 
    }
    name[index] = currentChar;  
    drawString(tmpBmp, name, 1, 19, 50);
    
    if(instructionsIndex == 0){
      drawSmallString(tmpBmp, "ENTER  YOUR", 1, 1, 50);
      drawSmallString(tmpBmp, "NAME", 1, 9, 50);
    }else if(instructionsIndex == 1){
      drawSmallString(tmpBmp, "<  LETTER  SEL.", 1, 1, 50);
      drawSmallString(tmpBmp, "NEXT LETTER >", 0, 9, 50);
    }else if(instructionsIndex == 2){
      drawSmallString(tmpBmp, "< + > TO", 1, 1, 50);
      drawSmallString(tmpBmp, "VALIDATE", 1, 9, 50);
    }
    Old_leftFlipper = leftFlipper;
    Old_rightFlipper = rightFlipper;
    
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
    
    
  }
  
  time = 0;
  short frameIndex = 0;
  flag = true;
  x = 0;
  while(requestedScreen == SCREEN_PSIT_ANIM){
    time++;
    if(time%4 == 0 && flag) frameIndex++;
    if(time%4 == 0 && !flag) frameIndex--;
    if(frameIndex == 4 && flag){
      flag = !flag;
      frameIndex = 3;
    }
    else if(frameIndex == -1 && !flag){
      flag = !flag;
      frameIndex = 0;
      x+=10;
      if(x > 64) x = 0;
    }
    drawBigMotif(tmpBmp, psitMan[frameIndex], x, 2, 14, 29);

    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp); 
  }
  
  /*========== SCREEN_WORD_GAME =====*/
  index = 0;
  currentChar = '_';
  Old_leftFlipper = 0;
  Old_rightFlipper = 0;
  byte stringSize;
  time = 0;
  commandToSend = 0;
  //Answer definitions
  char superman[9] = {'S', 'U', 'P', 'E', 'R', 'M', 'A', 'N', '\0'};
  char pikachu[8] = {'P', 'I', 'K', 'A', 'C', 'H', 'U', '\0'};
  char hulk[5] = {'H', 'U', 'L', 'K','\0'};
  char batman[7] = {'B', 'A', 'T', 'M', 'A', 'N', '\0'};
  char *selectedAnswer;
  
  //Question selection
  char answerHidden[9];
  byte nbLetterToHide = 0;
  randomSeed(analogRead(0));
  byte hasard = random(4);
  if(hasard == 0){
    copyString(superman, answerHidden, 9);
    stringSize = 8;
  }else if(hasard == 1){
    copyString(pikachu, answerHidden, 8);
    stringSize = 7;
  }else if(hasard == 2){
    copyString(hulk, answerHidden, 5);
    stringSize = 4;
  }else if(hasard == 3){
    copyString(batman, answerHidden, 7);
    stringSize = 6;
  }
  
  answerHidden[stringSize] = '\0';
  nbLetterToHide = stringSize/2;
  byte nbHiddenLetter = 0;

  //Hide randomly some letters
  while(nbHiddenLetter < nbLetterToHide){
    randomSeed(analogRead(0));
    if(random(3) == 0 && answerHidden[index] != '_'){
      nbHiddenLetter++;
      answerHidden[index] = '_';
    }else 
    index++;
    if(index == 7) index = 0;
  }

  index = 0;
  while(answerHidden[index] != '_') index++;
  bool correct = false;
  while(requestedScreen == SCREEN_WORD_GAME){
    bool leftFlipper = flippers_state & 1;
    bool rightFlipper = (flippers_state & 2) >> 1;
    
    time++;
    if(time%10 == 0) flag = !flag;

    if(!nameEntered && leftFlipper == 0 && leftFlipper != Old_leftFlipper){
      if(currentChar == '_') currentChar = 'A';
      else{
       currentChar++;
       if(currentChar == 91) currentChar = '_';
      }
       
    }
    if(!nameEntered && rightFlipper == 0 && rightFlipper != Old_rightFlipper){
      index++;
      while(answerHidden[index] != '_' && index < stringSize) index++;
      if(index >= stringSize){
        nameEntered = true;
        time = 0;
        
        if(hasard == 0) correct = compareString(answerHidden, superman, stringSize);
        else if(hasard == 1) correct = compareString(answerHidden, pikachu, stringSize);
        else if(hasard == 2) correct = compareString(answerHidden, hulk, stringSize);
        else if(hasard == 3) correct = compareString(answerHidden, batman, stringSize);
        
      }else{
        answerHidden[index] = currentChar;
        currentChar = '_';
      } 
    }
    
    byte nameLength = getStringLengthAt(answerHidden, index, FONT_NORMAL);
    byte currentCharLength = getCharLength(currentChar, FONT_NORMAL);
    
    if(flag && !nameEntered){
      drawMotif(tmpBmp, curseur, 1 + nameLength - (currentCharLength/2) - 4, 29, 5, 3); 
    }
    if(!nameEntered) answerHidden[index] = currentChar;
  
    if(!nameEntered || nameEntered && time < 50){  
      drawString(tmpBmp, answerHidden, 1, 19, 50);
      
      if(hasard == 0){
        drawSmallString(tmpBmp, "SUPERHERO", 1, 0, 50);
        drawSmallString(tmpBmp, "CHARACTER", 1, 8, 50);
      }else if(hasard == 1){
        drawSmallString(tmpBmp, "IT S  A", 1, 0, 50);
        drawSmallString(tmpBmp, "POKEMON", 1, 8, 50);
      }else if(hasard == 2){
        drawSmallString(tmpBmp, "VERY", 1, 0, 50);
        drawSmallString(tmpBmp, "STRONG", 1, 8, 50);
      }else if(hasard == 3){
        drawSmallString(tmpBmp, "SUPERHERO", 1, 0, 50);
        drawSmallString(tmpBmp, "CHARACTER", 1, 8, 50);
      }
      
      //Display Timer
      char buf[2];
      sprintf(buf, "%d", countdown);
      drawSmallString(tmpBmp, buf, 57, 0, 50);
    
    }else{
      if(correct){
        centerString(tmpBmp, "CORRECT!", 11);
        if(time > 100) SendCommandToMaster(GAME_WIN);
      }else{
        centerString(tmpBmp, "WRONG!", 7);
        if(time > 100) SendCommandToMaster(GAME_LOST);
      }
      
    }
    Old_leftFlipper = leftFlipper;
    Old_rightFlipper = rightFlipper;
    
    DisplayMatrix(tmpBmp);
    EmptyMatrix(tmpBmp);
  }
  
  
  
  
}


