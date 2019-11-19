

void Auto(){
   
    mcp.digitalWrite(AUTO,stateA);
    
    if(currenttime-autotime>10000 && stateA==1 && stateP==0){
        Serial.println("Auto");
      
        if(averagedust>=40){clearspeed();digitalWrite(M4,1);}
        if(averagedust>=30&&averagedust<40){clearspeed();digitalWrite(M3,1);}
        if(averagedust>=20&&averagedust<30){clearspeed();digitalWrite(M2,1);}
        if(averagedust<20){clearspeed();digitalWrite(M1,1);}
        
        autotime=currenttime;

    }
    
if ((Ba != La) && (Ba == 0)&& (currenttime-auto0 > buttondelay)&&autocount==0 && stateP==0){  
     La=Ba;
     stateA=!stateA;
     autocount=1;
     clearspeed();
     if(stateA==0){applythespeedswitch();}
     auto0=currenttime;      // get the current time
     beepvarB=1;
     Serial.print("Auto is :");
     Serial.print(stateA);
 }
   else if ((Ba != La) && (Ba == 1)&& (currenttime-auto0 > buttondelay)&&autocount==1 && stateP==0){
      La=Ba;
      autocount=0;
  }
    
}
