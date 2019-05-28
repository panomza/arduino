
void TIMER(){

  if (currenttime-buttontime0>1000&&Bt==0){
      buttontime0=currenttime;
        if(buttoncount0<3){
          buttoncount0++; 
          }
      }
      else if(Bt==1){buttoncount0=0;}
 
  if (buttoncount0==3){buttoncount1=10;}
  
  if (currenttime-buttontime1>1000&&buttoncount1>0){
      buttontime1=currenttime; 
       if(buttoncount1<=10){
        buttoncount1=buttoncount1-1;
        }
      }
  
  if (buttoncount1==0){beepout = 0; } 
  if (buttoncount1==10&&beepout == 0){beepvar=1;beepout = 1;}
    
  if (buttoncount0<=2&&buttoncount1>0 || checkstate_in==1){
      
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
      BTcount=1;    
    }
  }
    

///////////////////////////////////////////////////////////////////////////////.
    if(Bp==0){Settime=0;timeshow2=0;}
    if(timedown==0&&Settime>0){Bp=0;Settime=0;}
    if(Settime==0){timeshow2=0;timedown=0;}
    
      runtime=millis();
            if(runtime - timetrig >1000){
                     timetrig = runtime;
                     timedown=timedown-1;  
                     timeshow0=timeshow0-1;  
             }
      timeshow0=timedown/60;  
      timeshow1=(((timedown/60)-timeshow0)*60)/100;
      timeshow2=timeshow1+timeshow0;   
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
    timedown=60;
    break;
    case 4:
    timedown=150;
    break;
  }
}
