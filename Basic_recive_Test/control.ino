void control_status()
{
  if (Bpower == 1 ){
      Serial.print("Receive :");
      Serial.println("Power ON");
      Bpower=0;
      }else{Serial.println("Power OFF");}
   Serial.print("Receive");Serial.print("Speed = ");Serial.println(Bspeed);
   Serial.print("Receive");Serial.print("Timer = ");Serial.println(Btimer);
  if (Bauto == 1 ){Serial.print("Receive");Serial.println("Auto ON");}else{Serial.println("Auto OFF");}
  
        Serial.println();
}
