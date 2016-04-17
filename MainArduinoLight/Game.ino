#define BUMPER_BONUS_INTERVAL 1200

unsigned long score;
unsigned long sendedScore;
byte nbBall = 0;
bool gate1Passed;
bool gate2Passed;
bool gate3Passed;
bool psitModeActive;
byte psitModeState;
short nbBump;
short nbTarget;

byte nbPlayer = 1;
byte currentPlayer = 0;
byte selectedPlayer = 0;

//Variables generales
bool gameIsOn = false;
bool ballIsInPlay = false;
byte ballInPlay = 0;
bool ballLaunched = false;

//Variable pour les Kickouts
int timeInHole1 = 0;
bool ballCatchedInHole1 = false;
int timeInHole2 = 0;
bool ballCatchedInHole2 = false;

//GESTION DES MODE
byte activeMode = NO_MODE;
unsigned long modeBeginTime = 0;
bool modeStarted = false;
unsigned long time = 0;
unsigned long timeSinceUpdateScreen = 0;
byte nb_hits = 0;
bool alreadyActivatedModes[10] = {false, false, false, false, false, false, false, false, false, false};

//Bumpers
byte bumpersState = 0;
int timeSinceBumper1Hit = 100;
int timeSinceBumper2Hit = 100;
int timeSinceBumper3Hit = 100;

//Targets
int timeSinceLeftRedTargetHit = 100; int timeSinceRightRedTargetHit = 100;
int timeSinceLeftGreenTargetHit = 100; int timeSinceRightGreenTargetHit = 100;
int timeSinceYellowTargetHit = 100;

//Targets status, no multiplayer, lives for 1 ball
byte leftRedTarget_Status = 0;
byte rightRedTarget_Status = 0;
byte leftGreenTarget_Status = 0;
byte rightGreenTarget_Status = 0;
byte yellowTarget_Status = 0;

bool allTargetsHitFiveTimes = false;

//Ramp status
bool ramp1Passed = false;
unsigned long timeSinceRamp1 = 0;

//Double Mode
byte scoreCoef = 1;

//TILT Management
bool TILT_Active = false;
int TILT_Time = 0;
byte TILT_WarningCount = 0;

char name[11];

int nbBallFired = 0;
int nbBumperFired = 0;
int nbTargetReached = 0;

//Timings
unsigned long timeSinceNewBall = 0;

void ManageGame() {

  AllLightsOff();
  
  //If game is on but still ball to play
  if (gameIsOn){
    SendLedMatrixScore(selectedPlayer);
    selectedPlayer++;
    bool newRound = false;
    if(selectedPlayer == nbPlayer){
      selectedPlayer = 0;
      newRound = true;
    }
    SelectPlayer(selectedPlayer);
    SendScreenData(PLAYER_SELECTED, selectedPlayer);
    
    if(newRound && nbBall > 0 && nbPlayer > 1){
      DisplayScreen(SCREEN_PLAYER_SCORES, PRIORITY_LOW);
      delay(8000);
    }
    
  }
  //GAME OVER- if the game is on, no more ball and no more player
  if (gameIsOn && nbBall <= 0) {
    //Game finished
    StopMusic();
    PlaySound(GAME_OVER);
    DisplayScreen(SCREEN_GAMEOVER, PRIORITY_LOW);
    DisableIncrementalScore();
    DisplayScore(score);
    BlinkScore();
    DisableFlippers();
    AmbiLight(ANIME_ALL);
    AnimLight(ANIM_ALL);
    AnimLight2(ANIM_ALL);
    delay(2000);
    
    //calculate bonuses and display Final score, per player
    for(byte k = 0; k < nbPlayer ; k++){
      SelectPlayer(k);
      nbBumperFired += nbBump;
      nbTargetReached += nbTarget;
      SendScreenData(PLAYER_SELECTED, k);
    
      SendScreenData(NB_HITS, nbBump);
      DisplayScreen(SCREEN_BUMPERS_RESULT, PRIORITY_LOW);
      score += nbBump*50;
      EnableIncrementalScore();
      DisplayScore(score);
      delay(3000);
    
      SendScreenData(NB_HITS, nbTarget);
      DisplayScreen(SCREEN_TARGETS_RESULT, PRIORITY_LOW);
      score += nbTarget*50;
      if(nbBump == nbTarget && nbTarget > 5) score += 500;
      EnableIncrementalScore();
      DisplayScore(score);
      delay(3000);
    
      DisableIncrementalScore();
      DisplayScreen(SCREEN_SCORE, PRIORITY_LOW);
      delay(1000);
      SendLedMatrixScore();
      DisplayScreen(SCREEN_SCORE_RESULT, PRIORITY_LOW);
      SendLedMatrixScore(k);
      if(nbPlayer > 1) delay(2000);
      else delay(5000);
    }
    
    //Write Maintenance Data
    WritePinballData(0, nbBump, nbTarget, 1);
    delay(100);
    
    //If multiplayer, Display all the scores
    if(nbPlayer > 1){
      DisplayScreen(SCREEN_PLAYER_SCORES, PRIORITY_LOW);
      delay(5000);
      DisplayScreen(SCREEN_PLAYER_WIN, PRIORITY_LOW);
      delay(2000);
    }
     
    for(byte k = 0; k < nbPlayer ; k++){
      SelectPlayer(k);
      SendScreenData(PLAYER_SELECTED, k);
      DisplayScore(score);
      //Enter Score Mode if score ok
      if (score >= getMinScore()) {
        
        //Retrieve the Player name
        ReadSolenoidSwitches(); delay(50);
        ReadSwitches(); delay(50);
        RIGHT_FLIPPER = 0; LEFT_FLIPPER = 0; START = 0;
        SendScreenData(FLIPPERS_STATE, 0);
        delay(50);
        
        DisplayScreen(SCREEN_ENTER_NAME, PRIORITY_LOW);
        PlaySound(OMGYOUWON_HIGHSCORE);
        while (1) {
          ReadSolenoidSwitches();
          ReadSwitches();
          byte flippers_state = RIGHT_FLIPPER;
          flippers_state = (flippers_state << 1) | LEFT_FLIPPER;
          flippers_state = (flippers_state << 1) | START;
          SendScreenData(FLIPPERS_STATE, flippers_state);
  
          delay(50);
          ReadPlayerName(name);
          if (name[0] != 40) break;
          delay(30);
        }
        if(name[0] != 39){
          addHighScore(score, name);
          WriteScoreMemory();
          
          DisplayScreen(SCREEN_SCORE_SAVED, PRIORITY_LOW);
          delay(1000);
          SendHighScores();
          delay(500);
        }
      }
    }
    //--------------
    //End of the game, waiting for player to restart
    DisplayScreen(SCREEN_HIGHSCORES, PRIORITY_LOW);
    delay(100);
    StopMusic();
    WaitForRestart();
    nbBallFired = 0;
    PlaySound(PIECE);
    score = 0;
    DisplayScore(score);
    delay(500);
    gameIsOn = false;
  }
  //Game start 
  if (gameIsOn == false) {
    //lcd.setCursor(0, 0); lcd.print("Game Mode");
    //lcd.setCursor(0, 1); lcd.print("----------------");
    
    //Ask for player Number
    delay(200);
    DisplayScreen(SCREEN_PLAYER_SELECTION, PRIORITY_LOW);
    
    bool oldRIGHT_FLIPPER = false;
    bool oldLEFT_FLIPPER = false;
    while (1) {
      ReadSolenoidSwitches();
      ReadSwitches();
      byte flippers_state = RIGHT_FLIPPER;
      flippers_state = (flippers_state << 1) | LEFT_FLIPPER;
      flippers_state = (flippers_state << 1) | START;
      SendScreenData(FLIPPERS_STATE, flippers_state);

      if((RIGHT_FLIPPER != oldRIGHT_FLIPPER && RIGHT_FLIPPER == 1) || (LEFT_FLIPPER != oldLEFT_FLIPPER && LEFT_FLIPPER == 1)){
        PlaySound(BIP);
      }
      oldRIGHT_FLIPPER = RIGHT_FLIPPER;
      oldLEFT_FLIPPER = LEFT_FLIPPER;
      delay(30);
      nbPlayer = ReadPlayerNumber();
      if (START) break;
      delay(30);
    }
    //Here we have chosen the number of players
    initPlayers(nbPlayer);
    selectedPlayer = 0;
    
    RestoreModesRandom();
    SelectPlayer(selectedPlayer);
    SendScreenData(PLAYER_SELECTED, selectedPlayer);
    
    AmbiLight(ALL_OFF);
    AmbiLight(RED_ON);
    AnimLight(LAUNCHER_OFF);
    AnimLight(OFF_TOP_LIGHTS);
    //score = 0;
    DisplayScore(score);
    PlayRandomMusic();
    DisplayScreen(SCREEN_YOUHAVE, PRIORITY_LOW); delay(1500);
    DisplayScreen(SCREEN_XBALLS, PRIORITY_LOW); delay(1500);
    //Initialisation du nombre de balle
    EnableIncrementalScore();

  }
  
  //Came truth before every single ball play
  if(nbBall !=3  || selectedPlayer > 0) PlayRandomMusic();
  EnableFlippers();
  gameIsOn = true;
  DisableIncrementalScore();delay(50);
  DisplayScore(score);
  ProvideANewBall();
  
  //Initial screen
  DisplayScreen(SCREEN_GETREADY, PRIORITY_LOW); 
  PlaySound(VALIDATION);
  //PlaySound(GET_READY);
  
  AllLightsOff();
  
  if(nbPlayer > 1 ){
    Serial.print(selectedPlayer);
    if(selectedPlayer == 0) PlaySound(PLAYER_1);
    else if(selectedPlayer == 1) PlaySound(PLAYER_2);
    else if(selectedPlayer == 2) PlaySound(PLAYER_3);
    else if(selectedPlayer == 3) PlaySound(PLAYER_4);
    
    delay(1500);
    PlaySound(GET_READY);
    delay(1200);
    
  }else{
    PlaySound(GET_READY);
    delay(1500);
  }
  
  DisplayScreen(SCREEN_GO, PRIORITY_LOW);
  PlaySound(START_SOUND);
  
  //Initial lights
  AnimLight(FLASH_TOP_LIGHTS);
  delay(1500);
  AnimLight(OFF_TOP_LIGHTS);
  RestoreLight();
  
  ballIsInPlay = true;
  ramp1Passed = false;
  DisplayScreen(SCREEN_SCORE, PRIORITY_LOW);
  activeMode = NO_MODE;

  scoreCoef = 1;

  modeBeginTime = 0;
  bumpersState = 0;
  
  RestoreTargetStatus();
  EnableIncrementalScore();
  //Serial.print("nbBall =  "); Serial.print(nbBall); Serial.print("\n");
  
  TILT_WarningCount = 0;
  TILT_Active = false;
  TILT_Time = 10000;

  //Game is on
  while (ballIsInPlay) {
    time = millis();
    delay(1);
    
    //TARGETS HIT MANAGEMENT----------------------------------------------------------
    if (timeSinceYellowTargetHit < 1000) timeSinceYellowTargetHit++;
    if (timeSinceLeftRedTargetHit < 100) timeSinceLeftRedTargetHit++;
    if (timeSinceRightRedTargetHit < 100) timeSinceRightRedTargetHit++;
    if (timeSinceLeftGreenTargetHit < 100) timeSinceLeftGreenTargetHit++;
    if (timeSinceRightGreenTargetHit < 100) timeSinceRightGreenTargetHit++;
     
    //BUMPER HITTEN MANAGEMENT----------------------------
    if (timeSinceBumper1Hit < BUMPER_BONUS_INTERVAL) {
      timeSinceBumper1Hit++;
      if (timeSinceBumper1Hit == BUMPER_BONUS_INTERVAL) {
        AnimLight(OFF_TOP_LIGHTS);
        if (activeMode == BUMPERS_MODE) AnimLight(BUMPER_1_OFF);
        else AnimLight(BUMPER_1_ON);
      }
    }
    if (timeSinceBumper2Hit < BUMPER_BONUS_INTERVAL) {
      timeSinceBumper2Hit++;
      if (timeSinceBumper2Hit == BUMPER_BONUS_INTERVAL) {
        AnimLight(OFF_TOP_LIGHTS);
        if (activeMode == BUMPERS_MODE) AnimLight(BUMPER_2_OFF);
        else AnimLight(BUMPER_2_ON);
      }
    }
    if (timeSinceBumper3Hit < BUMPER_BONUS_INTERVAL) {
      timeSinceBumper3Hit++;
      if (timeSinceBumper3Hit == BUMPER_BONUS_INTERVAL) {
        AnimLight(OFF_TOP_LIGHTS);
        if (activeMode == BUMPERS_MODE) AnimLight(BUMPER_3_OFF);
        else AnimLight(BUMPER_3_ON);
      }
    }

    ReadSwitches();
    ReadSolenoidSwitches();
    
    if(TILT_Time < 10000) TILT_Time++;
    //TILT Management----------------------------------------
    if(TILT && TILT_Time > 2000){
      TILT_WarningCount++; 
      TILT_Time = 0;
      if(TILT_WarningCount == 1){
        DisplayScreen(SCREEN_TILT_WARNING, PRIORITY_HIGH);
        PlaySound(TILT_SOUND);
      }else if(TILT_WarningCount == 2){
        TILT_Active = true;
        DisplayScreen(SCREEN_TILT_ACTIVE, PRIORITY_LOW);
        
        PlaySound(TILT_SOUND);
        
        StopMusic();
        
        //Turn Off Lights
        AllLightsOff();
        
        
        delay(100);
        //If Ball Catched in KO2, release
        if(ballCatchedInHole2) FireKickout2();
        delay(50);
        //If Ball Catched in K01, release
        if(ballCatchedInHole1) FireKickout1();
        delay(100);
        //Disable Flippers
        DisableFlippers();
        
      }
    }

    if(TILT_Active == false){
      
      //If any switch is activated, the ball is now in play
      if (BSW1 || BSW2 || BSW3 || LKSW || RKSW || ROSW1 || ROSW2 || ROSW3 || CT || RT1 || RT2 || LT1 || LT2 || RLOSW || LLOSW || LOSW || RAMP1 || RAMP2) {
        if(ballLaunched == false){
          ballLaunched = true;
          AnimLight(LAUNCHER_OFF);
          AnimLight(OFF_TOP_LIGHTS);
        }
        
        if(ballCatchedInHole1 && ballCatchedInHole2){
          FireKickout1();
          PlaySound(KICKOUT_RELEASE_1);
          
          AnimLight(SNAKE_KO1);
          delay(100);
          FireKickout2();
          PlaySound(KICKOUT_RELEASE_2);
          AnimLight(SNAKE_KO2);
        }
      }
      
      if(time - timeSinceNewBall > 10000 && !ballLaunched){
        timeSinceNewBall = millis();
        PlaySound(STILLWAITING);
      }
      
      //RAMPS-----------------------------------------------------
      if(timeSinceRamp1 != 0 && time - timeSinceRamp1 > 3000){
        ramp1Passed = false;
        timeSinceRamp1 = 0;
      }
      if(RAMP1){
        if(!ramp1Passed){
          timeSinceRamp1 = millis();
          score += 100 * scoreCoef;
          AnimLightFor2(RAMPGATE_BLINK, 30);
          AnimLightFor2(RAMP_BLINK, 30);
          ramp1Passed = true;
        }else{
          DisplayScreen(SCREEN_RAMP_MISSED, PRIORITY_HIGH);
          PlaySound(NOPE);
          ramp1Passed = false;
        }
      }
      
      if(RAMP2){
        score += 500 * scoreCoef;
        ramp1Passed = false;
        timeSinceRamp1 = 0;
        AnimLightFor(FLASH_TOP_LIGHTS, 50);
        AmbiLight(FLASH_WHITE);
        
        if(activeMode == DOUBLE_MODE){
          PlaySound(EVERYTHING_DOUBLED);
          
          DisplayScreen(SCREEN_MODE_DOUBLE_IDLE, PRIORITY_LOW);
          delay(100);
          DisplayScreen(SCREEN_MODE_DOUBLE_COMPLETE, PRIORITY_HIGH);
    
          scoreCoef = 2;
          
          activeMode = NO_MODE;
          RestoreLight();
          PlayMusic(CANCAN_SPEED);
          delay(2000);
          AmbiLight(SNAKE_ALL_COLORS);
        }else{
          PlaySound(YIHHA);
          DisplayScreen(SCREEN_RAMP_SUCCEED, PRIORITY_HIGH); 
        }
      }
      //BUMPERS-------------------------------------------------------------------------
      if (BSW1) {
        nbBump++;
        timeSinceBumper1Hit = 0;
        score += 100* scoreCoef;
        AnimLight(BLINK_BUMPER_1);
  
        //If 3 Bumper hit in a short amount of time
        if (timeSinceBumper2Hit < BUMPER_BONUS_INTERVAL && timeSinceBumper3Hit < BUMPER_BONUS_INTERVAL) {
          AnimLight(FLASH_TOP_LIGHTS);
          AmbiLight(FLASH_WHITE);
          PlaySound(THREEBUMPERS);
          score += 500*scoreCoef;
        }else{
          PlaySound(BUMPER_3);
        }
        
        if (activeMode == BUMPERS_MODE){
          bumpersState = bumpersState | 0b001;
          SendScreenData(BUMPER_STATUS, bumpersState);
        }
      }
      if (BSW2) {
        nbBump++;
        timeSinceBumper2Hit = 0;
        score += 50* scoreCoef;
        AnimLight(BLINK_BUMPER_2);
        PlaySound(BUMPER_2);
        //If 3 Bumper hit in a short amount of time
        if (timeSinceBumper1Hit < BUMPER_BONUS_INTERVAL && timeSinceBumper3Hit < BUMPER_BONUS_INTERVAL){
          AnimLight(FLASH_TOP_LIGHTS);
          AmbiLight(FLASH_WHITE);
          PlaySound(THREEBUMPERS);
          score += 500*scoreCoef;
        }else{
          PlaySound(BUMPER_2);
        }
        
        if (activeMode == BUMPERS_MODE){
          bumpersState = bumpersState | 0b010;
          SendScreenData(BUMPER_STATUS, bumpersState);
        }
      }
  
      if (BSW3) {
        nbBump++;
        timeSinceBumper3Hit = 0;
        score += 10* scoreCoef;
        AnimLight(BLINK_BUMPER_3);

        PlaySound(BUMPER_1);
        //If 3 Bumper hit in a short amount of time
        if (timeSinceBumper2Hit < BUMPER_BONUS_INTERVAL && timeSinceBumper1Hit < BUMPER_BONUS_INTERVAL){
          AnimLight(FLASH_TOP_LIGHTS);
          AmbiLight(FLASH_WHITE);
          PlaySound(THREEBUMPERS);
          score += 500*scoreCoef;
        }else{
          PlaySound(BUMPER_1);
        }
        
        if (activeMode == BUMPERS_MODE){
          bumpersState = bumpersState | 0b100;
          SendScreenData(BUMPER_STATUS, bumpersState);
        }
      }
  
      //KICKERS-------------------------------------------------------------------------------
      if (LKSW || RKSW) {
        score += 50* scoreCoef;
        PlaySound(BOINNG);
      }
  
      //GATES-------------------------------------------------
      if (ROSW1) {
        score += 100* scoreCoef;
        if (gate1Passed) {
          PlaySound(GATE_BUZZ);
        } else {
          DisplayScreen(SCREEN_ROSW1, PRIORITY_HIGH);
          AnimLight(GATE_1_OFF);
          gate1Passed = true;
          PlaySound(GATE1);
        }
      }
      if (ROSW2) {
        score += 200* scoreCoef;
        if (gate2Passed) {
          PlaySound(GATE_BUZZ);
        } else {
          DisplayScreen(SCREEN_ROSW2, PRIORITY_HIGH);
          AnimLight(GATE_2_OFF);
          gate2Passed = true;
          PlaySound(GATE2);
        }
      }
      if (ROSW3) {
        score += 300* scoreCoef;
        if (gate3Passed) {
          PlaySound(DESIREHEY);
        } else {
          DisplayScreen(SCREEN_ROSW3, PRIORITY_HIGH);
          AnimLight(GATE_3_OFF);
          gate3Passed = true;
          PlaySound(GATE3);
        }
      }
      if (gate1Passed && gate2Passed && gate3Passed) {
        AnimLight(ALL_GATES_ON);
        AnimLightFor(FLASH_TOP_LIGHTS, 30);
        score += 1000* scoreCoef;
        DisplayScreen(SCREEN_ALL_GATES, PRIORITY_HIGH);
        PlaySound(WOULDUBEWONDERMAN);
        gate1Passed = gate2Passed = gate3Passed = false;
      }
  
      //TARGETS-----------------------------------------------------------------------
      //MIDDLE YELLOW
      if (CT && timeSinceYellowTargetHit > 100) {
        nbTarget++;
        timeSinceYellowTargetHit = 0;
        byte randSound = random(4);
        if (randSound == 0) PlaySound(KABOOM);
        else if (randSound == 1) PlaySound(WAWWHATASHOT);
        else if( randSound == 2) PlaySound(RICOCHET);
        else PlaySound(OUCH);
        
        if (activeMode == NO_MODE) {
          score += 100* scoreCoef;
          DisplayScreen(SCREEN_MIDDLE_SHOT, PRIORITY_HIGH);
          
          //If no mode only, count the targets status
          if(yellowTarget_Status == 4) {
            score += 500* scoreCoef;
            AnimLightFor(FLASH_TOP_LIGHTS, 10);
          }
          if(yellowTarget_Status < 5) yellowTarget_Status++;
          AnimLightData(DATA_YELLOW_TARGET, NumberToData(yellowTarget_Status));
          AnimLightFor(BLINK_YELLOW_TARGET, 30);
          
          //Super Psit Jackpot
          if(allTargetsHitFiveTimes){
            score += 10000* scoreCoef;
            PlaySound(CAISSE);
            RestoreTargetStatus();
            DisplayScreen(SCREEN_SCORE, PRIORITY_LOW);
            DisplayScreen(SCREEN_SUPER_PSIT_COMPLETE, PRIORITY_HIGH);
            RestoreLight();
            PlayRandomMusic();
          }
          CheckTarget();
  
        } else if (activeMode == MIDDLE_TARGET_MODE  || activeMode == ALL_TARGET_MODE) {
          score += 500* scoreCoef;
          AnimLightFor(FLASH_TOP_LIGHTS, 10);
          nb_hits++;
          SendScreenData(NB_HITS, nb_hits);
          AnimLightFor(BLINK_YELLOW_TARGET, 30);
          
        } else {
          score += 100* scoreCoef;
        }
      }
      //RIGHT RED
      if (RT1 && timeSinceRightRedTargetHit > 90) {
        nbTarget++;
        timeSinceRightRedTargetHit = 0;
        bool playSound = true;
        
        if (activeMode == NO_MODE) {
          score += 100* scoreCoef;
          DisplayScreen(SCREEN_RED_SHOT, PRIORITY_HIGH);
          
          //If no mode only, count the targets status
          if(rightRedTarget_Status == 4) {
            score += 500* scoreCoef;
            AnimLightFor(FLASH_TOP_LIGHTS, 10);
          }
          if(rightRedTarget_Status < 5) rightRedTarget_Status++;
          AnimLightData(DATA_RIGHT_RED_TARGET, NumberToData(rightRedTarget_Status));
          AnimLightFor(BLINK_RIGHT_RED_TARGET, 30);
          
          CheckTarget();
          
        } else if (activeMode == RED_TARGET_MODE  || activeMode == ALL_TARGET_MODE) {
          score += 200* scoreCoef;
          AnimLightFor(BLINK_RIGHT_RED_TARGET, 30);
          AnimLightFor(FLASH_TOP_LIGHTS, 10);
          nb_hits++;
          SendScreenData(NB_HITS, nb_hits);
        } else {
          score += 100* scoreCoef;
        }
        //PSIT MODE
        if (activeMode == NO_MODE && psitModeActive && ((psitModeState & 0b0010) >> 1 == 0)) {
          psitModeState = psitModeState | 0b0010;
          SendScreenData(PSIT_STATE, psitModeState);
          DisplayScreen(SCREEN_PSIT_MODE_STATE, PRIORITY_HIGH);
          AnimLight(LETTER_I_ON);
         
          playSound = CheckPsit();
        }
        
        if(playSound){
          byte randSound = random(2);
          if (randSound == 0) PlaySound(TARGET_1);
          else PlaySound(WHATASHOT);
        }
      }
      //LEFT RED
      if (LT1 && timeSinceLeftRedTargetHit > 90) {
        nbTarget++;
        timeSinceLeftRedTargetHit = 0;
        bool playSound = true;
        
        if (activeMode == NO_MODE) {
          score += 100* scoreCoef;
          DisplayScreen(SCREEN_RED_SHOT, PRIORITY_HIGH);
          
          //If no mode only, count the targets status
          if(leftRedTarget_Status == 4) {
            score += 500* scoreCoef;
            AnimLightFor(FLASH_TOP_LIGHTS, 10);
          }
          if(leftRedTarget_Status < 5) leftRedTarget_Status++;
          AnimLightData(DATA_LEFT_RED_TARGET, NumberToData(leftRedTarget_Status));
          AnimLightFor(BLINK_LEFT_RED_TARGET, 30);
          
          CheckTarget();
          
        } else if (activeMode == RED_TARGET_MODE  || activeMode == ALL_TARGET_MODE) {
          score += 200* scoreCoef;
          AnimLightFor(BLINK_LEFT_RED_TARGET, 30);
          AnimLightFor(FLASH_TOP_LIGHTS, 10);
          nb_hits++;
          SendScreenData(NB_HITS, nb_hits);
        } else {
          score += 100* scoreCoef;
        }
        //PSIT MODE
        if (activeMode == NO_MODE && psitModeActive && ((psitModeState & 0b0100) >> 2 == 0)) {
          psitModeState = psitModeState | 0b0100;
          SendScreenData(PSIT_STATE, psitModeState);
          DisplayScreen(SCREEN_PSIT_MODE_STATE, PRIORITY_HIGH);
          AnimLight(LETTER_S_ON);
          playSound = CheckPsit();
        }
        
        if(playSound){
          byte randSound = random(2);
          if (randSound == 0) PlaySound(TARGET_1);
          else PlaySound(YOUHITTHATRIGHT);
        }
      }
  
      //RIGHT GREEN
      if (RT2 && timeSinceRightGreenTargetHit > 90) {
        nbTarget++;
        timeSinceRightGreenTargetHit = 0;
        bool playSound = true;
        
        if (activeMode == NO_MODE) {
          score += 50* scoreCoef;
          DisplayScreen(SCREEN_GREEN_SHOT, PRIORITY_HIGH);
          
          //If no mode only, count the targets status
          if(rightGreenTarget_Status == 4) {
            score += 250* scoreCoef;
            AnimLightFor(FLASH_TOP_LIGHTS, 10);
          }
          if(rightGreenTarget_Status < 5) rightGreenTarget_Status++;
          AnimLightData(DATA_RIGHT_GREEN_TARGET, NumberToData(rightGreenTarget_Status));
          AnimLightFor(BLINK_RIGHT_GREEN_TARGET, 30);
          
          CheckTarget();
          
        } else if (activeMode == GREEN_TARGET_MODE  || activeMode == ALL_TARGET_MODE) {
          score += 100* scoreCoef;
          AnimLightFor(FLASH_TOP_LIGHTS, 20);
          AnimLightFor(BLINK_RIGHT_GREEN_TARGET, 30);
          nb_hits++;
          SendScreenData(NB_HITS, nb_hits);
        } else {
          score += 50* scoreCoef;
        }
        //PSIT MODE
        if (activeMode == NO_MODE && psitModeActive && ((psitModeState & 1) == 0)) {
          psitModeState = psitModeState | 1;
          SendScreenData(PSIT_STATE, psitModeState);
          DisplayScreen(SCREEN_PSIT_MODE_STATE, PRIORITY_HIGH);
          AnimLight(LETTER_T_ON);
          playSound = CheckPsit();
        }
        
        if(playSound){
          byte randSound = random(2);
          if (randSound == 0) PlaySound(TARGET_2);
          else PlaySound(OUCH);
        }
      }
      //LEFT GREEN
      if (LT2 && timeSinceLeftGreenTargetHit > 90) {
        nbTarget++;
        timeSinceLeftGreenTargetHit = 0;
        bool playSound = true;
        
        if (activeMode == NO_MODE) {
          score += 50* scoreCoef;
          DisplayScreen(SCREEN_GREEN_SHOT, PRIORITY_HIGH);
          
          //If no mode only, count the targets status
          if(leftGreenTarget_Status == 4) {
            score += 250* scoreCoef;
            AnimLightFor(FLASH_TOP_LIGHTS, 10);
          }
          if(leftGreenTarget_Status < 5) leftGreenTarget_Status++;
          AnimLightData(DATA_LEFT_GREEN_TARGET, NumberToData(leftGreenTarget_Status));
          AnimLightFor(BLINK_LEFT_GREEN_TARGET, 30);
          
          CheckTarget();
          
        } else if (activeMode == GREEN_TARGET_MODE  || activeMode == ALL_TARGET_MODE) {
          score += 100* scoreCoef;
          AnimLightFor(FLASH_TOP_LIGHTS, 20);
          AnimLightFor(BLINK_LEFT_GREEN_TARGET, 30);
          nb_hits++;
          SendScreenData(NB_HITS, nb_hits);
        } else {
          score += 50* scoreCoef;
        }
  
        //PSIT MODE
        if (activeMode == NO_MODE && psitModeActive && ((psitModeState & 0b1000) >> 3 == 0)) {
          psitModeState = psitModeState | 0b1000;
          SendScreenData(PSIT_STATE, psitModeState);
          DisplayScreen(SCREEN_PSIT_MODE_STATE, PRIORITY_HIGH);
          AnimLight(LETTER_P_ON);
          playSound = CheckPsit();
        }
        
        if(playSound){
          byte randSound = random(2);
          if (randSound == 0) PlaySound(TARGET_2);
          else PlaySound(OUCH);
        }
      }
  
      //LOSING SWITCHES
      if (RLOSW) {
        score += 20* scoreCoef;
        PlayRandomLoose();
      }
      if (LLOSW) {
        score += 50* scoreCoef;
        PlayRandomLoose();
      }
      //KO1-----------------------------------------------------------
      //If the ball is in Hole1, Waiting for K02, animating Ligths
      if(ballCatchedInHole1 && timeInHole1 > 0){
        if(timeInHole1 == 5000) AnimLightData(DATA_KO1, 0b00011);
        else if(timeInHole1 == 10000) AnimLightData(DATA_KO1, 0b00111);
        else if(timeInHole1 == 15000) AnimLightData(DATA_KO1, 0b01111);
        else if(timeInHole1 == 20000) AnimLightData(DATA_KO1, 0b11111);
        else if(timeInHole1 == 25000) AnimLight(BLINK_KO1);
      }
      
      
      if (KO1_Old || ballCatchedInHole1) {
        timeInHole1++;
        //KICK THE BALL OUT
        if(ballCatchedInHole2 && ballInPlay < 3){
          FireANewBall();
          delay(500);
        
        //if first ball catched & no mode, launch a ball
        }else if (timeInHole1 >= 30000 && !ballCatchedInHole2) {
          if (modeStarted == false) AnimLight(SNAKE_KO1);
          else AnimLight(KO1_OFF);
          FireKickout1();
          byte randSound = random(2);
          if (randSound == 0) PlaySound(KICKOUT_RELEASE_1);
          else PlaySound(WANG);
  
          
          score += 100* scoreCoef;
  
        //Ball actually caught in Hole 1
        } else if (timeInHole1 == 100 && ballCatchedInHole1 == false) {
          ballLaunched = true;
          AnimLight(BLINK_KO1);
          byte randSound = random(2);
          if (randSound == 0) PlaySound(KICKOUT_CATCH_1);
          else PlaySound(YOURETHEHERO);
  
          ballCatchedInHole1 = true;
          score += 100* scoreCoef;
          if (ballInPlay > 1 || activeMode != NO_MODE || ballCatchedInHole2){
            if (modeStarted == false) AnimLight(SNAKE_KO1);
            else AnimLight(KO1_OFF);
            FireKickout1();
            PlaySound(WAW);
            
            score += 100* scoreCoef;
          }else{
            AllLightsOff();
            
            DisplayScreen(SCREEN_KO1_MULTIBALL, PRIORITY_HIGH);
            
            delay(2000);
            RestoreLight();
            FireANewBall();
            PlayRandomMultiballMusic();
            
            AnimLightData(DATA_KO1, 0b00001);
          }
          
        }
      } else {
        timeInHole1 = 0;
        ballCatchedInHole1 = false;
      }
      //KO2--------------------------------------------------------------------------
      if (KO2_Old  || ballCatchedInHole2 ) {
        timeInHole2++;
        //RELEASE BALL FROM HOLE 2
        if (timeInHole2 >= 5000 && !ballCatchedInHole1) {
          FireKickout2();
          PlaySound(KICKOUT_RELEASE_2);

          // Serial.print("RELEASE BALL \n");
          if (modeStarted == false) {
  
            if (activeMode == BUMPERS_MODE) {
              modeBeginTime = millis();
              AmbiLight(BOOST_OFF);
              AmbiLight(RED_ON);
              AmbiLight(BLUE_ON);
              AmbiLight(GREEN_ON);
              AnimLight(ALL_BUMPERS_ON);
              AnimLight(MODE_3_BUMPERS);
  
              modeStarted = true;
            } else if (activeMode == GREEN_TARGET_MODE) {
              modeBeginTime = millis();
              AmbiLight(BOOST_ON);
              AmbiLight(GREEN_ON);
              AnimLight(ALL_BUMPERS_ON);
              AnimLight(MODE_GREEN_TARGETS);
              AnimLight(SNAKE_RIGHT_GREEN_TARGET);
              AnimLight(SNAKE_LEFT_GREEN_TARGET);
  
              modeStarted = true;
            } else if (activeMode == RED_TARGET_MODE) {
              modeBeginTime = millis();
              AmbiLight(BOOST_ON);
              AmbiLight(RED_ON);
              AnimLight(ALL_BUMPERS_ON);
              AnimLight(MODE_RED_TARGETS);
              AnimLight(SNAKE_RIGHT_RED_TARGET);
              AnimLight(SNAKE_LEFT_RED_TARGET);
  
              modeStarted = true;
            } else if (activeMode == MIDDLE_TARGET_MODE) {
              modeBeginTime = millis();
              AmbiLight(BOOST_ON);
              AmbiLight(YELLOW_ON);
              AnimLight(ALL_BUMPERS_ON);
              AnimLight(MODE_5_MIDDLE);
              AnimLight(SNAKE_YELLOW_TARGET);
  
              modeStarted = true;
            } else if (activeMode == ALL_TARGET_MODE) {
              modeBeginTime = millis();
              AmbiLight(BOOST_ON);
              AmbiLight(ALL_ON);
              AnimLight(ALL_BUMPERS_ON);
              AnimLight(MODE_ALL_TARGETS);
              AnimLight(SNAKE_YELLOW_TARGET); delay(100);
              AnimLight(SNAKE_RIGHT_GREEN_TARGET); delay(100);
              AnimLight(SNAKE_LEFT_GREEN_TARGET); delay(100);
              AnimLight(SNAKE_RIGHT_RED_TARGET); delay(100);
              AnimLight(SNAKE_LEFT_RED_TARGET); delay(100);
  
              modeStarted = true;
            } else if (psitModeActive && activeMode == NO_MODE) {
              RestoreLight();
              AnimLight(SNAKE_KO2);
              
            }else if(activeMode == DOUBLE_MODE){
              modeBeginTime = millis();
              RestoreLight();
              DisplayScreen(SCREEN_MODE_DOUBLE_STATE, PRIORITY_LOW);
              modeStarted = true;
            } else {
              AnimLight(SNAKE_KO2);
            }
  
  
          } else {
            AnimLight(KO2_OFF);
          }
        } else if (timeInHole2 == 100) {
          ballLaunched = true;
          //BALL CATCHED IN HOLE 2
          if (ballCatchedInHole2 == false) {
            AnimLight(BLINK_KO2);
            PlaySound(KICKOUT_CATCH_1);
            ballCatchedInHole2 = true;
            
            //Cancel Double Mode
            scoreCoef = 1;
            //Si on est en multiball ou en cours de mode, on relache direct
            if (ballInPlay > 1 || activeMode != NO_MODE || ballCatchedInHole1) timeInHole2 = 4800;
            else {
              //STARTING A MODE
              //IF THE SUPER PSIT WAS A BOUT TO BE COMPLETED= TOO LATE BRO!!!
              if(allTargetsHitFiveTimes) RestoreTargetStatus();
              
              byte hasardMode = random(10);
              while (psitModeActive && hasardMode == 6) hasardMode = random(10);
  
              if ( alreadyActivatedModes[0] && alreadyActivatedModes[1] && alreadyActivatedModes[2] && alreadyActivatedModes[3] && alreadyActivatedModes[4] &&
                   alreadyActivatedModes[5] && alreadyActivatedModes[6] && alreadyActivatedModes[7] && alreadyActivatedModes[8] && alreadyActivatedModes[9]) {
                RestoreModesRandom();
              }
              while (alreadyActivatedModes[hasardMode]) hasardMode = random(10);
              //hasardMode = 7;
              //Serial.print("Rand = "); Serial.print(hasardMode); Serial.print("\n");
              modeStarted = false;
              DisableKickers();
              if (hasardMode == 0) {
                alreadyActivatedModes[0] = true;
                activeMode = BUMPERS_MODE;
                //ALL LIGHTS OFF
                AllLightsOff();
                AnimLight(BLINK_MODES);
                timeInHole2 = 5000;
  
                DisplayScreen(SCREEN_3BUMPERS_MODE_STATE, PRIORITY_LOW);
                DisplayScreen(SCREEN_3BUMPERS_MODE, PRIORITY_HIGH);
  
                //STOP MUSIC
                StopMusic();
                bumpersState = 0;
                SendScreenData(BUMPER_STATUS, bumpersState);
                SendScreenData(COUNTDOWN, 25);
                PlaySound(BUMPERS_ROUND);
                delay(3000);
                delay(PlayRandomMusic());
  
              } else if (hasardMode == 1) {
                alreadyActivatedModes[1] = true;
                activeMode = GREEN_TARGET_MODE;
                //ALL LIGHTS OFF
                AllLightsOff();
                AnimLight(BLINK_MODES);
                timeInHole2 = 5000;
  
                DisplayScreen(SCREEN_GREEN_TARGET_MODE_STATE, PRIORITY_LOW);
                DisplayScreen(SCREEN_GREEN_TARGET_MODE, PRIORITY_HIGH);
  
                StopMusic();
                nb_hits = 0;
                SendScreenData(COUNTDOWN, 25);
                SendScreenData(NB_HITS, nb_hits);
                PlaySound(GREEN_TARGETS_ROUND);
                delay(1000);
                delay(PlayRandomMusic());
                
              } else if (hasardMode == 2) {
                alreadyActivatedModes[2] = true;
                activeMode = RED_TARGET_MODE;
                //ALL LIGHTS OFF
                AllLightsOff();
                AnimLight(BLINK_MODES);
                timeInHole2 = 4800;
  
                DisplayScreen(SCREEN_RED_TARGET_MODE_STATE, PRIORITY_LOW);
                DisplayScreen(SCREEN_RED_TARGET_MODE, PRIORITY_HIGH);
  
                StopMusic();
                nb_hits = 0;
                SendScreenData(COUNTDOWN, 25);
                SendScreenData(NB_HITS, nb_hits);
  
                PlaySound(RED_TARGET_ROUND);
                delay(3000);
                delay(PlayRandomMusic());
              } else if (hasardMode == 3) {
                alreadyActivatedModes[3] = true;
                activeMode = MIDDLE_TARGET_MODE;
                //ALL LIGHTS OFF
                AllLightsOff();
                AnimLight(BLINK_MODES);
                timeInHole2 = 5000;
  
                DisplayScreen(SCREEN_MIDDLE_TARGET_MODE_STATE, PRIORITY_LOW);
                DisplayScreen(SCREEN_MIDDLE_TARGET_MODE, PRIORITY_HIGH);
  
                StopMusic();
                nb_hits = 0;
                SendScreenData(COUNTDOWN, 25);
                SendScreenData(NB_HITS, nb_hits);
  
                byte randSound = random(2);
                if (randSound == 0) PlaySound(MIDDLE_TARGET_ROUND);
                else PlaySound(MIDDLE_SHOT_ROUND);
                delay(2000);
                delay(PlayRandomMusic());
              } else if (hasardMode == 4) {
                alreadyActivatedModes[4] = true;
                activeMode = ALL_TARGET_MODE;
                //ALL LIGHTS OFF
                AllLightsOff();
                AnimLight(BLINK_MODES);
                timeInHole2 = 5000;
  
                DisplayScreen(SCREEN_RED_TARGET_MODE_STATE, PRIORITY_LOW);
                DisplayScreen(SCREEN_ALL_TARGET_MODE, PRIORITY_HIGH);
  
                StopMusic();
                nb_hits = 0;
                SendScreenData(COUNTDOWN, 25);
                SendScreenData(NB_HITS, nb_hits);
                PlaySound(HITALLTHETARGETUCAN);
                delay(2000);
  
                delay(PlayRandomMusic());
              } else if (hasardMode == 5) {
                alreadyActivatedModes[5] = true;
                activeMode = EXTRA_BALL_MODE;
                //ALL LIGHTS OFF
                AllLightsOff();
                AnimLight(BLINK_MODES);
                DisableFlippers();
                DisplayScreen(SCREEN_BALL_GAME_INTRO, PRIORITY_LOW);
                PlaySound(EXTRABALL_ROUND);
                delay(3000);
                AnimLight(MODE_EXTRA_BALL);
                StopMusic();
                DisplayScreen(SCREEN_BALL_GAME, PRIORITY_LOW);
                PlayBallGame();
                timeInHole2 = 5000;
  
              } else if (hasardMode == 6) {
                alreadyActivatedModes[6] = true;
                AllLightsOff();
                AnimLight(BLINK_MODES);
                DisplayScreen(SCREEN_PSIT_MODE_ACTIVE, PRIORITY_LOW);
                StopMusic();
                PlaySound(PSIT_MODE);
                delay(4000);
                DisplayScreen(SCREEN_PSIT_ANIM, PRIORITY_LOW);
                delay(PlayRandomMusic());
                
                
                DisplayScreen(SCREEN_SCORE, PRIORITY_LOW);
                psitModeActive = true;
                psitModeState = 0;
                timeInHole2 = 5000;
              }else if (hasardMode == 7) {
                alreadyActivatedModes[7] = true;
                activeMode = WORD_GAME_MODE;
                //ALL LIGHTS OFF
                AllLightsOff();
                AnimLight(BLINK_MODES);
                DisableFlippers();
                DisplayScreen(SCREEN_BALL_GAME_INTRO, PRIORITY_LOW);
                PlaySound(EXTRABALL_ROUND);
                delay(3000);
                AnimLight(MODE_EXTRA_BALL);
                PlayMusic(JAZZ);
                DisplayScreen(SCREEN_WORD_GAME, PRIORITY_LOW);
                PlayWordGame();
                timeInHole2 = 5000;
                
              }else if (hasardMode == 8) {
                alreadyActivatedModes[8] = true;
                activeMode = STARWARS_MODE;
                //ALL LIGHTS OFF
                AllLightsOff();
                AnimLight(ALL_MODE_OFF);
                DisableFlippers();
                StopMusic();
                DisplayScreen(SCREEN_STARWARS_INTRO_2, PRIORITY_LOW);
                delay(3000);
                PlayMusic(STARWARSTHEME);
                delay(500);
                DisplayScreen(SCREEN_STARWARS_INTRO, PRIORITY_LOW);
                
                //Possibilite de switch l introduction star Wars
                unsigned long timeDepart = millis();
                unsigned long timeTps = millis();
                ReadSolenoidSwitches();
                while (!RIGHT_FLIPPER || !LEFT_FLIPPER) {
                  ReadSolenoidSwitches();
                  if(timeTps - timeDepart > 33000 || timeTps - timeDepart < 0) break;
                  timeTps = millis();
                  delay(100);
                }
              
                AnimLight(MODE_EXTRA_BALL);
                DisplayScreen(SCREEN_STARWARS_GAME, PRIORITY_LOW);
                PlayStarWarsGame();
                timeInHole2 = 5000;
                
              }else if (hasardMode == 9) {
                alreadyActivatedModes[9] = true;
                activeMode = DOUBLE_MODE;
                //ALL LIGHTS OFF
                AllLightsOff();
                AnimLight(BLINK_MODES);

                DisplayScreen(SCREEN_MODE_DOUBLE_INTRO, PRIORITY_LOW);
                PlaySound(DOUBLE_ROUND_INTRO);
                delay(3000);
                AnimLight(MODE_DOUBLE);
                //StopMusic();
  
                timeInHole2 = 5000;
                
              }
  
              //Pas de delais supplementaire si on est dans un jeu
              if (activeMode != EXTRA_BALL_MODE && activeMode != WORD_GAME_MODE && activeMode != STARWARS_MODE && hasardMode != 6) delay(100);
              else EnableFlippers();
            }
          }
        }
      } else {
        timeInHole2 = 0;
        ballCatchedInHole2 = false;
      }
      
      
      //MODE MANAGEMENT------------------------------------------------------------------------------------------------------
      if (activeMode != NO_MODE && modeBeginTime != 0) {
        //END OF THE MODE
        if ( millis() - timeSinceUpdateScreen > 1000) {
          unsigned long countdown = (25000 - (millis() - modeBeginTime)) / 1000;
          byte countdownByted = countdown;
          if (countdownByted <= 0 ) countdownByted = 0;
          timeSinceUpdateScreen = millis();
  
          SendScreenData(COUNTDOWN, countdownByted);
          
          //Sound for the Double Mode
          if(activeMode == DOUBLE_MODE && countdownByted % 6 == 0 ){
            PlaySound(SHOOT_THE_RAMP); 
          }
        }
        //MODE SUCCEEDED or ended
        bool modeSucceded = false;
        if (activeMode == BUMPERS_MODE) modeSucceded = (bumpersState == 0b111);
        else if (activeMode == GREEN_TARGET_MODE) modeSucceded = false;
        else if (activeMode == RED_TARGET_MODE) modeSucceded = false;
        else if (activeMode == MIDDLE_TARGET_MODE) modeSucceded = (nb_hits == 5);
        else if (activeMode == ALL_TARGET_MODE) modeSucceded = false;
        else if (activeMode == EXTRA_BALL_MODE || activeMode == WORD_GAME_MODE || activeMode == STARWARS_MODE) modeSucceded = true;
        else if (activeMode == DOUBLE_MODE) modeSucceded = false;
        
        
        if (millis() - modeBeginTime >= 25000 || modeSucceded) { //END OF THE MODE
          //Serial.print("END OF MODE\n");
          DisplayScreen(SCREEN_SCORE, PRIORITY_LOW);
          //BUMPER MODE SUCCESS extra score
          if (activeMode == BUMPERS_MODE && modeSucceded) {
            DisplayScreen(SCREEN_3BUMPERS_MODE_SUCCESS, PRIORITY_HIGH);
            score += 1000* scoreCoef;
          } else if (activeMode == MIDDLE_TARGET_MODE && modeSucceded) {
            DisplayScreen(SCREEN_3BUMPERS_MODE_SUCCESS, PRIORITY_HIGH);
            score += 1000* scoreCoef;
          }
          //Back to normal
          activeMode = NO_MODE;
          
          PlayRandomMusic();
  
          modeBeginTime = 0;
  
          bumpersState = 0;
          nb_hits = 0;
          modeStarted = false;
          EnableFlippers();
          RestoreLight();
        }
      }
  
      //Multiball Activation
      if ( nbBall == 1 && (ROSW2 || ROSW1 || ROSW3) && ballInPlay == 1) {
        DisplayScreen(SCREEN_MULTIBALL, PRIORITY_HIGH);
        PlaySound(MULTIBALL_SOUND);
        FireANewBall();
        PlayRandomMultiballMusic();
      }
    }else{ // END TILT Active
    
      //Manage KO2 Kickout event if Tilt Acrive
      if (KO2_Old  || ballCatchedInHole2 ) {
          timeInHole2++;
          //RELEASE BALL FROM HOLE 2
          if (timeInHole2 == 100) {
            FireKickout2();
          }
      }else {
        timeInHole2 = 0;
        ballCatchedInHole2 = false;
      }
     }
    DisplayScore(score);

    //Balle perdu
    if (LOSW) {
      //Serial.print("LOOSE BALL\n");
      ballInPlay = ballInPlay - 1;
      if(!TILT_Active) RestoreLight();
      //If multiball mode is done, play normal tune
      if(ballInPlay == 1 && !TILT_Active){
        PlayRandomMusic();
      }
      //Si on perd une balle mais il y en a d autres en jeu
      if(!TILT_Active){
        if (ballInPlay > 0) {
          PlaySound(LOOSE_BADLY);
        } else {
          PlayRandomLoose();
        }
      }
      if(ballCatchedInHole1 && !TILT_Active){
         FireKickout1();
         PlaySound(KICKOUT_RELEASE_1);
         AnimLight(SNAKE_KO1);
      }
    }
    if (ballInPlay == 0) {
      activeMode = NO_MODE;
      DisplayScreen(SCREEN_BALL_INTO_HOLE, PRIORITY_LOW);
      BlinkScore();
      AnimLight(BLINK_LOOSE);
      delay(3000);
      AnimLight(LOOSE_OFF);
      PlaySound(BALL_LOOSE);
      nbBall = nbBall - 1;
      scoreCoef = 1;

      DisplayScreen(SCREEN_BALLLEFT, PRIORITY_LOW);
      delay(2000);
      ballIsInPlay = false;
      modeStarted = false;
    }
  }
}

void ProvideANewBall() {
  RampABall();
  ballInPlay++;
  AnimLight(SNAKE_LAUNCHER);
  AnimLight(SNAKE_TOP_LIGHTS);
  ballLaunched = false;
  timeSinceNewBall = millis();
}

void FireANewBall() {
  ShootABall();
  ballInPlay++;
  AnimLight(SNAKE_TOP_LIGHTS);
  ballLaunched = false;
}

void AllLightsOff(){
   AmbiLight(ALL_OFF);
  AnimLight(ALL_ANIM_OFF);
  AnimLight2(ALL_ANIM_OFF); 
}
void RestoreLight() {
  AmbiLight(BOOST_ON);
  
  //Restore AmbiLights
  if (nbBall == 3) {
    AmbiLight(RED_ON);
    AmbiLight(GREEN_ON);
    AnimLight2(RAMP_BLUE);
    AmbiLight(YELLOW_ON);
  } else if (nbBall == 2) {
    AmbiLight(BLUE_ON);
    AmbiLight(RED_ON);
    AmbiLight(YELLOW_ON);
    AnimLight2(RAMP_ON);
  } else if (nbBall == 1) {
    AmbiLight(RED_ON);
    AmbiLight(YELLOW_ON);
    AnimLight2(RAMP_YELLOW);
  }
  
  if(ballInPlay > 1) AmbiLight(WHITE_ON);
  else AmbiLight(WHITE_OFF);
  
  if(allTargetsHitFiveTimes){
    AmbiLight(ALL_OFF);
    AmbiLight(YELLOW_ON);
  } 

  //AnimLights
  AnimLight(ALL_BUMPERS_ON);
  AnimLight(ALL_GATES_OFF);
  AnimLight(LOOSE_OFF);
  AnimLight(SNAKE_KO1);
  AnimLight(SNAKE_KO2);
  AnimLight(SNAKE_MODES);

  AnimLightData(DATA_YELLOW_TARGET, NumberToData(yellowTarget_Status));
  AnimLightData(DATA_RIGHT_GREEN_TARGET, NumberToData(rightGreenTarget_Status));
  AnimLightData(DATA_LEFT_GREEN_TARGET, NumberToData(leftGreenTarget_Status));
  AnimLightData(DATA_RIGHT_RED_TARGET, NumberToData(rightRedTarget_Status));
  AnimLightData(DATA_LEFT_RED_TARGET, NumberToData(leftRedTarget_Status));

  //Reallume les gate
  if (!gate1Passed) AnimLight(GATE_1_ON);
  if (!gate2Passed) AnimLight(GATE_2_ON);
  if (!gate3Passed) AnimLight(GATE_3_ON);

  if (psitModeActive == false) {
    AnimLight(SNAKE_LETTERS);
  } else {

    if ((psitModeState & 0b1000) >> 3) AnimLight(LETTER_P_ON);
    else AnimLight(BLINK_LETTER_P);
    if ((psitModeState & 0b0100) >> 2) AnimLight(LETTER_S_ON);
    else AnimLight(BLINK_LETTER_S);
    if ((psitModeState & 0b0010) >> 1) AnimLight(LETTER_I_ON);
    else AnimLight(BLINK_LETTER_I);
    if (psitModeState & 0b0001) AnimLight(LETTER_T_ON);
    else AnimLight(BLINK_LETTER_T);
  }
  
  //Mode Double
  if(activeMode == DOUBLE_MODE){
    AnimLight2(RAMPGATE_DUAL_SNAKE);
    AnimLight2(RAMP_SNAKE);
    AnimLight(MODE_DOUBLE);
  }else{
    AnimLight2(RAMPGATE_ALTERNATE);
  }
  
}

void WaitForRestart() {
  ReadSwitches();
  while (!START) {
    ReadSwitches();
    delay(100);
  }
  
  ReadSwitches();
  while(START){
    ReadSwitches();
    delay(100);
  }
  
  AnimLight(START_OFF);
}

bool CheckPsit() {
  if ( psitModeState == 0b1111) {
    DisplayScreen(SCREEN_PSIT_MODE_COMPLETE, PRIORITY_HIGH);
    psitModeActive = false;
    psitModeState = 0;
    score += 5000* scoreCoef;
    AnimLight(SNAKE_LETTERS);
    AnimLightFor(FLASH_TOP_LIGHTS, 50);
    PlaySound(PSITSUCCESS5000);
  }else if(psitModeState == 0b1110 || psitModeState == 0b1101 || psitModeState == 0b1011 || psitModeState == 0b0111){
    PlaySound(ONEMOREFOREXTRAPOINT);
    return false;
  }
  return true;
}

void CheckTarget(){
  if(leftRedTarget_Status == 5 && rightRedTarget_Status == 5 && leftGreenTarget_Status == 5 && rightGreenTarget_Status == 5 && yellowTarget_Status == 5 ){
    DisplayScreen(SCREEN_SUPER_PSIT, PRIORITY_LOW);
    PlayMusic(MISSION_IMPOSSIBLE);
    PlaySound(SUPER_PSIT_MODE);
    
    if(allTargetsHitFiveTimes == false){
      AmbiLight(ALL_OFF);
      AmbiLight(YELLOW_ON);
    }    
    allTargetsHitFiveTimes = true;
  }
}

void RestoreModesRandom() {
  for(byte i=0; i<10; i++){
    alreadyActivatedModes[i] = false;
  }
}

void RestoreTargetStatus(){
  leftRedTarget_Status = 0;
  rightRedTarget_Status = 0;
  leftGreenTarget_Status = 0;
  rightGreenTarget_Status = 0;
  yellowTarget_Status = 0;
  allTargetsHitFiveTimes = false;
  AnimLightData(DATA_YELLOW_TARGET, NumberToData(yellowTarget_Status));
  AnimLightData(DATA_RIGHT_GREEN_TARGET, NumberToData(rightGreenTarget_Status));
  AnimLightData(DATA_LEFT_GREEN_TARGET, NumberToData(leftGreenTarget_Status));
  AnimLightData(DATA_RIGHT_RED_TARGET, NumberToData(rightRedTarget_Status));
  AnimLightData(DATA_LEFT_RED_TARGET, NumberToData(leftRedTarget_Status));
}

byte NumberToData(byte number){
 if(number == 0) return 0;
 else if(number == 1) return 0b1;
 else if(number == 2) return 0b11;
 else if(number == 3) return 0b111;
 else if(number == 4) return 0b1111;
 else if(number == 5) return 0b11111;
 
}
