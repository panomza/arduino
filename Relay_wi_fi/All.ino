BLYNK_WRITE(V5) // ALL ON
{
  int pinValue = param.asInt();
  Serial.println("all on");
  
  if(pinValue==1 && Bord =="master"){
  
     digitalWrite(0,0);
     digitalWrite(1,0);
     digitalWrite(2,0);
     digitalWrite(3,0);
     
     Blynk.virtualWrite(V1,1 );
     Blynk.virtualWrite(V2,1 ); 
     Blynk.virtualWrite(V3,1 ); 
     Blynk.virtualWrite(V4,1 ); 

      button1 = 1;
      button2 = 1;
      button3 = 1;
      button4 = 1;
  }
  
  if(pinValue==1 && Bord =="slave"){
    
     digitalWrite(0,0);
     digitalWrite(1,0);
     digitalWrite(2,0);
     digitalWrite(3,0);
     
     Blynk.virtualWrite(V6,1 );
     Blynk.virtualWrite(V7,1 ); 
     Blynk.virtualWrite(V8,1 ); 
     Blynk.virtualWrite(V9,1 ); 

      button6 = 1;
      button7 = 1;
      button8 = 1;
      button9 = 1;
  }
}

BLYNK_WRITE(V15) // ALL OFF
{
  int pinValue = param.asInt();
  Serial.println("all off");
   
  if(pinValue==1 && Bord =="master"){
    
     digitalWrite(0,1);
     digitalWrite(1,1);
     digitalWrite(2,1);
     digitalWrite(3,1);
     
     Blynk.virtualWrite(V1,0 );
     Blynk.virtualWrite(V2,0 ); 
     Blynk.virtualWrite(V3,0 ); 
     Blynk.virtualWrite(V4,0 ); 
     
      button1 = 0;
      button2 = 0;
      button3 = 0;
      button4 = 0;
  }
  
  if(pinValue==1 && Bord =="slave"){
    
     digitalWrite(0,1);
     digitalWrite(1,1);
     digitalWrite(2,1);
     digitalWrite(3,1);
     
     Blynk.virtualWrite(V6,0 );
     Blynk.virtualWrite(V7,0 ); 
     Blynk.virtualWrite(V8,0 ); 
     Blynk.virtualWrite(V9,0 ); 
     
      button6 = 0;
      button7 = 0;
      button8 = 0;
      button9 = 0;
  }
}
