short int timeoff=0;
short int timetrig=0;
short int timedown=0;
short int statetime=0;

void TIMER(){
statustimer();
  
if ((Bt != Lt) && Bt == 0  && (currenttime-timer0 > buttondelay) && (timercount ==0)){
        stateT=!stateT;
        selectime++;
        Lt=Bt;
        timer0 = currenttime;
        timercount =1;
        beepvar=1;
        timeoff=0;
        if(selectime>4){selectime=0;}
        timercount = 1;
        contdown();
    } else if ((Bt != Lt) && (Bt == 1)&& (currenttime-timer0 > buttondelay)){
      Lt=Bt;
      timercount = 0;
      Serial.print("Timer is set to: ");
      Serial.println(selectime);
    }

    if(selectime>0){  
      if(currenttime - timetrig > 1000){
                 timetrig = currenttime;
                 timeoff++;
                 timedown = timedown-+1;   
                 Serial.print("Timer\t");
                 if(stateP==0){Serial.print("off :"); }
                 if(stateP==1){Serial.print("on :"); }
                 Serial.println(timedown);     
         }
    }
    if(selectime==1) {
        if(timeoff==10){Bp=0;timeoff=0;selectime=0;}else{Bp=1;}
    }
    if(selectime==2) {   
        if(timeoff==20){Bp=0;timeoff=0;selectime=0;}else{Bp=1;}
    }
    if(selectime==3) {   
        if(timeoff==30){Bp=0;timeoff=0;selectime=0;}else{Bp=1;}
    }
    if(selectime==4) {   
        if(timeoff==40){Bp=0;timeoff=0;selectime=0;}else{Bp=1;}
    }
}
void contdown(){
    switch(selectime){
      case 0:
      timedown=0;
      break;
      case 1:
      timedown=10;
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
void statustimer(){
  if(timedown==9){clearstatetime();digitalWrite(T1,1);}
  if(timedown==20){clearstatetime();digitalWrite(T2,1);}
  if(timedown==30){clearstatetime();digitalWrite(T3,1);}
  if(timedown==40){clearstatetime();digitalWrite(T4,1);}
  if(timedown==0){clearstatetime();}
  if(selectime==0){timedown=0;clearstatetime();}
}

void clearstatetime(){
  digitalWrite(T1,0);
  digitalWrite(T2,0);
  digitalWrite(T3,0);
  digitalWrite(T4,0);
}
