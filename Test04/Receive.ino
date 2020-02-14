
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
            Blynk.virtualWrite(V0, !Power);
            Blynk.virtualWrite(V5,Speed);
            Blynk.virtualWrite(V9, dust);
            Blynk.virtualWrite(V2,timer/100);


            WidgetLED led2(V8);
             if(Auto==1){led2.setValue(255);}
             if(Auto==0){led2.setValue(0);}
        
        }  
        dataj_bord = data_bord; 
    }
 
      
      
  }
}
