void poweroff(){

     if(stateP==1){statePM=0;}
      digitalWrite(PLASMA,0);
     if(stateP==1){stateA=0;}
      digitalWrite(AUTO,0);
}
void powoff(){
  digitalWrite(PLASMA,0);
  digitalWrite(AUTO,0);
}
