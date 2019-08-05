bool check =0;

void senddata()
{

   if (Bpower==1){
    NanoSerial.print("O");
    NanoSerial.print("\n");
  
    }
    if (Bspeed==1){
    NanoSerial.print("s");
    NanoSerial.print("\n");
   
    }
    if (Btimer==1){
    NanoSerial.print("t");
    NanoSerial.print("\n");
  
    }
    if (Bauto==1){
    NanoSerial.print("a");
    NanoSerial.print("\n");
   
    }
}




/////////////////////////////////////////////////////////////////////



void receive_bord()
{
  if(NanoSerial.available()>0){
     
    data_bord = NanoSerial.read(); 
    dataj_bord += data_bord;
    
    StaticJsonDocument<400> jsonBuffer;
    deserializeJson(jsonBuffer, dataj_bord); 
    
    if (data_bord=='\n'){
          
    JsonObject root = jsonBuffer.as<JsonObject>();

//    Serial.println (dataj_bord );
    
      String stateP_s = root ["state"]["desired"]["power"];
      String index_s = root ["state"]["desired"]["speed"];
      String timeshow2_s = root ["state"]["desired"]["timer"];
      String stateA_s = root ["state"]["desired"]["auto"];
      String dust_s = root ["state"]["desired"]["dust"];

      Power = root ["state"]["desired"]["power"];
      Speed = root ["state"]["desired"]["speed"];
      timer = root ["state"]["desired"]["timer"];
      Auto = root ["state"]["desired"]["auto"];
      dust = root ["state"]["desired"]["dust"];

   if(stateP_s  == "null" ||index_s =="null" || timeshow2_s =="null" ||stateA_s =="null" ||dust_s=="null")
      {
//      Serial.println("failed");
      }
      else{

      sendData();
      
      Power = root ["state"]["desired"]["power"];
      Speed = root ["state"]["desired"]["speed"];
      timer = root ["state"]["desired"]["timer"];
      Auto = root ["state"]["desired"]["auto"];
      dust = root ["state"]["desired"]["dust"];

      timer=timer/100;
      
        // Print values.
//       Serial.print("Receive bord :"); Serial.print("Power = "); Serial.println(Power);
//       Serial.print("Receive bord :"); Serial.print("Speed = "); Serial.println(Speed);
//       Serial.print("Receive bord :"); Serial.print("timer = "); Serial.println(timer);
//       Serial.print("Receive bord :"); Serial.print("Auto  = "); Serial.println(Auto);
//       Serial.print("Receive bord :"); Serial.print("Dust  = "); Serial.println(dust);
 status_blynk();
        }  
        dataj_bord = data_bord; 
    }
 
      if (data_bord=='F'){
        Bpower=0;
        Bspeed=0;
        Btimer=0;
        Bauto=0;
      }
      
      
  }
}
