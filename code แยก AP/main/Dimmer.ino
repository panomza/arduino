unsigned int rundim=0;
unsigned int trigdim=0;
unsigned int timedim=10;

unsigned int dim1=0;
unsigned int delaydim=0;
unsigned int countdim=0;



void Dimmer(){
  rundim=millis();
  TCCR0A = _BV(COM0A1) | _BV(WGM01)| _BV(WGM00);
  OCR0A = countdim;
  
  if (timedim==0){PWM();}
  
  if (timedim>0){delaydim=0;countdim=255;}
  if (digitalRead(Bpow)==0 || digitalRead(Bspeed)==0  || digitalRead(Bauto)==0 || digitalRead(Btimer)==0)
  {
   timedim=5;
  }
  if(rundim-trigdim>1000&&timedim>0){
    trigdim=rundim;
    timedim=timedim-1;   
    
  }

}

void PWM(){
  if(rundim-dim1>2&&delaydim==0){
    dim1=rundim;
    countdim=countdim-1;
    if(countdim==50){delaydim=1;}
  } 
}
