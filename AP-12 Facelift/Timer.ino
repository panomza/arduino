bool out = 0;

void TIMER(){
    if ( Bp == 0 ) {Settime=0;}

    if ((Bt != Lt) && Bt == 0  && (currenttime-timer0 > buttondelay)){
        Lt=Bt;
        Settime++;
        out = 0;
        timer0 = currenttime;
        beepvarB=1;
        if(Settime==5){Settime=0;}
        selecttime();
        Serial.print("Timer to : ");
        Serial.println(Settime);
    } else 
    if ((Bt != Lt) && (Bt == 1)&& (currenttime-timer0 > buttondelay)){
        Lt=Bt;  
    }
  
    

///////////////////////////////////////////////////////////////////////////////.

      runtime=millis();
      
            if(runtime - timetrig >1000 && selecttime>0){
                     timetrig = runtime;
                     timedown=timedown-1;   
                     out = 0; 
             }
 
      if (Settime==0){timedown=0;}

      if (timedown == 40 && out == 0 ){Settime=4;out =1;}
      if (timedown == 30 && out == 0 ){Settime=3;out =1;}
      if (timedown == 20 && out == 0 ){Settime=2;out =1;}
      if (timedown == 10 && out == 0 ){Settime=1;out =1;}
      if (timedown == 0 && out == 0 && Settime >0){Settime=0;Bp = 0;out =1;}
//      Serial.println(Bp); 
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
    timedown=30;
    break;
    case 4:
    timedown=40;
    break;
  }
}
