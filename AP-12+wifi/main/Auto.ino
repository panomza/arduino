

void Auto(){
   
    if(currenttime-autotime>3000 && stateA==1 && stateP==0){
//        Serial.println("Auto");
      
        if(averagedust>=120){clearspeed();digitalWrite(M4,1);}
        if(averagedust>=100 && averagedust<120){clearspeed();digitalWrite(M3,1);}
        if(averagedust>=50 && averagedust<100){clearspeed();digitalWrite(M2,1);}
        if(averagedust<50){clearspeed();digitalWrite(M1,1);}
        
        autotime=currenttime;

    }
    
if ((Ba != La) && (Ba == 0)&& (currenttime-auto0 > buttondelay)&&autocount==0 && stateP==0){  
     La=Ba;
     stateA=!stateA;
     autocount=1;
     
     clearspeed();
     if(stateA==0){index=1;}
     if(stateA==1){index=5;}
     auto0=currenttime;      // get the current time
     beepvarB=1;
//     Serial.print("Auto is :");
//     Serial.print(stateA);
 }
   else if ((Ba != La) && (Ba == 1)&& (currenttime-auto0 > buttondelay)&&autocount==1 && stateP==0){
      La=Ba;
      autocount=0;
  }
    
}
