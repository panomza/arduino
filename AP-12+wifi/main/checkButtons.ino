
unsigned int tc=0;

void checkbuttons(){
  Bp      =  digitalRead(Bpow);
  Bs      =  digitalRead(Bspeed);
  Bt      =  digitalRead(Btimer); 
}

void statebutton(){

  if (digitalRead(Bpow)==0 || digitalRead(Bspeed)==0 || digitalRead(Btimer)==0) {
      checkbuttons();
  }
if(NodeSerial.available()>0){}else{
  if(currenttime-tc>100){
      checkbuttons();
      tc=currenttime;
  }
}
}
