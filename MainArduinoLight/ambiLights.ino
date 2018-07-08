
void AmbiLight(byte light){
  Wire.beginTransmission(6);
  Wire.write(light);
  Wire.endTransmission();
}

void CloseGate() {
  Wire.beginTransmission(6);
  Wire.write(GATE_ON);
  Wire.endTransmission();
  gateClosed = true;
  delay(100);
}

void OpenGate() {
  Wire.beginTransmission(6);
  Wire.write(GATE_OFF);
  Wire.endTransmission();
  gateClosed = false;
  ballInRamp = 0;
  delay(100);
}

void LeaveOneBall() {
  Wire.beginTransmission(6);
  Wire.write(GATE_ONE_BALL);
  Wire.endTransmission();
  if( ballInRamp > 0 && ballInRamp < 100) ballInRamp = ballInRamp -1;
  else ballInRamp = 0;
 
}
void TestAmbiLights(){
  AmbiLight(ALL_OFF);
  printLine("Ambi Lights Test", ".....");
  AmbiLight(RED_ON); delay(2000); AmbiLight(RED_OFF);

  AmbiLight(GREEN_ON); delay(2000); AmbiLight(GREEN_OFF); 

  AmbiLight(YELLOW_ON); delay(2000); AmbiLight(YELLOW_OFF); 

  AmbiLight(BLUE_ON); delay(2000); AmbiLight(BLUE_OFF);

  AmbiLight(ALL_ON); delay(2000); AmbiLight(ALL_OFF);
  
  OpenGate(); delay(2000); CloseGate(); delay(2000); OpenGate();
}
