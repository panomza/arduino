
unsigned int tc=0;

void checkbuttons(){
  Bp      =  digitalRead(Bpow);
  Bs      =  digitalRead(Bspeed);
  Bt      =  digitalRead(Btimer); 
  Bf      =  digitalRead(Bfilter); 
 
}

void statebutton(){

  if (Bp==0 || Bs==0 || Bt==0 ) {

      timedim=brightdim;  
  }
  
//if(NodeSerial.available()>0){}else

  if(currenttime-tc>80){
      checkbuttons();
      tc=currenttime;
  }

}
