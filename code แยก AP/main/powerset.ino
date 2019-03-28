
void powerset(){
  // check if previous state is different from current state, current state is 0 and powercount=0

  if ((Bp != Lp) && (Bp == 0) && (millis()-powert0 > buttondelay) && (powercount==0)){
    stateP=!stateP;
    digitalWrite(POW,stateP);
    Serial.print("Power is set to: ");
    Serial.println(stateP); 
    applythespeedswitch(); // apply the switch for speed when turning on
    Lp=Bp;
    index=1;
    powert0 = millis();
    clearspeed();
    poweroff();
    powercount = 1;
    datasent = (1);
     
    if(stateP==0){
      beeppowervar=1;
      songindex=1;
      NodeSerial.print("O");
    }else 
    if(stateP==1){
      beeppowervar=1;
      songindex=2;
      NodeSerial.print("F");
    }
} // else if Bp is back to 1, reset the powercount
  else if ((Bp != Lp) && (Bp == 1)&& (millis()-powert0 > buttondelay)){
    Lp=Bp;
    powercount = 0;
  }
}
