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
    }else{digitalWrite(2,1);}   
  Blynk.virtualWrite(V3,pinValue );  
}
