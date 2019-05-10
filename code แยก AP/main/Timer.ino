
unsigned int timetrig=0;
unsigned int runtime =0;

void TIMER(){
 
    if ((Bt != Lt) && Bt == 0  && (currenttime-timer0 > buttondelay)){
        Lt=Bt;
        Settime++;
        timer0 = currenttime;
        beepvar=1;
        if(Settime==5){Settime=0;}
        selecttime();
      Serial.print("Timer to : ");
      Serial.println(Settime);
    } else 
    if ((Bt != Lt) && (Bt == 1)&& (currenttime-timer0 > buttondelay)){
      Lt=Bt;      
    }
///////////////////////////////////////////////////////////////////////////////.
  if(timedown==0){Settime=0;}  
  if(timedown==1){Bp=0;}
  
if(Settime==0) {timedown=0;} 
if(Settime>0){  
  runtime=millis();
        if(runtime - timetrig >1000){
                 timetrig = runtime;
                 timedown=timedown-+1;  
                 Serial.println(timedown);     
         }    
  }
}

void selecttime(){
  switch(Settime){
    case 1:
    timedown=10;
    break;
    case 2:
    timedown=20;
    break;
    case 3:
    timedown=40;
    break;
    case 4:
    timedown=80;
    break;
  }
}
