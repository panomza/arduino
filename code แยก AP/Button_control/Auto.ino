void Auto(){
    Ba      =  digitalRead(Bauto);
  // set speed according to dust
    if(currenttime-autotime>autotimer && stateA==0){
        Serial.print("average dust is :");
        Serial.println(averagedust);
        if(averagedust>=40){index=4;Serial.println("speed is set to 4");}
        else if(averagedust>=30){index=3;Serial.println("speed is set to 3");}
        else if(averagedust>=20){index=2;Serial.println("speed is set to 2");}
        else{index=1;Serial.println("speed is set to 1");}
        autotime=currenttime;
        Serial.println("speed is set by the auto function");
    }
    // activate or deactivate auto function
    if ((Ba != La) && (stateP == 0) && (currenttime-auto0 > buttondelay) && (autocount ==0)){
        stateA=!stateA;
        digitalWrite(AUTO,stateA);
        Serial.print("Auto is set to: ");
        Serial.println(stateA); 
        La=Ba;
        auto0 = currenttime;
        autocount =1;
    } else if ((Ba != La) && (Ba == 1)&& (currenttime-auto0 > buttondelay)){
      La=Ba;
      autocount = 0;
    }
}
