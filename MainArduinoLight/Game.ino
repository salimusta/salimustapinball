#define BUMPER_BONUS_INTERVAL 200

unsigned long score;
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
bool alreadyActivatedModes[9] = {false, false, false, false, false, false, false, false, false};

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

//Double Mode
byte scoreCoef = 1;


char name[11];

//Timings
unsigned long timeSinceNewBall = 0;

void ManageGame() {

  AmbiLight(ALL_OFF);
  AnimLight(ALL_ANIM_OFF);
  AnimLight2(ALL_ANIM_OFF);
  
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
      delay(4000);
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
    delay(3000);
    WaitForRestart();
    
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
  AnimLight(ALL_ANIM_OFF);
  AnimLight2(ALL_ANIM_OFF);
  AmbiLight(ALL_OFF);
  delay(1500);
  DisplayScreen(SCREEN_GO, PRIORITY_LOW);
  
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
  
  //Game is on
  while (ballIsInPlay) {
    time = millis();
    delay(10);
    
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
        ballCatchedInHole1 = false;
        timeInHole1 = 0;
        AnimLight(SNAKE_KO1);
        delay(100);
        FireKickout2();
        PlaySound(KICKOUT_RELEASE_2);
        ballCatchedInHole2 = false;
        timeInHole2 = 0;
        AnimLight(SNAKE_KO2);
      }
    }
    
    if(time - timeSinceNewBall > 10000 && !ballLaunched){
      timeSinceNewBall = millis();
      PlaySound(STILLWAITING);
    }
    
    //RAMPS-----------------------------------------------------
    if(RAMP1){
      if(!ramp1Passed){
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
      AnimLightFor(FLASH_TOP_LIGHTS, 50);
      
      if(activeMode == DOUBLE_MODE){
        PlaySound(EVERYTHING_DOUBLED);
        DisplayScreen(SCREEN_MODE_DOUBLE_COMPLETE, PRIORITY_LOW);

        scoreCoef = 2;
        //DisplayScreen(SCREEN_MODE_DOUBLE_IDLE, PRIORITY_LOW);
        
        activeMode = NO_MODE;
        RestoreLight();
        PlayRandomMusic();
        
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
    if (CT && timeSinceYellowTargetHit > 20) {
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
    if (RT1) {
      nbTarget++;
      timeSinceRightRedTargetHit = 0;
      byte randSound = random(2);
      if (randSound == 0) PlaySound(TARGET_1);
      else PlaySound(WHATASHOT);

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
       
        CheckPsit();
      }
    }
    //LEFT RED
    if (LT1) {
      nbTarget++;
      timeSinceLeftRedTargetHit = 0;
      byte randSound = random(2);
      if (randSound == 0) PlaySound(TARGET_1);
      else PlaySound(YOUHITTHATRIGHT);
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
        CheckPsit();
      }
    }

    //RIGHT GREEN
    if (RT2) {
      nbTarget++;
      timeSinceRightGreenTargetHit = 0;
      byte randSound = random(2);
      if (randSound == 0) PlaySound(TARGET_2);
      else PlaySound(OUCH);
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
        CheckPsit();
      }
    }
    //LEFT GREEN
    if (LT2) {
      nbTarget++;
      timeSinceLeftGreenTargetHit = 0;
      byte randSound = random(2);
      if (randSound == 0) PlaySound(TARGET_2);
      else PlaySound(OUCH);
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
        CheckPsit();
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
      if(timeInHole1 == 500) AnimLightData(DATA_KO1, 0b00011);
      else if(timeInHole1 == 1000) AnimLightData(DATA_KO1, 0b00111);
      else if(timeInHole1 == 1500) AnimLightData(DATA_KO1, 0b01111);
      else if(timeInHole1 == 2000) AnimLightData(DATA_KO1, 0b11111);
      else if(timeInHole1 == 2500) AnimLight(BLINK_KO1);
    }
    
    
    if (KO1_Old || ballCatchedInHole1) {
      timeInHole1++;
      //KICK THE BALL OUT
      if(ballCatchedInHole2 && ballInPlay < 3){
        FireANewBall();
        delay(500);
      
      //if first ball catched & no mode, launch a ball
      }else if (timeInHole1 >= 3000 && !ballCatchedInHole2) {
        if (modeStarted == false) AnimLight(SNAKE_KO1);
        else AnimLight(KO1_OFF);
        FireKickout1();
        byte randSound = random(2);
        if (randSound == 0) PlaySound(KICKOUT_RELEASE_1);
        else PlaySound(WANG);

        ballCatchedInHole1 = false;
        timeInHole1 = 0;
        score += 100* scoreCoef;

      //Ball actually caught in Hole 1
      } else if (timeInHole1 == 20 && ballCatchedInHole1 == false) {
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
          ballCatchedInHole1 = false;
          timeInHole1 = 0;
          score += 100* scoreCoef;
        }else{
          AmbiLight(ALL_OFF);
          AnimLight(ALL_ANIM_OFF);
          AnimLight2(ALL_ANIM_OFF);
          
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
      if (timeInHole2 >= 300 && !ballCatchedInHole1) {
        FireKickout2();
        byte randSound = random(2);
        if (randSound == 0) PlaySound(KICKOUT_RELEASE_2);
        else PlaySound(YOUMOVE);
        
        ballCatchedInHole2 = false;
        timeInHole2 = 0;
        // Serial.print("RELEASE BALL \n");
        if (modeStarted == false) {

          if (activeMode == BUMPERS_MODE) {
            modeBeginTime = millis();
            AmbiLight(RED_ON);
            AmbiLight(BLUE_ON);
            AnimLight(ALL_BUMPERS_ON);
            AnimLight(MODE_3_BUMPERS);

            modeStarted = true;
          } else if (activeMode == GREEN_TARGET_MODE) {
            modeBeginTime = millis();
            AmbiLight(GREEN_ON);
            AnimLight(ALL_BUMPERS_ON);
            AnimLight(MODE_GREEN_TARGETS);
            AnimLight(SNAKE_RIGHT_GREEN_TARGET);
            AnimLight(SNAKE_LEFT_GREEN_TARGET);

            modeStarted = true;
          } else if (activeMode == RED_TARGET_MODE) {
            modeBeginTime = millis();
            AmbiLight(RED_ON);
            AnimLight(ALL_BUMPERS_ON);
            AnimLight(MODE_RED_TARGETS);
            AnimLight(SNAKE_RIGHT_RED_TARGET);
            AnimLight(SNAKE_LEFT_RED_TARGET);

            modeStarted = true;
          } else if (activeMode == MIDDLE_TARGET_MODE) {
            modeBeginTime = millis();
            AmbiLight(YELLOW_ON);
            AnimLight(ALL_BUMPERS_ON);
            AnimLight(MODE_5_MIDDLE);
            AnimLight(SNAKE_YELLOW_TARGET);

            modeStarted = true;
          } else if (activeMode == ALL_TARGET_MODE) {
            modeBeginTime = millis();
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
          } else {
            AnimLight(SNAKE_KO2);
          }


        } else {
          AnimLight(KO2_OFF);
        }
      } else if (timeInHole2 == 20) {
        //BALL CATCHED IN HOLE 2
        if (ballCatchedInHole2 == false) {
          AnimLight(BLINK_KO2);
          PlaySound(KICKOUT_CATCH_1);
          ballCatchedInHole2 = true;
          //Si on est en multiball ou en cours de mode, on relache direct
          if (ballInPlay > 1 || activeMode != NO_MODE || ballCatchedInHole1) timeInHole2 = 280;
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
            hasardMode = 7;
            modeStarted = false;
            DisableKickers();
            if (hasardMode == 0) {
              alreadyActivatedModes[0] = true;
              activeMode = BUMPERS_MODE;
              //ALL LIGHTS OFF
              AmbiLight(ALL_OFF);
              AnimLight(ALL_ANIM_OFF);
              AnimLight2(ALL_ANIM_OFF);
              AnimLight(BLINK_MODES);
              timeInHole2 = 300;

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
              AmbiLight(ALL_OFF);
              AnimLight(ALL_ANIM_OFF);
              AnimLight2(ALL_ANIM_OFF);
              AnimLight(BLINK_MODES);
              timeInHole2 = 300;

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
              AmbiLight(ALL_OFF);
              AnimLight(ALL_ANIM_OFF);
              AnimLight2(ALL_ANIM_OFF);
              AnimLight(BLINK_MODES);
              timeInHole2 = 200;

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
              AmbiLight(ALL_OFF);
              AnimLight(ALL_ANIM_OFF);
              AnimLight2(ALL_ANIM_OFF);
              AnimLight(BLINK_MODES);
              timeInHole2 = 300;

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
              AmbiLight(ALL_OFF);
              AnimLight(ALL_ANIM_OFF);
              AnimLight2(ALL_ANIM_OFF);
              AnimLight(BLINK_MODES);
              timeInHole2 = 300;

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
              AmbiLight(ALL_OFF);
              AnimLight(ALL_ANIM_OFF);
              AnimLight2(ALL_ANIM_OFF);
              AnimLight(BLINK_MODES);
              DisableFlippers();
              DisplayScreen(SCREEN_BALL_GAME_INTRO, PRIORITY_LOW);
              PlaySound(EXTRABALL_ROUND);
              delay(3000);
              AnimLight(MODE_EXTRA_BALL);
              StopMusic();
              DisplayScreen(SCREEN_BALL_GAME, PRIORITY_LOW);
              PlayBallGame();
              timeInHole2 = 300;

            } else if (hasardMode == 6) {
              alreadyActivatedModes[6] = true;
              AmbiLight(ALL_OFF);
              AnimLight(ALL_ANIM_OFF);
              AnimLight2(ALL_ANIM_OFF);
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
              timeInHole2 = 300;
            }else if (hasardMode == 7) {
              alreadyActivatedModes[7] = true;
              activeMode = WORD_GAME_MODE;
              //ALL LIGHTS OFF
              AmbiLight(ALL_OFF);
              AnimLight(ALL_ANIM_OFF);
              AnimLight2(ALL_ANIM_OFF);
              AnimLight(BLINK_MODES);
              DisableFlippers();
              DisplayScreen(SCREEN_BALL_GAME_INTRO, PRIORITY_LOW);
              PlaySound(EXTRABALL_ROUND);
              delay(3000);
              AnimLight(MODE_EXTRA_BALL);
              PlayMusic(JAZZ);
              DisplayScreen(SCREEN_WORD_GAME, PRIORITY_LOW);
              PlayWordGame();
              timeInHole2 = 300;
              
            }else if (hasardMode == 8) {
              alreadyActivatedModes[8] = true;
              activeMode = STARWARS_MODE;
              //ALL LIGHTS OFF
              AmbiLight(ALL_OFF);
              AnimLight(ALL_ANIM_OFF);
              AnimLight2(ALL_ANIM_OFF);
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
              timeInHole2 = 300;
              
            }else if (hasardMode == 9) {
              alreadyActivatedModes[9] = true;
              activeMode = DOUBLE_MODE;
              //ALL LIGHTS OFF
              AmbiLight(ALL_OFF);
              AnimLight(ALL_ANIM_OFF);
              AnimLight2(ALL_ANIM_OFF);
              AnimLight(BLINK_MODES);
              DisableFlippers();
              DisplayScreen(SCREEN_MODE_DOUBLE_INTRO, PRIORITY_LOW);
              PlaySound(DOUBLE_ROUND_INTRO);
              delay(3000);
              AnimLight(MODE_DOUBLE);
              //StopMusic();

              timeInHole2 = 300;
              
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
        if(countdownByted % 6 == 0 ){
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
      FireANewBall();
      PlayRandomMultiballMusic();
    }

    DisplayScore(score);

    //Balle perdu
    if (LOSW) {
      ballInPlay = ballInPlay - 1;
      
      //If multiball mode is done, play normal tune
      if(ballInPlay == 1){
        PlayRandomMusic();
      }
      //Si on perd une balle mais il y en a d autres en jeu
      if (ballInPlay > 0) {
        PlaySound(LOOSE_BADLY);
      } else {
        PlayRandomLoose();
      }
      if(ballCatchedInHole1){
         FireKickout1();
         PlaySound(KICKOUT_RELEASE_1);
         AnimLight(SNAKE_KO1);
         ballCatchedInHole1 = false;
         timeInHole1 = 0;
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

void RestoreLight() {
  //Restore AmbiLights
  if (nbBall == 3) {
    AmbiLight(RED_ON);
    AmbiLight(GREEN_ON);
    AnimLight2(RAMP_BLUE);
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
}

void CheckPsit() {
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
  }
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

  alreadyActivatedModes[0] = false;
  alreadyActivatedModes[1] = false;
  alreadyActivatedModes[2] = false;
  alreadyActivatedModes[3] = false;
  alreadyActivatedModes[4] = false;
  alreadyActivatedModes[5] = false;
  alreadyActivatedModes[6] = false;
  alreadyActivatedModes[7] = false;
  alreadyActivatedModes[8] = false;
  alreadyActivatedModes[9] = false;
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
