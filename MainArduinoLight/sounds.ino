

void TestSounds(){
  /*printLine("Sound test", "On Going...");
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
  wTrig.stopAllTracks();*/
}

void PlaySound(byte sound, bool override){
  if(override || (time - timeOfLastSoundPlayed > 0 && time - timeOfLastSoundPlayed > 400)) {
    timeOfLastSoundPlayed = time;
    wTrig.trackPlayPoly(sound);
  }
  
  //delay(50);
}

void StopMusic(){
 byte i;
  for(i = 100; i< 121; i++) {wTrig.trackStop(i);}
  //delay(100);
}

void PlayRandomLoose(){
  //randomSeed(analogRead(0));
  byte rand = random(12);
  if(rand == 0){
    PlaySound(LOOSE_SINGE, false);
  }else  if(rand == 1){
     PlaySound(LAUGH_1, false);
  }else  if(rand == 2){
     PlaySound(LOOSE_POINT_POINT, false);
  }else  if(rand == 3){
     PlaySound(ANADINMI, false);
  }else  if(rand == 4){
     PlaySound(JAVOO_SALIM, false);
  }else  if(rand == 5){
     PlaySound(CANDOBETTER, false);
  }else  if(rand == 6){
     PlaySound(GRANDMOTHER, false);
  }else  if(rand == 7){
     PlaySound(MERRYCHRISTMASLOOSER, false);
  }else  if(rand == 8){
     PlaySound(RIREBOTH, false);
  }else  if(rand == 9){
     PlaySound(RIRESALIM, false);
  }else  if(rand == 10){
     PlaySound(RIREDESIREE, false);
  }else  if(rand == 11){
     PlaySound(WHYDIDUDOTHAT, false);
  }
  
}
int PlayRandomMusic(){
  StopMusic();
  
  long hasardSound;
  randomSeed(analogRead(0));
  hasardSound = random(15);
  
  wTrig.masterGain(0);
  byte i;
  int timeRelease = 0;
  for(i = 100; i< 121; i++){
    wTrig.trackLoop(i, true);
    wTrig.trackGain(i, -10);
  }
  
  if(hasardSound == 0){
    PlaySound(JIVE_BUNNY, true);
    timeRelease = 3000;
  }else  if(hasardSound == 1){
     PlaySound(FALLIN_RAIN, true);
     timeRelease = 4700;
  }else  if(hasardSound == 2){
     PlaySound(SURFIN_USA, true);
     timeRelease = 3500;
  }else  if(hasardSound == 3){
     PlaySound(RELAX, true);
     timeRelease = 2000;
  }else  if(hasardSound == 4){
     PlaySound(ELVIS, true);
     timeRelease = 8000;
  }else  if(hasardSound == 5){
     PlaySound(FINDERSKEEPERS, true);
     timeRelease = 2500;
  }else  if(hasardSound == 6){
     PlaySound(ROCKNROLLPARTY, true);
     timeRelease = 1000;
  }else  if(hasardSound == 7){
     PlaySound(HEY, true);
     timeRelease = 5500;
  }else  if(hasardSound == 8){
     PlaySound(NOBLESURFER, true);
     timeRelease = 7000;
  }else  if(hasardSound == 9){
     PlaySound(TWISTPARTY, true);
     timeRelease = 4500;
  }else  if(hasardSound == 10){
     PlaySound(SHUTDOWN, true);
     timeRelease = 6500;
  }else  if(hasardSound == 11){
     PlaySound(BUSINESS, true);
     timeRelease = 4000;
  }else  if(hasardSound == 12){
     PlaySound(FISHBONE, true);
     timeRelease = 10500;
  }else  if(hasardSound == 13){
     PlaySound(CUBA, true);
     timeRelease = 2500;
  }else  if(hasardSound == 14){
     PlaySound(HIDEHO, true);
     timeRelease = 6800;
  }
  
  return 2000;
  return timeRelease;

}

void PlayRandomMultiballMusic(){
  StopMusic();
  
  long hasardSound;
  randomSeed(analogRead(0));
  hasardSound = random(2);
  
  wTrig.masterGain(0);
  byte i;
  int timeRelease = 0;
  for(i = 100; i< 121; i++){
    wTrig.trackLoop(i, true);
    wTrig.trackGain(i, -10);
  }
  
  if(hasardSound == 0){
    PlaySound(MISIRLOU, true);
  }else{
    PlaySound(CANCANYOU, true);
  }
  

}

void PlayMusic(short musicId){
  StopMusic();
  
  wTrig.masterGain(0);
  byte i;
  int timeRelease = 0;
  for(i = 100; i< 121; i++){
    wTrig.trackLoop(i, true);
    wTrig.trackGain(i, -10);
  }
  
  PlaySound(musicId, true);

}
