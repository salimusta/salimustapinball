
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
void TestAnimLights(){
  printLine("Anim Lights Test", "On Going...");
  Serial.print("ALL OFF\n");
  AmbiLight(ALL_OFF);
  AnimLight(ALL_ANIM_OFF);
  delay(2000);
  /*
  AnimLight(ANIM_ALL); delay(2000);
  AnimLight(ALL_ANIM_OFF); delay(2000);
  
  AnimLight(OFF_TOP_LIGHTS); delay(2000); 
  AnimLightFor(FLASH_TOP_LIGHTS, 30); delay(3000);
  AnimLightFor(LIGHT_TOP_LIGHTS, 20); delay(3000);
  AnimLightFor(ALTERN_TOP_LIGHTS, 100); delay(5000);
  
  AnimLight(LIGHT_TOP_LIGHTS); delay(2000);
  AnimLightFor(FLASH_TOP_LIGHTS, 30); delay(3000);
  AnimLightFor(OFF_TOP_LIGHTS, 30); delay(3000);
  */
  /*
  AnimLight(OFF_RIGHT_GREEN_TARGET); delay(2000);
  AnimLightFor(BLINK_RIGHT_GREEN_TARGET, 30); delay(3000);
  AnimLightFor(SNAKE_RIGHT_GREEN_TARGET, 30); delay(3000);
  
  AnimLight(SNAKE_RIGHT_GREEN_TARGET); delay(2000);
  AnimLightFor(BLINK_RIGHT_GREEN_TARGET, 30); delay(3000);
  AnimLight(OFF_RIGHT_GREEN_TARGET); delay(2000);
  */
  /*
  AnimLight(OFF_LEFT_GREEN_TARGET); delay(2000);
  AnimLightFor(BLINK_LEFT_GREEN_TARGET, 30); delay(3000);
  AnimLightFor(SNAKE_LEFT_GREEN_TARGET, 30); delay(3000);
  
  AnimLight(SNAKE_LEFT_GREEN_TARGET); delay(2000);
  AnimLightFor(BLINK_LEFT_GREEN_TARGET, 30); delay(3000);
  AnimLight(OFF_LEFT_GREEN_TARGET); delay(2000);
  */
  /*
 AnimLight(ALL_LETTERS_OFF); delay(2000);
 AnimLight(ALL_LETTERS_ON); delay(2000);
 AnimLight(ALL_LETTERS_OFF); delay(2000);
 
 AnimLight(BLINK_LETTER_P); delay(2000);
 
 AnimLight(LETTER_P_ON);
 AnimLight(BLINK_LETTER_S); delay(2000);
 
 AnimLight(LETTER_S_ON);
 AnimLight(BLINK_LETTER_I); delay(2000);
 
 AnimLight(LETTER_I_ON);
 AnimLight(BLINK_LETTER_T); delay(2000);
 
 AnimLight(LETTER_T_ON);
 AnimLight(ALL_LETTERS_ON); delay(2000);
 AnimLightFor(SNAKE_LETTERS, 50); delay(2000);
  */
  /*
  AnimLight(ALL_MODE_OFF); delay(2000);
  AnimLightFor(ALL_MODE_ON, 30); delay(3000);
  AnimLight(ALL_MODE_OFF); delay(2000);
  
  AnimLight(MODE_3_BUMPERS); delay(3000);
  AnimLight(MODE_5_MIDDLE); delay(3000);
  AnimLightFor(SNAKE_MODES, 30); delay(3000);
  AnimLightFor(SNAKE_MODES, 30); delay(3000);
  AnimLight(ALL_MODE_OFF); delay(3000);
  
  AnimLight(MODE_DOUBLE); delay(3000);
  AnimLightFor(BLINK_MODES, 30); delay(3000);
  */
  /*
  AnimLight(ALL_BUMPERS_OFF); delay(3000);
  AnimLight(ALL_BUMPERS_ON); delay(3000);
  
  AnimLightFor(BLINK_BUMPER_1, 30);delay(2000);
  AnimLightFor(BLINK_BUMPER_2, 30);delay(2000);
  AnimLightFor(BLINK_BUMPER_3, 30);delay(2000);
  
  AnimLight(BUMPER_1_OFF);delay(500);
  AnimLight(BUMPER_2_OFF);delay(500);
  AnimLight(BUMPER_3_OFF);delay(500);
  AnimLight(ALL_BUMPERS_ON); delay(3000);
 */
 /*
 AnimLight(LAUNCHER_OFF);delay(2000);
 AnimLightFor(SNAKE_LAUNCHER, 50);delay(2000);
 
 AnimLight(LOOSE_OFF);delay(2000);
 AnimLightFor(BLINK_LOOSE, 30);delay(2000);
*/

AnimLight(KO1_OFF);delay(2000);
 AnimLightFor(BLINK_KO1, 30);delay(2000);
 AnimLightFor(SNAKE_KO1, 30);delay(2000);
 AnimLight(SNAKE_KO1);delay(2000);
 
 AnimLight(KO2_OFF);delay(2000);
 AnimLightFor(BLINK_KO2, 30);delay(2000);
 AnimLightFor(SNAKE_KO2, 30);delay(2000);
 AnimLight(SNAKE_KO2);delay(2000);


  delay(600000);
  
  /*
  AnimLight(FLASH_TOP_LIGHTS); delay(2000); AnimLight(LIGHT_TOP_LIGHTS); delay(2000); AnimLight(ALTERN_TOP_LIGHTS); delay(2000); AnimLight(OFF_TOP_LIGHTS); delay(2000);
  AnimLight(SNAKE_GREEN_TARGET); delay(2000); AnimLight(BLINK_GREEN_TARGET); delay(2000); AnimLight(OFF_GREEN_TARGET); delay(2000);
  AnimLight(SNAKE_RED_TARGET); delay(2000); AnimLight(BLINK_RED_TARGET); delay(2000); AnimLight(OFF_RED_TARGET); delay(2000);
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
