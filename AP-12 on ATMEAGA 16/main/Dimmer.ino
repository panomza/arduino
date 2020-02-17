
unsigned int trigdim=0;
unsigned int timedim=10;

void Dimmer(){
  
  if (timedim>0){digitalWrite(dim,1);bright7=7;}
  if (timedim==0){digitalWrite(dim,0);bright7=1;}

  if(currenttime-trigdim>1000&&timedim>0){
    trigdim=currenttime;
    timedim=timedim-1;       
  }

  if ((Rd != Ld) && (Rd == 0)&& (currenttime-Rdim0 > buttondelay)&&dimcount==0){  
     Ld=Rd;
     
     ck=!ck;
     dimcount=1;
     Rdim0=currenttime;      // get the current time
     beepvarB=1;
     if(ck==1){timedim=0;}else{timedim=brightdim;}
//     Serial.print("Remote Dim");
 }
   else if ((Rd != Ld) && (Rd == 1)&& (currenttime-Rdim0 > buttondelay)&&dimcount==1){
      Ld=Rd;
      dimcount=0;
  }

}
