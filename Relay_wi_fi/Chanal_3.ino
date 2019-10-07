BLYNK_WRITE(V4) //Chanal 3
{
  int pinValue = param.asInt();
  
   if(pinValue==1 && Bord_Set=="master"){
     digitalWrite(3,0);
     Serial.println("3");
     }else{digitalWrite(2,1);}
}

BLYNK_WRITE(V14) 
{
  int pinValue = param.asInt();
  
  if(pinValue==1 && Bord_Set=="master"){
    Serial.println("3"); 
    digitalWrite(3,0); 
    }else{digitalWrite(2,1);} 
  Blynk.virtualWrite(V4,pinValue );    
}
