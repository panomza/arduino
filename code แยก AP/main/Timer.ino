int timeoff=0;
int timetrig=0;
int timedown=0;

void TIMER(){
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
