BLYNK_WRITE(V1) 
{
  int pinValue = param.asInt();
  
  if(pinValue==1 && Bord=="master"){
     digitalWrite(2,0);
     Serial.println("1");
  }else{digitalWrite(2,1);}
}

BLYNK_WRITE(V11) 
{
  int pinValue = param.asInt();
  
  if(pinValue==1 && Bord=="master"){
    Serial.println("1"); 
    digitalWrite(2,0 );  
    }else{digitalWrite(2,1);}   
  Blynk.virtualWrite(V1,pinValue );  
}
