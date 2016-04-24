
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
  
  /*
  AnimLight(FLASH_TOP_LIGHTS); delay(2000); AnimLight(LIGHT_TOP_LIGHTS); delay(2000); AnimLight(ALTERN_TOP_LIGHTS); delay(2000); AnimLight(OFF_TOP_LIGHTS); delay(2000);
  AnimLight(SNAKE_LEFT_GREEN_TARGET); delay(2000); AnimLight(BLINK_LEFT_GREEN_TARGET); delay(2000); AnimLight(OFF_LEFT_GREEN_TARGET); delay(2000);
  AnimLight(SNAKE_LEFT_RED_TARGET); delay(2000); AnimLight(BLINK_LEFT_RED_TARGET); delay(2000); AnimLight(OFF_LEFT_RED_TARGET); delay(2000);
  AnimLight(SNAKE_YELLOW_TARGET); delay(2000); AnimLight(BLINK_YELLOW_TARGET); delay(2000); AnimLight(OFF_YELLOW_TARGET); delay(2000);
  AnimLight(MODE_3_BUMPERS); delay(2000); AnimLight(MODE_5_MIDDLE); delay(2000); AnimLight(MODE_GREEN_TARGETS); delay(2000); AnimLight(MODE_EXTRA_BALL); delay(2000);
  AnimLight(MODE_ALL_TARGETS); delay(2000); AnimLight(MODE_DOUBLE); delay(2000); AnimLight(MODE_RED_TARGETS); delay(2000); AnimLight(MODE_PSIT); delay(2000);
  AnimLight(SNAKE_MODES); delay(2000); AnimLight(BLINK_MODES); delay(2000); AnimLight(ALL_MODE_OFF); delay(2000);
  AnimLight(LETTER_P_ON); delay(2000); AnimLight(LETTER_S_ON); delay(2000); AnimLight(LETTER_I_ON); delay(2000); AnimLight(LETTER_T_ON); delay(2000); AnimLight(ALL_LETTERS_OFF); delay(2000);
  AnimLight(BUMPER_1_ON); delay(2000); AnimLight(BLINK_BUMPER_1); delay(2000); AnimLight(BUMPER_1_OFF); delay(2000);
  AnimLight(BUMPER_2_ON); delay(2000); AnimLight(BLINK_BUMPER_2); delay(2000); AnimLight(BUMPER_2_OFF); delay(2000);
  AnimLight(BUMPER_3_ON); delay(2000); AnimLight(BLINK_BUMPER_3); delay(2000); AnimLight(BUMPER_3_OFF); delay(2000);
  AnimLight(ALL_BUMPERS_ON); delay(2000); AnimLight(ALL_BUMPERS_OFF); delay(2000);
  AnimLight(GATE_1_ON); delay(2000); AnimLight(GATE_1_OFF); delay(2000); AnimLight(GATE_2_ON); delay(2000); AnimLight(GATE_2_OFF); delay(2000);
  AnimLight(GATE_3_ON); delay(2000); AnimLight(GATE_3_OFF); delay(2000); AnimLight(ALL_GATES_ON); delay(2000); AnimLight(ALL_GATES_OFF); delay(2000);
  AnimLight(SNAKE_LAUNCHER); delay(2000); AnimLight(LAUNCHER_OFF); delay(2000); AnimLight(BLINK_LOOSE); delay(2000); AnimLight(LOOSE_OFF); delay(2000);
  AnimLight(SNAKE_KO1); delay(2000); AnimLight(BLINK_KO1); delay(2000); AnimLight(KO1_OFF); delay(2000);
  AnimLight(SNAKE_KO2); delay(2000); AnimLight(BLINK_KO2); delay(2000); AnimLight(KO2_OFF); delay(2000);
  */
  
}
