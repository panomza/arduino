void Auto(){
    if(stateA==1&&Bs==0){Ba=0;}

    if(currenttime-autotime>10000 && stateA==1){
      Serial.println("Auto");
        if(averagedust>=40){index=4;}
        else if(averagedust>=30){index=3;}
        else if(averagedust>=20){index=2;}
        else{index=1;}
        autotime=currenttime;
        applythespeedswitch();
    }
    
  // activate or deactivate auto function
    if ((Ba != La) && Ba == 0 && (stateP == 0) && (currenttime-auto0 > buttondelay) && (autocount ==0)){
        stateA=!stateA;
        digitalWrite(AUTO,stateA);
        Serial.print("Auto to : ");
        Serial.println(stateA); 
        La=Ba;
        auto0 = currenttime;
        autocount =1;
        beepvarB=1;
    } else if ((Ba != La) && (Ba == 1)&& (currenttime-auto0 > buttondelay)){
      La=Ba;
      autocount = 0;
    }
}
