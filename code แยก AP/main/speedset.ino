void speedset(){

 if ((Bs != Ls) && (stateP==0) && (Bs == 0)&& (currenttime-speedt0 > buttondelay)){  
     stateS=!stateS;
     index++;
     if(index>4){index=1;}
     Serial.print("Speed is set to: ");
     Serial.println(index);
     speedt0=currenttime; // get the current time
     Ls=Bs;
     beepvar=1;
     applythespeedswitch();
 }
 else if ((Bs != Ls) && (Bs == 1)&& (currenttime-speedt0 > buttondelay)){
    Ls=Bs;
  }
}

void applythespeedswitch(){
  if(stateP==0){
    switch (index) {
    case 0:
      clearspeed();
      break;
    case 1:
      clearspeed();
      digitalWrite(M1,1);   
      NodeSerial.print("l");
      break;
    case 2:
      clearspeed();
      digitalWrite(M2,1);
      NodeSerial.print("m");
      break;
    case 3:
      clearspeed();
      digitalWrite(M3,1);
      NodeSerial.print("h");
      break;
    case 4:
      clearspeed();
      digitalWrite(M4,1);
      NodeSerial.print("t");
      break;
  }
  }
}
