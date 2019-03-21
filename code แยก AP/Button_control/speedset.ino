void speedset(){
  Bs      =  digitalRead(Bspeed);
 if ((Bs != Ls) && (stateP==0) && (Bs == 0)&& (millis()-speedt0 > buttondelay)&&(stateA==1)){  
     stateS=!stateS;
     index++;
     if(index>4){index=1;}
     Serial.print("Speed is set to: ");
     Serial.println(index);
     speedt0=millis(); // get the current time
     Ls=Bs;

 }
 else if ((Bs != Ls) && (Bs == 1)&& (millis()-speedt0 > buttondelay)){
    Ls=Bs;
  }
  
}

void applythespeedswitch(){
  if(stateP==0){
    switch (index) {
    case 0:
      clearspeed();
      digitalWrite(PLASMA,1);
      break;
    case 1:
      clearspeed();
      digitalWrite(M1,0);   
     // Serial.println("M1");
      break;
    case 2:
      clearspeed();
      digitalWrite(M2,0);
     // Serial.println("M2");
      break;
    case 3:
      clearspeed();
      digitalWrite(M3,0);
     // Serial.println("M3");
      break;
    case 4:
      clearspeed();
      digitalWrite(M4,0);
     // Serial.println("M4");
      break;
  }
  }
}
