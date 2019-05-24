
unsigned int timetrig=0;
unsigned int runtime =0;



void TIMER(){
 
    if ((Bt != Lt) && Bt == 0  && (currenttime-timer0 > buttondelay)){
        Lt=Bt;
        Settime++;
        timer0 = currenttime;
        beepvar=1;
        if(Settime==5){Settime=0;NodeSerial.print("z");}
        selecttime();
      Serial.print("Timer to : ");
      Serial.println(Settime);
    } else 
    if ((Bt != Lt) && (Bt == 1)&& (currenttime-timer0 > buttondelay)){
      Lt=Bt;      
    }
///////////////////////////////////////////////////////////////////////////////.
if(Bp==0){Settime=0;timeshow2=0;}
if(timedown==0&&Settime>0){Bp=0;Settime=0;}
if(Settime==0){timeshow2=0;}
if(Settime>0){ Serial.println(timedown); 
  runtime=millis();
        if(runtime - timetrig >1000){
                 timetrig = runtime;
                 timedown=timedown-1;  
                 timeshow0=timeshow0-1;  
 
      Serial.println(timeshow2);
         }
  timeshow0=timedown/60;  
  timeshow1=(((timedown/60)-timeshow0)*60)/100;
  timeshow2=timeshow1+timeshow0;   
  }

  
  
}

void selecttime(){
  switch(Settime){
    case 1:
    timedown=10;
    NodeSerial.print("x");
    break;
    case 2:
    timedown=20;
    NodeSerial.print("c");
    break;
    case 3:
    timedown=60;
    NodeSerial.print("v");
    break;
    case 4:
    timedown=150;
    NodeSerial.print("b");
    break;
  }
}
