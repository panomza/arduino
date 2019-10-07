BLYNK_WRITE(V1) // ALL ON
{
  int pinValue = param.asInt();

     digitalWrite(0,0);
     digitalWrite(1,0);
     digitalWrite(2,0);
     digitalWrite(3,0);

     Blynk.virtualWrite(V2,1 ); 
     Blynk.virtualWrite(V3,1 ); 
     Blynk.virtualWrite(V4,1 ); 
     Blynk.virtualWrite(V5,1 );    
}

BLYNK_WRITE(V11) 
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
