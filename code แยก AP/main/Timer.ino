unsigned int timedown=0;
unsigned int timetrig=0;
unsigned int runtime =0;

void TIMER(){
 runtime=millis();
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
  
if(Settime==0) {timedown=0;clearstatetime();} 
if(Settime>0){  
        if(runtime - timetrig >1000){
                 timetrig = runtime;
                 timedown=timedown-+1;  
                 Serial.println(timedown);     
         }    
         
 
  if(timedown==0){Settime=0;}  
  if(timedown==1){Bp=0;}else{Bp=1;}
  if(timedown==10){clearstatetime();digitalWrite(T1,1);}
  if(timedown==20){clearstatetime();digitalWrite(T2,1);}
  if(timedown==30){clearstatetime();digitalWrite(T3,1);}
  if(timedown==40){clearstatetime();digitalWrite(T4,1);}
  }
}

void selecttime(){
  switch(Settime){
    case 1:
    timedown=11;
    break;
    case 2:
    timedown=20;
    break;
    case 3:
    timedown=30;
    break;
    case 4:
    timedown=40;
    break;
  }
}

void clearstatetime(){
  digitalWrite(T1,0);
  digitalWrite(T2,0);
  digitalWrite(T3,0);
  digitalWrite(T4,0);
}
