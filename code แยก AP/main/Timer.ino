bool shift = 0;

void TIMER(){

  digitalWrite(timerled,statetime);
 
  if (stateP==1 && timedim==0){statetime=0; shift=0; }
  
  if (shift==0){
     if (digitalRead(Bpow)==0 || digitalRead(Bspeed)==0 || digitalRead(Bauto)==0 || digitalRead(Btimer)==0 ) {
      statetime=1;
      shift=1;
    }
  }



  if (currenttime-buttontime0>1000&&Bt==0){
      buttontime0=currenttime;
        if(buttoncount0<3){
          buttoncount0++; 
          }
      }
      else if(Bt==1){buttoncount0=0;}
 
  if (buttoncount0==3){buttoncount1=5;}
  
  if (currenttime-buttontime1>1000&&buttoncount1>0){
      buttontime1=currenttime; 
       if(buttoncount1<=5){
        buttoncount1=buttoncount1-1;
        }
      }
  if (buttoncount1>0&&Bt==0){buttoncount1=5;}
  
  if (buttoncount1==0 && beepout == 1 ){beepvarS=1;beepout = 0;} 
  if (buttoncount1==5 && beepout == 0 ){beepvarS=1;beepout = 1;}
    
  if (buttoncount0<=2&&buttoncount1>0 || checkstate_in==1){
      
    if ((Bt != Lt) && Bt == 0  && (currenttime-timer0 > buttondelay)){
        Lt=Bt;
        Settime++;
        timer0 = currenttime;
        beepvarB=1;
        if(Settime==5){Settime=0;}
        selecttime();
        Serial.print("Timer to : ");
        Serial.println(Settime);
    } else 
    if ((Bt != Lt) && (Bt == 1)&& (currenttime-timer0 > buttondelay)){
        Lt=Bt;  
        BTcount=1;    
    }
  }
    

///////////////////////////////////////////////////////////////////////////////.
    if(Bp==0){Settime=0;timeshow2=0;}
    if(timedown==0&&Settime>0){Bp=0;Settime=0;}
    if(Settime==0){timeshow2=0;timedown=0;}
    Serial.println(timeshow2);
      runtime=millis();
            if(runtime - timetrig >1000){
                     timetrig = runtime;
                     timedown=timedown-1;  
                     timeshow0=timeshow0-1;  
             }
      timeshow0=(timedown/60)*100;  
      timeshow1=timedown%60;
      timeshow2=timeshow1+timeshow0;   
}

void selecttime(){
  switch(Settime){
    case 1:
    timedown=60;
    break;
    case 2:
    timedown=120;
    break;
    case 3:
    timedown=240;
    break;
    case 4:
    timedown=360;
    break;
  }
}
