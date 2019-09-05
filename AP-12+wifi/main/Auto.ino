unsigned int B_wifi = 0;
unsigned int wifi_state = 0;
bool state_led = 0;
byte count_wifi = 0;
bool set_wifi = 0;
bool set = 0;

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
        La=Ba;
        auto0 = currenttime;
        autocount =1;
        beepvarB=1;
        Wi=0;
    } else if ((Ba != La) && (Ba == 1)&& (currenttime-auto0 > buttondelay)&&autocount ==1&&set_wifi==0){
      La=Ba;
        if (Wi==0){stateA=!stateA;}
        digitalWrite(AUTO,stateA);
        Serial.print("Auto to : ");
        Serial.println(stateA); 
      autocount = 0;
    }

    if (Bp==0) {set_wifi=0;Wi=1;}

    if (currenttime-B_wifi>100&&Ba==0&&stateP == 0){
      B_wifi=currenttime;
      count_wifi++;
    }
    if (Ba==1){count_wifi=0;set=0;}
    
    if (count_wifi==30&&set==0){ 
        set = 1;
        set_wifi=1;
        wifi=1;
        NodeSerial.print("W");
        NodeSerial.print("\n");
    }

    if (set_wifi==1){
      if (currenttime-wifi_state>500&&state_led==0){
          wifi_state=currenttime;
          digitalWrite(AUTO,1);
          state_led=1;
      }else
      if (currenttime-wifi_state>500&&state_led==1){
          wifi_state=currenttime;
          digitalWrite(AUTO,0);
          state_led=0;
      }
    }




    
}
