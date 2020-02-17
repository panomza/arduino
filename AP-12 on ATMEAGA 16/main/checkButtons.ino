
unsigned int tc=0;

void checkbuttons(){
  Bp      =  digitalRead(Bpow);
  Bs      =  digitalRead(Bspeed);
  Bt      =  digitalRead(Btimer); 
 
}

void statebutton(){
 
  if (Bp==0 || Bs==0 || Bt==0) {
      checkbuttons(); 
      timedim=brightdim;
       
  }
//if(NodeSerial.available()>0){}else{
  if(currenttime-tc>100){
      checkbuttons();
      tc=currenttime;
  }
//}
}
