BLYNK_WRITE(V5) // ALL ON
{
  int pinValue = param.asInt();

     digitalWrite(0,0);
     digitalWrite(1,0);
     digitalWrite(2,0);
     digitalWrite(3,0);
     
     Blynk.virtualWrite(V1,1 );
     Blynk.virtualWrite(V2,1 ); 
     Blynk.virtualWrite(V3,1 ); 
     Blynk.virtualWrite(V4,1 ); 
         
}

BLYNK_WRITE(V15) 
{
  int pinValue = param.asInt();

     digitalWrite(0,1);
     digitalWrite(1,1);
     digitalWrite(2,1);
     digitalWrite(3,1);
     
     Blynk.virtualWrite(V1,0 );
     Blynk.virtualWrite(V2,0 ); 
     Blynk.virtualWrite(V3,0 ); 
     Blynk.virtualWrite(V4,0 ); 
     Blynk.virtualWrite(V5,0 );
}
