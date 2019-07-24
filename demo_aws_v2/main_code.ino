




//// wifimanager
//#include <DNSServer.h>
//#include <ESP8266WebServer.h>
//#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager



//wifi variables






//////////////////////////////////////////////////////////////////////////////////////////////////////
/// read the stupid board

char datar;

unsigned int dust=0;
float timer=0;
unsigned int Speed=0;
unsigned int Power=0;
unsigned int Auto=0;

void readReturnSignal() { 
  

  if(NanoSerial.available()>0){
        
      datar = NanoSerial.read();
    
        if (datar=='S'){
             Speed = NanoSerial.parseInt(); 
             Blynk.virtualWrite(V5,Speed);
             }
        if (datar=='d'){
             dust = NanoSerial.parseInt();
             Blynk.virtualWrite(V9, dust);
            }
        if (datar=='A'){
             Auto = NanoSerial.parseInt();
             WidgetLED led2(V8);
             if(Auto==1){led2.setValue(255);}
             if(Auto==0){led2.setValue(0);}
            }
        if (datar=='P'){
           Power = NanoSerial.parseInt();
           Blynk.virtualWrite(V0, !Power);
            }
        if (datar=='T'){
           timer = NanoSerial.parseFloat(); 
           Blynk.virtualWrite(V6,timer);}      
            }
}


// Blynk read button and Trasfer functions///////////////////////////////////////////////////////////


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



BLYNK_WRITE(V0) // ON-OFF
{
  if(button<num){
      NanoSerial.print("O"); 
      button++;
      Serial.println(button);

  } else{ button=0;  }  
  
}

BLYNK_WRITE(V1) // Speed
{
  if(button<num){
      NanoSerial.print("s"); 
      button++;
      Serial.println(button);
      ;
  } else{ button=0;  }  
             
}

BLYNK_WRITE(V3) // Timer
{
  if(button<num){
      NanoSerial.print("t"); 
      button++;
      Serial.println(button);
      
  } else{ button=0;  }  
          
}

BLYNK_WRITE(V4) //Auto
{  
   if(button<num){
      NanoSerial.print("a"); 
      button=1;
     
  } else{ button=0;  }  
        
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
