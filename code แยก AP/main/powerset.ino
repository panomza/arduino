
void powerset(){
  // check if previous state is different from current state, current state is 0 and powercount=0

  if ((Bp != Lp) && (Bp == 0) && (currenttime-powert0 > buttondelay) && (powercount==0)){
    clearspeed();
    stateP=!stateP;
    digitalWrite(POW,stateP);
    Serial.print("Power to : ");
    Serial.println(stateP);   
    Lp=Bp;
    powert0 = currenttime;   
    poweroff();
    powercount = 1;
    datasent = (1);
    Settime=0;
    if(stateP==0){
      beeppowervar=1;
      songindex=1;
      index=1;
      NodeSerial.print("O");
    }else 
    if(stateP==1){
      beeppowervar=1;
      songindex=2;
      index=0;
      NodeSerial.print("F");
    }
    applythespeedswitch(); // apply the switch for speed when turning on
} // else if Bp is back to 1, reset the powercount
  else if ((Bp != Lp) && (Bp == 1)&& (currenttime-powert0 > buttondelay)){
    Lp=Bp;
    powercount = 0;
  }
}
