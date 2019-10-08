BLYNK_WRITE(V6) //Chanal 1
{
  int pinValue = param.asInt();
  
  if(pinValue==1 && Bord =="master"){
     digitalWrite(2,0);
     Serial.println("2");
     }else{digitalWrite(2,1);}
}

BLYNK_WRITE(V16) 
{
  int pinValue = param.asInt();
  
  if(pinValue==1 && Bord =="master"){
    Serial.println("2");
    digitalWrite(2,0);  
    }else{digitalWrite(2,1);}   
  Blynk.virtualWrite(V6,pinValue );  
}

///////////////////////////////////////

BLYNK_WRITE(V7) //Chanal 2
{
  int pinValue = param.asInt();
  
  if(pinValue==1 && Bord =="master"){
     digitalWrite(0,0);
     Serial.println("2");
     }else{digitalWrite(0,1);}
}

BLYNK_WRITE(V17) 
{
  int pinValue = param.asInt();
  
  if(pinValue==1 && Bord =="master"){
    Serial.println("2");
    digitalWrite(0,0);  
    }else{digitalWrite(0,1);}   
  Blynk.virtualWrite(V7,pinValue );  
}


BLYNK_WRITE(V8) //Chanal 3
{
  int pinValue = param.asInt();
  
   if(pinValue==1 && Bord_Set=="master"){
     digitalWrite(3,0);
     Serial.println("3");
     }else{digitalWrite(2,1);}
}

BLYNK_WRITE(V18) 
{
  int pinValue = param.asInt();
  
  if(pinValue==1 && Bord_Set=="master"){
    Serial.println("3"); 
    digitalWrite(3,0); 
    }else{digitalWrite(2,1);} 
  Blynk.virtualWrite(V8,pinValue );    
}

BLYNK_WRITE(V9) //Chanal 4
{
  int pinValue = param.asInt();
  if(pinValue==1  && Bord_Set=="master"){
     digitalWrite(1,0);
     Serial.println("4");
     }else{digitalWrite(2,1);}
}

BLYNK_WRITE(V19) 
{
  int pinValue = param.asInt();
  if(pinValue==1 && Bord_Set=="master"){
    Serial.println("4");
    digitalWrite(1,!pinValue ); 
    }else{digitalWrite(2,1);}  
  Blynk.virtualWrite(V9,pinValue ); 
}
