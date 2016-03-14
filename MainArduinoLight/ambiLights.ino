
void AmbiLight(byte light){
  Wire.beginTransmission(6);
  Wire.write(light);
  Wire.endTransmission();
}
void TestAmbiLights(){
  AmbiLight(ALL_OFF);
  printLine("Ambi Lights Test", ".....");
  AmbiLight(RED_ON); delay(2000); AmbiLight(RED_OFF);

  AmbiLight(GREEN_ON); delay(2000); AmbiLight(GREEN_OFF); 

  AmbiLight(YELLOW_ON); delay(2000); AmbiLight(YELLOW_OFF); 

  AmbiLight(BLUE_ON); delay(2000); AmbiLight(BLUE_OFF);

  AmbiLight(ALL_ON); delay(2000); AmbiLight(ALL_OFF);
}
