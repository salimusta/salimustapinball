

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

}Player;


Player players[4];

void initPlayers(byte nb){
  Serial.print("initPlayers =  "); Serial.print(nb); Serial.print("\n");
  score = 0;
  nbBall = 3;
  gate1Passed = gate2Passed = gate3Passed = false;
  psitModeActive = false;
  psitModeState = nbBump = nbTarget = 0;
  for(byte i = 0; i < nb; i++){
    players[i].score = 0;
    players[i].nbBall = 3;
    players[i].gate1Passed = players[i].gate2Passed = players[i].gate3Passed = false;
    players[i].psitModeActive = false;
    players[i].psitModeState = 0;
    players[i].nbBump = 0;
    players[i].nbTarget = 0;

    for(byte j = 0; j < 9; j++) players[i].alreadyActivatedModes[j] = false;
  }

}

void SelectPlayer(byte index){
  //Save the current player status
  Serial.print("Sel Player "); Serial.print(index); Serial.print("\n");
  Serial.print("old "); Serial.print(currentPlayer); Serial.print("\n");
  
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

  currentPlayer = index;
}




