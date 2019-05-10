
unsigned int dim1=0;
unsigned long int delaydim=1;
unsigned long int rundim=0;
unsigned long int trigdim=0;
unsigned int countdim=0;
unsigned int timedim=10;


void Dimmer(){
  
  rundim=micros();
  
//  if (timedim==0){PWM();}
  if (timedim>0){digitalWrite(dim,1);}else{digitalWrite(dim,0);}
  if (digitalRead(Bpow)==0 || digitalRead(Bspeed)==0  || digitalRead(Bauto)==0 || digitalRead(Btimer)==0)
  {
   timedim=5;
  }
  if(rundim-trigdim>1000000&&timedim>0){
    trigdim=rundim;
    timedim=timedim-1;   
  }
}

void PWM(){
  
  if (rundim-delaydim>1 && dim1==0){
    digitalWrite(dim,0);
    delaydim=rundim;
    dim1=1;
  } else 
  if (rundim-delaydim>1000 && dim1==1){
    digitalWrite(dim,1);
    delaydim=rundim;
    dim1=0;
  }
}
