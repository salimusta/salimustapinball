
byte oldData = 0;
void ReadBluetoothState() {

  byte flippersState = 0;
  Wire.requestFrom(8, 1);
  
  flippersState = Wire.read();
  
  //Serial.print("F="); Serial.print(flippersState); Serial.print("\n");
  
  //Send Back info to the solenoids
  if(flippersState != oldData) SendSolenoidData(flippersState);
  oldData = flippersState;

}
