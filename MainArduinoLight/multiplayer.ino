

typedef struct {
  unsigned long score;
  byte nbBall;
  bool gate1Passed;
  bool gate2Passed;
  bool gate3Passed;
  bool psitModeActive;
  byte psitModeState;
  short nbBump;
  short nbTarget;
  bool alreadyActivatedModes[9] = {false, false, false, false, false, false, false, false, false};
  byte leftRedTarget_Status;
  byte rightRedTarget_Status;
  byte leftGreenTarget_Status;
  byte rightGreenTarget_Status;
  byte yellowTarget_Status;

}Player;


Player players[4];

void initPlayers(){
  score = 0;
  nbBall = 3;
  gate1Passed = gate2Passed = gate3Passed = false;
  psitModeActive = false;
  psitModeState = nbBump = nbTarget = 0;
  for(byte i = 0; i < 4; i++){
    players[i].score = 0;
    players[i].nbBall = 3;
    players[i].gate1Passed = players[i].gate2Passed = players[i].gate3Passed = false;
    players[i].psitModeActive = false;
    players[i].psitModeState = 0;
    players[i].nbBump = 0;
    players[i].nbTarget = 0;
    players[i].leftRedTarget_Status = 0;
    players[i].rightRedTarget_Status = 0;
    players[i].leftGreenTarget_Status = 0;
    players[i].rightGreenTarget_Status = 0;
    players[i].yellowTarget_Status = 0;
    for(byte j = 0; j < 9; j++) players[i].alreadyActivatedModes[j] = false;
  }
}

void SelectPlayer(byte index){
  //Save the current player status
  players[currentPlayer].score = score;
  players[currentPlayer].nbBall = nbBall;
  players[currentPlayer].gate1Passed = gate1Passed;
  players[currentPlayer].gate2Passed = gate2Passed;
  players[currentPlayer].gate3Passed = gate3Passed;
  players[currentPlayer].psitModeActive = psitModeActive;
  players[currentPlayer].psitModeState = psitModeState;
  players[currentPlayer].nbBump = nbBump;
  players[currentPlayer].nbTarget = nbTarget;
  for(byte j = 0; j < 9; j++){
    players[currentPlayer].alreadyActivatedModes[j] = alreadyActivatedModes[j];
  }
   players[currentPlayer].leftRedTarget_Status = leftRedTarget_Status;
   players[currentPlayer].rightRedTarget_Status = rightRedTarget_Status;
   players[currentPlayer].leftGreenTarget_Status = leftGreenTarget_Status;
   players[currentPlayer].rightGreenTarget_Status = rightGreenTarget_Status;
   players[currentPlayer].yellowTarget_Status = yellowTarget_Status;
  
  
  //Load the selected player status
  score = players[index].score;
  nbBall = players[index].nbBall;
  gate1Passed = players[index].gate1Passed;
  gate2Passed = players[index].gate2Passed;
  gate3Passed = players[index].gate3Passed;
  psitModeActive = players[index].psitModeActive;
  psitModeState = players[index].psitModeState;
  nbBump = players[index].nbBump;
  nbTarget = players[index].nbTarget;
  for(byte j = 0; j < 9; j++){
    alreadyActivatedModes[j] = players[currentPlayer].alreadyActivatedModes[j];
  }
  leftRedTarget_Status = players[index].leftRedTarget_Status;
  rightRedTarget_Status = players[index].rightRedTarget_Status;
  leftGreenTarget_Status = players[index].leftGreenTarget_Status;
  rightGreenTarget_Status = players[index].rightGreenTarget_Status;
  yellowTarget_Status = players[index].yellowTarget_Status;

  currentPlayer = index;
}




