

void Auto(){
   

    if(currenttime-autotime>10000 && stateA==1){
      Serial.println("Auto");
        if(averagedust>=40){digitalWrite(M4,1);}else{digitalWrite(M4,0);}
        if(averagedust>=30){digitalWrite(M4,1);}else{digitalWrite(M3,0);}
        if(averagedust>=20){digitalWrite(M4,1);}else{digitalWrite(M2,0);}
        if(averagedust<20{digitalWrite(M4,1);}else{digitalWrite(M1,0);}
        
        autotime=currenttime;

    }
    

    
}
