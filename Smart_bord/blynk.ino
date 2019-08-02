
int h = 0;
int t = 0;
unsigned int time_DHT = 0;


void Sensor_DHT(){

    if (millis()-time_DHT>1000){
      time_DHT=millis();
 
       h = dht.readHumidity();
       t = dht.readTemperature();
       
      Blynk.virtualWrite(V11,t);
      Blynk.virtualWrite(V10,h);
    }
}

void button_key(){
  if (state_button==1){
    
       send_button_state();
    
        buttonP = 0;
        buttonS = 0;
        buttonT = 0;
        buttonA = 0;   
    }
}

BLYNK_WRITE(V0) // ON-OFF
{
    if (param.asInt()==1){
        buttonP=1;
        state_button=1;
    }else{state_button=0;}
}

BLYNK_WRITE(V1) // Speed
{
  if (param.asInt()==1){
      buttonS=1;
      state_button=1;
    }else{state_button=0;} 
             
}

BLYNK_WRITE(V3) // Timer
{
  if (param.asInt()==1){
      buttonT=1;
      state_button=1;
    }else{state_button=0;} 
          
}

BLYNK_WRITE(V4) //Auto
{  
   if (param.asInt()==1){
       buttonA=1;
       state_button=1;
    }else{state_button=0;}
        
}

  /////////////// wifimanager//////////////////


void wifi(){


if (datar=='W'){
  digitalWrite(1,0);
  WiFi.disconnect();
  WiFiManager wifiManager;
  wifiManager.setAPCallback(configModeCallback);
  wifiManager.autoConnect("Air Purifier"); 
  digitalWrite(1,1);

      NanoSerial.print("w"); NanoSerial.print("w");
      NanoSerial.print("w"); NanoSerial.print("w");
      NanoSerial.print("w"); NanoSerial.print("w");
      NanoSerial.print("w"); NanoSerial.print("w");
      NanoSerial.print("w"); NanoSerial.print("w");
      NanoSerial.print("w"); NanoSerial.print("w");
      NanoSerial.print("w"); NanoSerial.print("w");
           
  } 
 
}


/////////////////////////////////////////////////////////////////////////////////////////////
