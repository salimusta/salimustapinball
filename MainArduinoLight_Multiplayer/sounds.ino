

void TestSounds(){
  printLine("Sound test", "On Going...");
  delay(1000);
  wTrig.masterGain(0);

  PlaySound(32);
  delay(1500);
  wTrig.trackPlayPoly(2);
  delay(1500);
  wTrig.trackPlayPoly(3);
  delay(1500);
  wTrig.trackPlayPoly(4);
  delay(3000);
  wTrig.trackPlayPoly(5);
  delay(3000);
  wTrig.stopAllTracks();
}

void PlaySound(byte sound){
  wTrig.trackPlayPoly(sound);
  delay(50);
}

void StopMusic(){
 byte i;
  for(i = 100; i< 117; i++) {wTrig.trackStop(i);delay(20);}
  delay(100);
}

void PlayRandomLoose(){
  //randomSeed(analogRead(0));
  byte rand = random(12);
  if(rand == 0){
    PlaySound(LOOSE_SINGE);
  }else  if(rand == 1){
     PlaySound(LAUGH_1);
  }else  if(rand == 2){
     PlaySound(LOOSE_POINT_POINT);
  }else  if(rand == 3){
     PlaySound(ANADINMI);
  }else  if(rand == 4){
     PlaySound(JAVOO_SALIM);
  }else  if(rand == 5){
     PlaySound(CANDOBETTER);
  }else  if(rand == 6){
     PlaySound(GRANDMOTHER);
  }else  if(rand == 7){
     PlaySound(MERRYCHRISTMASLOOSER);
  }else  if(rand == 8){
     PlaySound(RIREBOTH);
  }else  if(rand == 9){
     PlaySound(RIRESALIM);
  }else  if(rand == 10){
     PlaySound(RIREDESIREE);
  }else  if(rand == 11){
     PlaySound(WHYDIDUDOTHAT);
  }
  
}
int PlayRandomMusic(){
  StopMusic();
  
  long hasardSound;
  randomSeed(analogRead(0));
  hasardSound = random(17);
  
  wTrig.masterGain(0);
  byte i;
  int timeRelease = 0;
  for(i = 100; i< 117; i++){
    wTrig.trackLoop(i, true);
    wTrig.trackGain(i, -20);
  }
  
  if(hasardSound == 0){
    PlaySound(JIVE_BUNNY);
    timeRelease = 3000;
  }else  if(hasardSound == 1){
     PlaySound(FALLIN_RAIN);
     timeRelease = 4700;
  }else  if(hasardSound == 2){
     PlaySound(SURFIN_USA);
     timeRelease = 3500;
  }else  if(hasardSound == 3){
     PlaySound(MISIRLOU);
     timeRelease = 6000;
  }else  if(hasardSound == 4){
     PlaySound(ELVIS);
     timeRelease = 8000;
  }else  if(hasardSound == 5){
     PlaySound(FINDERSKEEPERS);
     timeRelease = 2500;
  }else  if(hasardSound == 6){
     PlaySound(ROCKNROLLPARTY);
     timeRelease = 1000;
  }else  if(hasardSound == 7){
     PlaySound(CANCANYOU);
     timeRelease = 3000;
  }else  if(hasardSound == 8){
     PlaySound(NOBLESURFER);
     timeRelease = 7000;
  }else  if(hasardSound == 9){
     PlaySound(TWISTPARTY);
     timeRelease = 4500;
  }else  if(hasardSound == 10){
     PlaySound(SHUTDOWN);
     timeRelease = 6500;
  }else  if(hasardSound == 11){
     PlaySound(BUSINESS);
     timeRelease = 4000;
  }else  if(hasardSound == 12){
     PlaySound(FISHBONE);
     timeRelease = 10500;
  }else  if(hasardSound == 13){
     PlaySound(CUBA);
     timeRelease = 2500;
  }else  if(hasardSound == 14){
     PlaySound(HIDEHO);
     timeRelease = 6800;
  }else  if(hasardSound == 15){
     PlaySound(HEY);
     timeRelease = 5500;
  }else  if(hasardSound == 16){
     PlaySound(RELAX);
     timeRelease = 2000;
  }
  
  return timeRelease;

}
