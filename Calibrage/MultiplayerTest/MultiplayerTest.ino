unsigned long score;
byte nbBall;
bool gate1Passed;
bool gate2Passed;
bool gate3Passed;
bool psitModeActive;
byte psitModeState;
short nbBump;
short nbTarget;

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

}Player;

byte nbPlayer = 1;
byte currentPlayer = 0;
Player players[4];


void initPlayers(){
  for(byte i = 0; i < 4; i++){
    players[i].score = 0;
    players[i].nbBall = 3;
    players[i].gate1Passed = players[i].gate2Passed = players[i].gate3Passed = false;
    players[i].psitModeActive = false;
    players[i].psitModeState = 0;
    players[i].nbBump = 0;
    players[i].nbTarget = 0;
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
  
  currentPlayer = index;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  initPlayers();
}

void loop() {
  // put your main code here, to run repeatedly:
  SelectPlayer(0);
  score+=100;
  SelectPlayer(1);
  score+=50;
  score+=50;
  SelectPlayer(0);
  score+=100;
  
  SelectPlayer(0);
  Serial.print("score0="); Serial.print(score);Serial.print("\n");

  SelectPlayer(1);
  Serial.print("score1="); Serial.print(score);Serial.print("\n");
  while(1);

}
