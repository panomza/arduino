void checkbuttons(){
  Bp      =  digitalRead(Bpow);
  Bs      =  digitalRead(Bspeed);
  Bpm     =  digitalRead(Bplasma);
  Ba      =  digitalRead(Bauto);
}
short int bstate=0;
short int b_count=0;

void statebutton(){

      bstate=currenttime;
  if (digitalRead(Bpow)==0 || digitalRead(Bspeed)==0 ||  digitalRead(Bplasma)==0 )
  {
    checkbuttons();
  }
  
}
