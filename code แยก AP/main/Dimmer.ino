
short int dim1=0;
short int delaydim=1;
short int brightdim=0;
unsigned int rundim=0;
int trigdim=0;
int countdim=0;
int timedim=10;


void Dimmer(){
  rundim++;
  
  if (timedim==0){PWM();}
  if (timedim>0){digitalWrite(dim,1);}
  if (digitalRead(Bpow)==0 || digitalRead(Bspeed)==0 || digitalRead(Bplasma)==0 || digitalRead(Bauto)==0 || digitalRead(Btimer)==0)
  {
   timedim=10;
  }
  if(rundim-trigdim>10125&&timedim>0){
    trigdim=rundim;
    timedim=timedim-+1;
  }
}

void PWM(){
  if (rundim-delaydim>1 && dim1==0){
    digitalWrite(dim,0);
    delaydim=rundim;
    dim1=1;
  } else 
  if (rundim-delaydim>5 && dim1==1){
    digitalWrite(dim,1);
    delaydim=rundim;
    dim1=0;
  }
}


  


void fucntiondim(){
  
}
