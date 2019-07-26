
void transfer_data_Bord()
{
  fail_check_sent(); 
  if (buttonP==1||buttonS==1||buttonP==1||buttonA==1){senddata();}
}


void senddata()
{
      DynamicJsonDocument jsonBuffer(JSON_OBJECT_SIZE(3) + 100);
      JsonObject root = jsonBuffer.to<JsonObject>();
      JsonObject state = root.createNestedObject("state");
      JsonObject state_desired = state.createNestedObject("desired");

    
      state_desired["power" ] = buttonP;
      state_desired["speed"] = buttonS;
      state_desired["timer"] = buttonT;
      state_desired["auto"] = buttonA;
    
      Serial.print("Sending to bord ");
      serializeJson(root,Serial);//send command      Serial.println(root);   
      Serial.print("\n"); 
      char key[measureJson(root) + 1];
      serializeJson(root, key, sizeof(key));
      
   NanoSerial.print(key);
   NanoSerial.print("\n");

}


char failcheck ;
String datacheck;
byte check=0;

void fail_check_sent()
{
  if(NanoSerial.available()>0){
      failcheck = NanoSerial.read(); 
      datacheck += failcheck;
      
      if(failcheck =='\n'){
        
      StaticJsonDocument<300> jsonBuffer;     
      deserializeJson(jsonBuffer, datacheck);      
      JsonObject root = jsonBuffer.as<JsonObject>();
      
      int fail = root ["failed"];
          
 
       if (fail == 1)
             {
              Serial.println(datacheck);
              senddata();          
             }
             datacheck = failcheck ;
        }
    }

}

/////////////////////////////////////////////////////////////////////+

char data_bord ;
String dataj_bord;

void receive_bord()
{
  if(NanoSerial.available()>0){
        
    data_bord = NanoSerial.read(); 
    dataj_bord += data_bord;
    
    StaticJsonDocument<400> jsonBuffer;
    deserializeJson(jsonBuffer, dataj_bord); 
    JsonObject root = jsonBuffer.as<JsonObject>();
    
   
      String Power = root ["state"]["desired"]["power"];
      String Speed = root ["state"]["desired"]["speed"];
      String Timer = root ["state"]["desired"]["timer"];
      String Auto = root ["state"]["desired"]["auto"];

      Bpower = root ["state"]["desired"]["power"];
      Bspeed = root ["state"]["desired"]["speed"];
      Btimer = root ["state"]["desired"]["timer"];
      Bauto = root ["state"]["desired"]["auto"];

//            // Print values.
//     Serial.print("Receive bord :"); Serial.print("Power = "); Serial.println(Power);
//     Serial.print("Receive bord :"); Serial.print("Speed = "); Serial.println(Speed);
//     Serial.print("Receive bord :"); Serial.print("timer = "); Serial.println(Timer);
//     Serial.print("Receive bord :"); Serial.print("Auto  = "); Serial.println(Auto);

    if (Bpower ==0){Bspeed =0;Btimer=0;Bauto=0;}
    if(Power == "null" ||Speed =="null" || Timer =="null" ||Auto =="null")
      {
      check=1;     
      }
      else{
        check=0;
        }  
        dataj_bord = data_bord;
   }
}
