void speedset(){

 if ((Bs != Ls) && (stateP==0) && (Bs == 0)&& (currenttime-speedt0 > buttondelay)&&speedcount==0){  
     Ls=Bs;
     speedcount=1;
     index++;
     speedt0=currenttime;      // get the current time
     beepvarB=1;
     if(index>5){index=1;}
//     Serial.print("Speed is : ");
//     Serial.println(index);
     applythespeedswitch();
 }
 else if ((Bs != Ls) && (Bs == 1)&& (currenttime-speedt0 > buttondelay)&&speedcount==1){
      Ls=Bs;
      speedcount=0;
  }
}

void applythespeedswitch(){
  
    switch (index) {
    case 0:
      clearspeed();
      stateA=0;
      break;
    case 1:
      clearspeed();
      digitalWrite(M1,1);  
      digitalWrite(s1,1); 
      stateA=0;
      break;
    case 2:
      clearspeed();
      digitalWrite(M2,1);
      digitalWrite(s2,1);
      stateA=0;
      break;
    case 3:
      clearspeed();
      digitalWrite(M3,1);
      digitalWrite(s3,1);
      stateA=0;
      break;
    case 4:
      clearspeed();
      digitalWrite(M4,1);
      digitalWrite(s4,1);
      stateA=0;
      break;
     case 5:
      clearspeed();
      stateA=1;
      break;
  }
  
}

void clearspeed(){
      
      digitalWrite(M1,0);  
      digitalWrite(M2,0);
      digitalWrite(M3,0);
      digitalWrite(M4,0);

      digitalWrite(s1,0);
      digitalWrite(s2,0);
      digitalWrite(s3,0);
      digitalWrite(s4,0); 
         
}
