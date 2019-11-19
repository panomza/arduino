BLYNK_WRITE(V6) //Chanal 1
{
  int pinValue = param.asInt();
  Serial.println("1");
  
  if(pinValue==1 && Bord =="slave"){
     digitalWrite(3,0);
     button6 = 1;   
     }
  if(pinValue==0 && Bord =="slave"){
     digitalWrite(3,1);
     button6 = 0;
     }
} 

BLYNK_WRITE(V16) 
{
  int pinValue = param.asInt();
  Serial.println("1");
  
  if(pinValue==1 && Bord =="slave"){   
    digitalWrite(3,0);  
    button6 = 1;
    }
  if(pinValue==0 && Bord =="slave"){
    digitalWrite(3,1);
    button6 = 0;
    }  
  Blynk.virtualWrite(V6,pinValue );  
}

///////////////////////////////////////

BLYNK_WRITE(V7) //Chanal 2
{
  int pinValue = param.asInt();
  Serial.println("2");
  
  if(pinValue==1 && Bord =="slave"){
     digitalWrite(0,0);
     button7 = 1;
     }
  if(pinValue==0 && Bord =="slave"){
     digitalWrite(0,1);
     button7 = 0;
     }
}

BLYNK_WRITE(V17) 
{
  int pinValue = param.asInt();
  Serial.println("2");
  
  if(pinValue==1 && Bord =="slave"){ 
    digitalWrite(0,0);  
    button7 = 1;
    }
  if(pinValue==0 && Bord =="slave"){
    digitalWrite(0,1);
    button7 = 0;
    } 
  Blynk.virtualWrite(V7,pinValue );  
}

////////////////////////////////////////

BLYNK_WRITE(V8) //Chanal 3
{
  int pinValue = param.asInt();
  Serial.println("3");
  
   if(pinValue==1 && Bord =="slave"){
     digitalWrite(2,0);  
     button8 = 1;   
     }
  if(pinValue==0 && Bord =="slave"){
    digitalWrite(2,1);
    button8 = 0;
    }
}

BLYNK_WRITE(V18) 
{
  int pinValue = param.asInt();
  Serial.println("3"); 
  
  if(pinValue==1 && Bord =="slave"){
    digitalWrite(2,0); 
    button8 = 1;
    }
  if(pinValue==0 && Bord =="slave"){
    digitalWrite(2,1);
    button8 = 0;
    }
  Blynk.virtualWrite(V8,pinValue );    
}

//////////////////////////////////////////

BLYNK_WRITE(V9) //Chanal 4
{
  int pinValue = param.asInt();
  Serial.println("4");
  
  if(pinValue==1 && Bord =="slave"){
     digitalWrite(1,0);  
     button9 = 1;  
     }
  if(pinValue==0 && Bord =="slave"){
     digitalWrite(1,1);
     button9 = 0;
     }
}

BLYNK_WRITE(V19) 
{
  int pinValue = param.asInt();
  Serial.println("4");
  
  if(pinValue==1 && Bord =="slave"){  
    digitalWrite(0,0); 
    button9 = 1;
    }
  if(pinValue==0 && Bord =="slave"){
    digitalWrite(0,1);
    button9 = 0;
    } 
  Blynk.virtualWrite(V9,pinValue ); 
}
