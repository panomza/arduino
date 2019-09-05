
void powerset(){
  // check if previous state is different from current state, current state is 0 and powercount=0

  if ((Bp != Lp) && (Bp == 0) && (currenttime-powert0 > buttondelay) && (powercount==0)&&play==0){
    clearspeed();
    stateP=!stateP;
    digitalWrite(POW,!stateP);
    Serial.print("Power to : ");
    Serial.println(stateP);   
    Lp=Bp;
    powert0 = currenttime;   
    powercount = 1;
    
    if(stateP==0){
      beeppowervar=1;
      songindex=0;
      index=1;
      statetime=1;
    } 
    
    else if(stateP==1){
      beeppowervar=1;
      songindex=1;
      index=0;
      stateA=0;
      digitalWrite(AUTO,stateA); 
      statetime=0;
      
    }
    
    applythespeedswitch(); // apply the switch for speed when turning on
    
} // else if Bp is back to 1, reset the powercount

  else if ((Bp != Lp) && (Bp == 1)&& (currenttime-powert0 > buttondelay)&&play==0){
      Lp=Bp;
      powercount = 0;shift=0;
  }
  
}
