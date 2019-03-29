void checkbuttons(){
  Bp      =  digitalRead(Bpow);
  Bs      =  digitalRead(Bspeed);
  Bpm     =  digitalRead(Bplasma);
  Ba      =  digitalRead(Bauto);
}

void statebutton(){

  if (digitalRead(Bpow)==0 || digitalRead(Bspeed)==0 || digitalRead(Bplasma)==0 || digitalRead(Bauto)==0 )
  {
    checkbuttons();
  }
  
}
