
short int tc=0;

void checkbuttons(){
  Bp      =  digitalRead(Bpow);
  Bs      =  digitalRead(Bspeed);
  Bpm     =  digitalRead(Bplasma);
  Ba      =  digitalRead(Bauto);
  Bt      =  digitalRead(Btimer);

  
}

void statebutton(){

  if(currenttime-tc>100){
    checkbuttons();
    tc=currenttime;
  }
}
