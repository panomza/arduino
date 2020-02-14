BLYNK_WRITE(V1) //Chanal 1
{
  int pinValue = param.asInt();
  Serial.println("1");  
     
  if(pinValue==1 && Bord =="master"){
     digitalWrite(3,0);
     button1 = 1;
     }
  if(pinValue==0 && Bord =="master"){
     digitalWrite(3,1);
     button1 = 0;
     }   
}

BLYNK_WRITE(V11) 
{
  int pinValue = param.asInt();
  Serial.println("1");
  
  if(pinValue==1 && Bord =="master"){
    digitalWrite(3,0); 
    button1 = 1; 
    }
  if(pinValue==0 && Bord =="master"){
    digitalWrite(3,1);
    button1 = 0;
    }   
  Blynk.virtualWrite(V1,pinValue );  
}

///////////////////////////////////////

BLYNK_WRITE(V2) //Chanal 2
{
  int pinValue = param.asInt();
  Serial.println("2");
  
  if(pinValue==1 && Bord =="master"){
     digitalWrite(0,0); 
     button2 = 1;  
     }
  if(pinValue==0 && Bord =="master"){
    digitalWrite(0,1);
    button2 = 0;
    }
}

BLYNK_WRITE(V12) 
{
  int pinValue = param.asInt();
  Serial.println("2");
  
  if(pinValue==1 && Bord =="master"){
    digitalWrite(0,0);  
    button2 = 1;
    }
  if(pinValue==0 && Bord =="master"){
    digitalWrite(0,1);
    button2 = 0;
    }  
  Blynk.virtualWrite(V2,pinValue );  
}

////////////////////////////////////

BLYNK_WRITE(V3) //Chanal 3
{
  int pinValue = param.asInt();
  Serial.println("3");
  
   if(pinValue==1 && Bord =="master"){
     digitalWrite(2,0); 
     button3 = 1;
     }
   if(pinValue==0 && Bord =="master"){
     digitalWrite(2,1);
     button3 = 0;
     }
}

BLYNK_WRITE(V13) 
{
  int pinValue = param.asInt();
  Serial.println("3"); 
  
  if(pinValue==1 && Bord =="master"){
    digitalWrite(2,0); 
    button3 = 1;
    }
  if(pinValue==0 && Bord =="master"){
    digitalWrite(2,1);
    button3 = 0;
    }
  Blynk.virtualWrite(V3,pinValue );    
}

BLYNK_WRITE(V4) //Chanal 4
{
  int pinValue = param.asInt();
  Serial.println("4");
  
  if(pinValue==1 && Bord =="master"){
     digitalWrite(1,0);
     button4 = 1;   
     }
  if(pinValue==0 && Bord =="master"){
    digitalWrite(1,1);
    button4 = 0;
    }
}

BLYNK_WRITE(V14) 
{
  int pinValue = param.asInt();
  Serial.println("4");
  
  if(pinValue==1 && Bord =="master"){ 
    digitalWrite(1,0); 
    button4 = 1;
    }
  if(pinValue==0 && Bord =="master"){
    digitalWrite(1,1);
    button4 = 0;
    } 
  Blynk.virtualWrite(V4,pinValue ); 
}
