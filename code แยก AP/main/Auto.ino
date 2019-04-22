//void Auto(){
//    if(stateA==1&&Bs==0){Ba=0;}
//  // set speed according to dust
//    if(currenttime-autotime>autotimer && stateA==1){
//        digitalWrite(AUTO,stateA);
//        
//        if(averagedust>=40){index=4;Serial.println("speed is set by the auto function to 4");}
//        else if(averagedust>=30){index=3;Serial.println("speed is set by the auto function to 3");}
//        else if(averagedust>=20){index=2;Serial.println("speed is set by the auto functionto 2");}
//        else{index=1;Serial.println("speed is set by the auto function to 1");}
//        autotime=currenttime;
//        applythespeedswitch();
//    }
//    
//  // activate or deactivate auto function
//    if ((Ba != La) && Ba == 0 && (stateP == 0) && (currenttime-auto0 > buttondelay) && (autocount ==0)){
//        stateA=!stateA;
//        digitalWrite(AUTO,stateA);
//        Serial.print("Auto is set to: ");
//        Serial.println(stateA); 
//        if(stateA==0){NodeSerial.print("A");}
//        else if (stateA==1){NodeSerial.print("a");}
//        La=Ba;
//        auto0 = currenttime;
//        autocount =1;
//        beepvar=1;
//    } else if ((Ba != La) && (Ba == 1)&& (currenttime-auto0 > buttondelay)){
//      La=Ba;
//      autocount = 0;
//    }
//}
