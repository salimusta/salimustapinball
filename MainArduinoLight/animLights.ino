
void AnimLight(byte light){
  Wire.beginTransmission(5);
  Wire.write(light);
  Wire.endTransmission();
}
void AnimLightFor(byte light, byte duration){
  Wire.beginTransmission(5);
  Wire.write(light);
  Wire.write(duration);
  Wire.endTransmission();
}
void AnimLightData(byte light, byte data){
  Wire.beginTransmission(5);
  Wire.write(light);
  Wire.write(0);
  Wire.write(data);
  Wire.endTransmission();
}

void AnimLight2(byte light){
  Wire.beginTransmission(7);
  Wire.write(light);
  Wire.endTransmission();
}
void AnimLightFor2(byte light, byte duration){
  Wire.beginTransmission(7);
  Wire.write(light);
  Wire.write(duration);
  Wire.endTransmission();
}
void AnimLightData2(byte light, byte data){
  Wire.beginTransmission(7);
  Wire.write(light);
  Wire.write(0);
  Wire.write(data);
  Wire.endTransmission();
}

void TestAnimLights(){
  int delayMs = 1000;
  int delayMs2 = 500;
  
  //Flash Top
  AnimLight(FLASH_TOP_LIGHTS); delay(delayMs); AnimLight(LIGHT_TOP_LIGHTS); delay(delayMs); AnimLight(ALTERN_TOP_LIGHTS); delay(delayMs); AnimLight(OFF_TOP_LIGHTS);
  
  //Targets
  AnimLight(SNAKE_LEFT_GREEN_TARGET); AnimLight(SNAKE_LEFT_RED_TARGET); AnimLight(SNAKE_YELLOW_TARGET); AnimLight(SNAKE_RIGHT_GREEN_TARGET); AnimLight(SNAKE_RIGHT_RED_TARGET);
  delay(delayMs);
  AnimLight(BLINK_LEFT_GREEN_TARGET); AnimLight(BLINK_LEFT_RED_TARGET); AnimLight(BLINK_YELLOW_TARGET); AnimLight(BLINK_RIGHT_GREEN_TARGET); AnimLight(BLINK_RIGHT_RED_TARGET);
  delay(delayMs);
  AnimLight(OFF_LEFT_GREEN_TARGET); AnimLight(OFF_LEFT_RED_TARGET); AnimLight(OFF_YELLOW_TARGET); AnimLight(OFF_RIGHT_GREEN_TARGET); AnimLight(OFF_RIGHT_RED_TARGET);
  delay(delayMs);
  
  //Modes
  AnimLight(MODE_3_BUMPERS); delay(delayMs2); AnimLight(MODE_5_MIDDLE); delay(delayMs2); AnimLight(MODE_GREEN_TARGETS); delay(delayMs2); AnimLight(MODE_EXTRA_BALL); delay(delayMs2);
  AnimLight(MODE_ALL_TARGETS); delay(delayMs2); AnimLight(MODE_DOUBLE); delay(delayMs2); AnimLight(MODE_RED_TARGETS); delay(delayMs2); AnimLight(MODE_PSIT); delay(delayMs2);
  AnimLight(SNAKE_MODES); delay(delayMs); AnimLight(BLINK_MODES); delay(delayMs); AnimLight(ALL_MODE_OFF); delay(delayMs);
  
  //Letters
  AnimLight(LETTER_P_ON); delay(delayMs2); AnimLight(LETTER_S_ON); delay(delayMs2); AnimLight(LETTER_I_ON); delay(delayMs2); AnimLight(LETTER_T_ON); delay(delayMs2);
  AnimLight(ALL_LETTERS_OFF); delay(delayMs2); AnimLight(SNAKE_LETTERS); delay(delayMs2); AnimLight(ALL_LETTERS_OFF);
  
  //Bumpers
  AnimLight(BUMPER_1_ON); delay(delayMs); AnimLight(BLINK_BUMPER_1); delay(delayMs); AnimLight(BUMPER_1_OFF); delay(delayMs);
  AnimLight(BUMPER_2_ON); delay(delayMs); AnimLight(BLINK_BUMPER_2); delay(delayMs); AnimLight(BUMPER_2_OFF); delay(delayMs);
  AnimLight(BUMPER_3_ON); delay(delayMs); AnimLight(BLINK_BUMPER_3); delay(delayMs); AnimLight(BUMPER_3_OFF); delay(delayMs);
  AnimLight(ALL_BUMPERS_ON); delay(delayMs); AnimLight(ALL_BUMPERS_OFF); delay(delayMs);
  
  //Gates
  AnimLight(GATE_1_ON); delay(delayMs); AnimLight(GATE_1_OFF); delay(delayMs); AnimLight(GATE_2_ON); delay(delayMs); AnimLight(GATE_2_OFF); delay(delayMs);
  AnimLight(GATE_3_ON); delay(delayMs); AnimLight(GATE_3_OFF); delay(delayMs); AnimLight(ALL_GATES_ON); delay(delayMs); AnimLight(ALL_GATES_OFF); delay(delayMs);
  
  //Launcher
  AnimLight(SNAKE_LAUNCHER); delay(delayMs); AnimLight(LAUNCHER_OFF); delay(delayMs);
  
  //Lose
  AnimLight(BLINK_LOOSE); delay(delayMs); AnimLight(LOOSE_OFF); delay(delayMs);
  
  //Kickers Out
  AnimLight(SNAKE_KO1); delay(delayMs); AnimLight(BLINK_KO1); delay(delayMs); AnimLight(KO1_OFF); delay(delayMs);
  AnimLight(SNAKE_KO2); delay(delayMs); AnimLight(BLINK_KO2); delay(delayMs); AnimLight(KO2_OFF); delay(delayMs);
  
  //RAMP GATE
  AnimLight2(RAMPGATE_BLINK); delay(delayMs); AnimLight2(RAMPGATE_SNAKE); delay(delayMs); AnimLight2(RAMPGATE_ON); delay(delayMs); AnimLight2(RAMPGATE_OFF); delay(delayMs);
  
  //RAMP
  AnimLight2(RAMP_BLUE); delay(delayMs); AnimLight2(RAMP_YELLOW); delay(delayMs); AnimLight2(RAMP_ALTERNATE); delay(delayMs); AnimLight2(RAMP_OFF); delay(delayMs);
  
  //ALL
  AnimLight(ANIM_ALL); delay(delayMs);
  AnimLight(ALL_ANIM_OFF); delay(delayMs);

}
