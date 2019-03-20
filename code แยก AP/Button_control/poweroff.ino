void poweroff(){

     if(stateP==1){statePM=1;}
      digitalWrite(PLASMA,1);
     if(stateP==1){stateA=1;}
      digitalWrite(AUTO,1);
}
