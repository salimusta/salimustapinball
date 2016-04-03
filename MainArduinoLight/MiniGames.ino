void PlayBallGame(){
  
  byte gameStatus;
   modeBeginTime = millis();
  gameStatus = GAME_IDLE;
  while(gameStatus != GAME_WIN && gameStatus != GAME_LOST){
    ReadSolenoidSwitches();
    
    //Order starting at 0: LEFT 0 then RIGHT 1
    byte flippers_state = RIGHT_FLIPPER;
    flippers_state = (flippers_state << 1) | LEFT_FLIPPER;
    SendScreenData(FLIPPERS_STATE, flippers_state);
    
    gameStatus = ReadBallGameStatus();
    if(gameStatus == BALL_BOUNCE) PlaySound(BOINNG);
    else if(gameStatus == BALL_CATCHED){
      PlaySound(BUMPER_2);
      score += 10;
      AnimLightFor(FLASH_TOP_LIGHTS, 30);
      
    }else if(gameStatus == GAME_LOST){
      PlaySound(LOOSE_POINT_POINT);
      
    }else if(gameStatus == GAME_WIN){
      PlaySound(CAFARTE);
      DisplayScreen(SCREEN_3BUMPERS_MODE_SUCCESS, PRIORITY_LOW);
      score += 1000;
      delay(2000);
      EnableFlippers();
      
      
      DisplayScreen(SCREEN_MULTIBALL, PRIORITY_HIGH);
      ProvideANewBall();
      PlayRandomMultiballMusic();
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
    
    //Order starting at 0: LEFT 0 then RIGHT 1
    byte flippers_state = RIGHT_FLIPPER;
    flippers_state = (flippers_state << 1) | LEFT_FLIPPER;
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
      PlaySound(LOOSE_POINT_POINT);
      
    }else if(gameStatus == GAME_WIN){
      PlaySound(CAFARTE);
      DisplayScreen(SCREEN_3BUMPERS_MODE_SUCCESS, PRIORITY_LOW);
      score += 1000;
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
  while(gameStatus != GAME_WIN && gameStatus != GAME_LOST){
    ReadSolenoidSwitches();
    
    //Order starting at 0: LEFT 0 then RIGHT 1
    byte flippers_state = RIGHT_FLIPPER;
    flippers_state = (flippers_state << 1) | LEFT_FLIPPER;
    SendScreenData(FLIPPERS_STATE, flippers_state);
    
    gameStatus = ReadBallGameStatus();
    if(gameStatus == GAME_LOST){
      PlaySound(DARTHVADORFAIL);
      DisplayScreen(SCREEN_STARWARS_LOST, PRIORITY_LOW);   
      delay(4000);  
    }else if(gameStatus == ENEMI_DESTROYED){
      PlaySound(PETITEEXPLOSION);
      AnimLightFor(FLASH_TOP_LIGHTS, 5);
      gameScore++;
    }else if(gameStatus == SHIP_DESTROYED){
      PlaySound(BIGEXPLOSION);
      AnimLightFor(FLASH_TOP_LIGHTS, 30);
    }else if(gameStatus == LASER_SHOT){
      PlaySound(BLASTER);
    }else if(gameStatus == GAME_WIN){
      delay(3000);
      DisplayScreen(SCREEN_STARWARS_WIN, PRIORITY_LOW);
      score += 3000;
      delay(1000);
      EnableFlippers();
      
      DisplayScreen(SCREEN_MULTIBALL, PRIORITY_HIGH);
      ProvideANewBall();
      PlayRandomMultiballMusic();
    }
    DisplayScore(gameScore);
    delay(50);
  }
  
  //Restore the game score
  DisableIncrementalScore();
  DisplayScore(score);
  EnableIncrementalScore();
}
