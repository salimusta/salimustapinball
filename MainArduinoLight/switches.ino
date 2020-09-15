

void TestSwitches() {
 while (1) {
    ReadSwitches();
    ReadSolenoidSwitches();
    lcd.setCursor(0, 1);
    if (BSW1) lcd.print("BSW1"); if (BSW2) lcd.print("BSW2"); if (BSW3) lcd.print("BSW3");
    if (ROSW1) lcd.print("ROSW1"); if (ROSW2) lcd.print("ROSW2-"); if (ROSW3) lcd.print("ROSW3");
    if (COIN) lcd.print("COIN"); if (KO2) lcd.print("KO2"); if (RKSW) lcd.print("Right Kick"); if (LKSW) lcd.print("Left Kick");if (TKSW) lcd.print("Top Kick");
    if (LOSW) lcd.print("LOSW"); if (RLOSW) lcd.print("RLOSW"); if (LLOSW) lcd.print("LLOSW");
    if (CT) lcd.print("CT"); if (GATE) lcd.print("GATE"); if (RT1) lcd.print("RT1"); if (RT1P) lcd.print("RT1P"); if (RT2) lcd.print("RT2");
    if (LT1) lcd.print("LT1"); if (LT2) lcd.print("LT2"); if (LT2P) lcd.print("LT2P"); if (KO1) lcd.print("KO1");
    if (RAMP2) lcd.print("RAMP2");
    if (digitalRead(BackBoutonPin) == HIGH) break;
  }
}


void ReadSwitches() {
  //Request switch status from switch arduino
  //Just 1 Byte, containing the switch status 0010 0110
  //Serial.print("Requesting 1 byte...\n");
  bool newBSW1, newBSW2, newBSW3, newROSW1, newROSW2, newROSW3, newCOIN, newKO2;
  bool newLOSW, newRLOSW, newLLOSW, newCT, newGATE, newRT1, newRT1P, newRT2, newLT1, newLT2, newLT2P, newKO1, newRAMP1, newRAMP2, newSTART, newTILT;
  Wire.requestFrom(3, 3);
  while (Wire.available())   // slave may send less than requested
  {
    char c = Wire.read(); // receive a byte as character
    char c2 = Wire.read(); // receive a byte as character
    char c3 = Wire.read(); // receive a byte as character
    //order starting from bit 0: BSW1, BSW2, BSW3, LOSW1, LOSW2, LOSW3, TRIEUR, KO2
    newBSW1 = (c & 1); newBSW2 = (c & 2) >> 1; newBSW3 = (c & 4) >> 2; newROSW1 = (c & 8) >> 3;
    newROSW2 = (c & 16) >> 4; newROSW3 = (c & 32) >> 5; newCOIN = (c & 64) >> 6; newKO2 = (c & 128) >> 7;

    //order starting from bit 0: LOSW, RLOSW, LLOSW, CT, CTP, RT1, RT1P, RT2
    newLOSW = (c2 & 1); newRLOSW = (c2 & 2) >> 1; newLLOSW = (c2 & 4) >> 2; newCT = (c2 & 8) >> 3;
    newGATE = (c2 & 16) >> 4; newRT1 = (c2 & 32) >> 5; newRT1P = (c2 & 64) >> 6; newRT2 = (c2 & 128) >> 7;

    //order starting from bit 0: LT1, LT2, LT2P, KO1, RAMP1, RAMP2, START, TILT
    newLT1 = (c3 & 1); newLT2 = (c3 & 2) >> 1; newLT2P = (c3 & 4) >> 2; newKO1 = (c3 & 8) >> 3;
    newRAMP1 = (c3 & 16) >> 4; newRAMP2 = (c3 & 32) >> 5; newSTART = (c3 & 64) >> 6; newTILT = (c3 & 128) >> 7;

    BSW1 = (newBSW1 && BSW1_Old != newBSW1); BSW2 = (newBSW2 && BSW2_Old != newBSW2); BSW3 = (newBSW3 && BSW3_Old != newBSW3);
    ROSW1 = (newROSW1 && ROSW1_Old != newROSW1); ROSW2 = (newROSW2 && ROSW2_Old != newROSW2); ROSW3 = (newROSW3 && ROSW3_Old != newROSW3);
    COIN = (newCOIN && COIN_Old != newCOIN); KO2 = (newKO2 && KO2_Old != newKO2);
    LOSW = (newLOSW && LOSW_Old != newLOSW); RLOSW = (newRLOSW && RLOSW_Old != newRLOSW); LLOSW = (newLLOSW && LLOSW_Old != newLLOSW);
    CT = (newCT && CT_Old != newCT); GATE = (newGATE && GATE_Old != newGATE); RT1 = (newRT1 && RT1_Old != newRT1);
    RT1P = (newRT1P && RT1P_Old != newRT1P); RT2 = (newRT2 && RT2_Old != newRT2); LT1 = (newLT1 && LT1_Old != newLT1); LT2 = (newLT2 && LT2_Old != newLT2);
    LT2P = (newLT2P && LT2P_Old != newLT2P); KO1 = (newKO1 && KO1_Old != newKO1);
    RAMP2 = (newRAMP2 && RAMP2_Old != newRAMP2);
    START = (newSTART && START_Old != newSTART);
    TILT = (newTILT && TILT_Old != newTILT);
  }
  BSW1_Old = newBSW1; BSW2_Old = newBSW2; BSW3_Old = newBSW3; ROSW1_Old = newROSW1; ROSW2_Old = newROSW2; ROSW3_Old = newROSW3; COIN_Old = newCOIN;
  KO2_Old = newKO2; LOSW_Old = newLOSW; RLOSW_Old = newRLOSW; LLOSW_Old = newLLOSW; CT_Old = newCT; GATE_Old = newGATE; RT1_Old = newRT1; RT1P_Old = newRT1P;
  RT2_Old = newRT2; LT1_Old = newLT1; LT2_Old = newLT2; LT2P_Old = newLT2P; KO1_Old = newKO1; RAMP2_Old = newRAMP2; START_Old = newSTART;
  TILT_Old = newTILT;
}

void ReadSolenoidSwitches() {
  //Request switch status from switch arduino
  //order starting from bit 0: KickerLeft, KickerRight, LeftFLipper, RightFLipper
  bool newKickerLeft, newKickerRight;
  bool newLeftFlipper, newRightFlipper;
  bool newTopKicker;
  Wire.requestFrom(2, 1);
  while (Wire.available()) {
    char c = Wire.read(); // receive a byte as character
    newTopKicker = (c & 1);
    newKickerLeft = (c & 2) >> 1;
    newKickerRight = (c & 4) >> 1;
    newLeftFlipper = (c & 8) >> 1;
    newRightFlipper = (c & 16) >> 1;
    
    RKSW = (newKickerRight && RKSW_Old != newKickerRight);
    LKSW = (newKickerLeft && LKSW_Old != newKickerLeft);
    TKSW = (newTopKicker && TKSW_Old != newTopKicker);
    
    LEFT_FLIPPER = newLeftFlipper;
    RIGHT_FLIPPER = newRightFlipper;
    
  }
  RKSW_Old = newKickerRight;
  LKSW_Old = newKickerLeft;
  TKSW_Old = newTopKicker;
  LEFT_FLIPPER_Old = LEFT_FLIPPER;
  RIGHT_FLIPPER_Old = RIGHT_FLIPPER;
}
