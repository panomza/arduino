BLYNK_WRITE(V1) //Chanal 1
{
  int pinValue = param.asInt();
  
  if(pinValue==1 && Bord =="master"){
     digitalWrite(2,0);
     Serial.println("2");
     }else{digitalWrite(2,1);}
}

BLYNK_WRITE(V11) 
{
  int pinValue = param.asInt();
  
  if(pinValue==1 && Bord =="master"){
    Serial.println("2");
    digitalWrite(2,0);  
    }else{digitalWrite(2,1);}   
  Blynk.virtualWrite(V2,pinValue );  
}

///////////////////////////////////////

BLYNK_WRITE(V2) //Chanal 2
{
  int pinValue = param.asInt();
  
  if(pinValue==1 && Bord =="master"){
     digitalWrite(0,0);
     Serial.println("2");
     }else{digitalWrite(0,1);}
}

BLYNK_WRITE(V12) 
{
  int pinValue = param.asInt();
  
  if(pinValue==1 && Bord =="master"){
    Serial.println("2");
    digitalWrite(0,0);  
    }else{digitalWrite(0,1);}   
  Blynk.virtualWrite(V2,pinValue );  
}


BLYNK_WRITE(V3) //Chanal 3
{
  int pinValue = param.asInt();
  
   if(pinValue==1 && Bord_Set=="master"){
     digitalWrite(3,0);
     Serial.println("3");
     }else{digitalWrite(2,1);}
}

BLYNK_WRITE(V13) 
{
  int pinValue = param.asInt();
  
  if(pinValue==1 && Bord_Set=="master"){
    Serial.println("3"); 
    digitalWrite(3,0); 
    }else{digitalWrite(2,1);} 
  Blynk.virtualWrite(V3,pinValue );    
}

BLYNK_WRITE(V4) //Chanal 4
{
  int pinValue = param.asInt();
  if(pinValue==1  && Bord_Set=="master"){
     digitalWrite(1,0);
     Serial.println("4");
     }else{digitalWrite(2,1);}
}

BLYNK_WRITE(V14) 
{
  int pinValue = param.asInt();
  if(pinValue==1 && Bord_Set=="master"){
    Serial.println("4");
    digitalWrite(1,!pinValue ); 
    }else{digitalWrite(2,1);}  
  Blynk.virtualWrite(V4,pinValue ); 
}
