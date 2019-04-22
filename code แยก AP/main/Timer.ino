short int timedown=0;
short int timetrig=0;


void TIMER(){
  
if ((Bt != Lt) && Bt == 0  && (currenttime-timer0 > buttondelay) && (timercount ==0)){
        stateT=!stateT;
        selectime++;
        Lt=Bt;
        timer0 = currenttime;
        timercount =1;
        beepvar=1;
        timedown=0;
        if(selectime>4){selectime=0;}
        timercount = 1;
        selecttime();
      Serial.print("Timer is set to: ");
      Serial.println(selectime);
    } else if ((Bt != Lt) && (Bt == 1)&& (currenttime-timer0 > buttondelay)){
      Lt=Bt;
      timercount = 0;      
    }
///////////////////////////////////////////////////////////////////////////////.

if(selectime>0){  
        if(currenttime - timetrig > 1000){
                 timetrig = currenttime;
                 timedown=timedown-+1;  
                 Serial.print("Timer\t");
                 if(stateP==0){Serial.print("off :"); }
                 if(stateP==1){Serial.print("on :"); }
                 Serial.println(timedown);     
         }
    }
    
if(timedown==1){Bp=0;timedown=0;selectime=0;}
if(timedown==10){digitalWrite(T1,1);}
if(timedown==20){clearstatetime();digitalWrite(T2,1);}
if(timedown==30){clearstatetime();digitalWrite(T3,1);}
if(timedown==40){clearstatetime();digitalWrite(T4,1);}

}

void selecttime(){
    if(selectime==1) {timedown=11;}
    if(selectime==2) {timedown=20;}
    if(selectime==3) {timedown=30;}
    if(selectime==4) {timedown=40;}
    if(selectime==0) {timedown=0;clearstatetime();}
  }

void clearstatetime(){
  digitalWrite(T1,0);
  digitalWrite(T2,0);
  digitalWrite(T3,0);
  digitalWrite(T4,0);
}
