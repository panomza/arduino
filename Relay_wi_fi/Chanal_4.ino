BLYNK_WRITE(V5) //Chanal 4
{
  int pinValue = param.asInt();
  if(pinValue==1  && Bord_Set=="master"){
     digitalWrite(1,0);
     Serial.println("4");
     }else{digitalWrite(2,1);}
}

BLYNK_WRITE(V15) 
{
  int pinValue = param.asInt();
  if(pinValue==1 && Bord_Set=="master"){
    Serial.println("4");
    digitalWrite(1,!pinValue ); 
    }else{digitalWrite(2,1);}  
  Blynk.virtualWrite(V5,pinValue ); 
}
