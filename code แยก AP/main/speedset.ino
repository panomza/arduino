void speedset(){

 if ((Bs != Ls) && (stateP==0) && (Bs == 0)&& (currenttime-speedt0 > buttondelay)){  
     Ls=Bs;
     index++;
     speedt0=currenttime;             // get the current time
     beepvarB=1;
     if(index>4){index=1;}
     Serial.print("Speed is : ");
     Serial.println(index);
     applythespeedswitch();
 }
 else if ((Bs != Ls) && (Bs == 1)&& (currenttime-speedt0 > buttondelay)){
    Ls=Bs;
  }
}

void applythespeedswitch(){
  
    switch (index) {
    case 0:
      clearspeed();
      break;
    case 1:
      clearspeed();
      digitalWrite(M1,1);   
      break;
    case 2:
      clearspeed();
      digitalWrite(M2,1);
      break;
    case 3:
      clearspeed();
      digitalWrite(M3,1);
      break;
    case 4:
      clearspeed();
      digitalWrite(M4,1);
      break;
  }
  
}
