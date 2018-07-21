void PlayBallGame(){
  
  byte gameStatus;
   modeBeginTime = millis();
  gameStatus = GAME_IDLE;
  while(gameStatus != GAME_WIN && gameStatus != GAME_LOST){
    ReadSolenoidSwitches();
    ReadSwitches();
    //Order starting at 0: LEFT 0 then RIGHT 1
    byte flippers_state = RIGHT_FLIPPER;
    flippers_state = (flippers_state << 1) | LEFT_FLIPPER;
    flippers_state = (flippers_state << 1) | START;
    SendScreenData(FLIPPERS_STATE, flippers_state);
    
    gameStatus = ReadBallGameStatus();
    if(gameStatus == BALL_BOUNCE) PlaySound(BOINNG, true);
    else if(gameStatus == BALL_CATCHED){
      PlaySound(BUMPER_2, true);
      score += 10* scoreCoef;
      AnimLightFor(FLASH_TOP_LIGHTS, 30);
      
    }else if(gameStatus == GAME_LOST){
      PlaySound(LOOSE_POINT_POINT, true);
      
    }else if(gameStatus == GAME_WIN){
      PlaySound(CAFARTE, true);
      DisplayScreen(SCREEN_3BUMPERS_MODE_SUCCESS, PRIORITY_LOW);
      score += 1000* scoreCoef;
      delay(2000);
      EnableFlippers();
      
      
      DisplayScreen(SCREEN_MULTIBALL, PRIORITY_HIGH);
      PlaySound(MULTIBALL_SOUND, true);
      FireANewBall();
      PlayRandomMultiballMusic();
      delay(2000);
    }
    DisplayScore(score);
    delay(50);
  } 
}

void PlayWordGame(){
  
  byte gameStatus;
   modeBeginTime = millis();
  gameStatus = GAME_IDLE;
  while(gameStatus != GAME_WIN && gameStatus != GAME_LOST){
    ReadSolenoidSwitches();
    ReadSwitches();
    //Order starting at 0: LEFT 0 then RIGHT 1
    byte flippers_state = RIGHT_FLIPPER;
    flippers_state = (flippers_state << 1) | LEFT_FLIPPER;
    flippers_state = (flippers_state << 1) | START;
    SendScreenData(FLIPPERS_STATE, flippers_state);
    
    //Send TimeOut
    if ( millis() - timeSinceUpdateScreen > 1000) {
      unsigned long countdown = (25000 - (millis() - modeBeginTime)) / 1000;
      byte countdownByted = countdown;
      if (countdownByted <= 0 ) countdownByted = 0;
      timeSinceUpdateScreen = millis();

      SendScreenData(COUNTDOWN, countdownByted);
    }
    
    
    
    //End of time out 
    if (millis() - modeBeginTime >= 25000){
      gameStatus = GAME_LOST;
    }else gameStatus = ReadBallGameStatus();
    
    if(gameStatus == GAME_LOST){
      PlaySound(LOOSE_POINT_POINT, true);
      
    }else if(gameStatus == GAME_WIN){
      PlaySound(CAFARTE, true);
      DisplayScreen(SCREEN_3BUMPERS_MODE_SUCCESS, PRIORITY_LOW);
      score += 1000* scoreCoef;
      delay(1000);
      EnableFlippers();
    }
    DisplayScore(score);
    delay(50);
  } 
}

void PlayStarWarsGame(){
  
  byte gameStatus;
  unsigned long gameScore = 0;
   modeBeginTime = millis();
  gameStatus = GAME_IDLE;
  int loosingLights = 0;
  while(gameStatus != GAME_WIN && gameStatus != GAME_LOST){
    time = millis();
    ReadSolenoidSwitches();
    ReadSwitches();
    //Order starting at 0: LEFT 0 then RIGHT 1
    byte flippers_state = RIGHT_FLIPPER;
    flippers_state = (flippers_state << 1) | LEFT_FLIPPER;
    flippers_state = (flippers_state << 1) | START;
    SendScreenData(FLIPPERS_STATE, flippers_state);
    
    gameStatus = ReadBallGameStatus();
    if(gameStatus == GAME_LOST){
      PlaySound(DARTHVADORFAIL, true);
      DisplayScreen(SCREEN_STARWARS_LOST, PRIORITY_LOW);   
      delay(4000);  
    }else if(gameStatus == ENEMI_DESTROYED){
      PlaySound(PETITEEXPLOSION, false);
      AnimLightFor(FLASH_TOP_LIGHTS, 5);
      gameScore++;
    }else if(gameStatus == SHIP_DESTROYED){
      PlaySound(BIGEXPLOSION, true);
      AnimLightFor(FLASH_TOP_LIGHTS, 30);
      AmbiLight(BOOST_ON);
      AmbiLight(RED_ON);
      loosingLights = 30;
    }else if(gameStatus == LASER_SHOT){
      PlaySound(BLASTER, true);
    }else if(gameStatus == GAME_WIN){
      delay(3000);
      DisplayScreen(SCREEN_STARWARS_WIN, PRIORITY_LOW);
      score += 3000* scoreCoef;
      delay(1000);
      EnableFlippers();
      
      DisplayScreen(SCREEN_MULTIBALL, PRIORITY_HIGH);
      PlaySound(MULTIBALL_SOUND, true);
      FireANewBall();
      PlayRandomMultiballMusic();
      delay(4000);
    }

    if(loosingLights == 1) {
      AmbiLight(BOOST_OFF);
      AmbiLight(ALL_OFF);
      loosingLights = 0;
    }else if (loosingLights > 1) {
      loosingLights --;
    }
    DisplayScore(gameScore);
    delay(50);
  }
  
  //Restore the game score
  DisableIncrementalScore();
  delay(100);
  DisplayScore(score);
  delay(100);
  EnableIncrementalScore();
}
