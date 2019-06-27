
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


// wifimanager
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager


#include <SoftwareSerial.h>
SoftwareSerial NanoSerial(D3, D2); // RX | TX

//wifi variables
//const char auth[] = "a7a249ec5f2c41edabf98479ba690559";
const char auth[] = "d7c89935fa6449caabdb6753b6d80b11";





void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/// read the stupid board

char datar;
unsigned int dust=0;
unsigned int timer=0;
unsigned int Speed=0;

void readReturnSignal() { 
  
  datar = NanoSerial.read();
  Serial.println(datar);
  if (datar=='O')
      {
       Serial.println("ON");
       Blynk.virtualWrite(V0, 1);
      }
  if (datar=='F')
      {
       Blynk.virtualWrite(V5, 0);
       Blynk.virtualWrite(V0, 0);     
       WidgetLED led2(V8);
       led2.setValue(0);
      }

//////////////////////////////SPEED////////////////////
 
  if (datar=='s'){
      Speed = NanoSerial.parseInt(); 
      Blynk.virtualWrite(V5,Speed);}
  
  if (datar=='x'){
      timer = NanoSerial.parseInt(); 
      Blynk.virtualWrite(V6,timer);}
  
      
  if (datar=='A')
      {
//      Serial.println("Auto On");
      WidgetLED led2(V8);
      led2.setValue(255);
      }
      
  if (datar=='a')
      {
//      Serial.println("Auto Off");
      WidgetLED led2(V8);
      led2.setValue(0);
      }
    
  if (datar=='d')
      {
        dust = NanoSerial.parseInt(); 
        Blynk.virtualWrite(V9, dust);
      }

}


// Blynk read button and Trasfer functions///////////////////////////////////////////////////////////
unsigned int current=0;
unsigned int timesent=0;
unsigned int button=0;
unsigned int count0=0;
void sent(){

  
  current=millis();
 
  if(count0>=6){count0=0;}
  if(current-timesent > 1 && count0>0&&button==1) {count0++;NanoSerial.print("O");timesent=current;}
  if(current-timesent > 1 && count0>0&&button==2) {count0++;NanoSerial.print("s");timesent=current;}
  if(current-timesent > 1 && count0>0&&button==3) {count0++;NanoSerial.print("a");timesent=current;}
  if(current-timesent > 1 && count0>0&&button==4) {count0++;NanoSerial.print("t");timesent=current;}
}

BLYNK_WRITE(V0) // ON-OFF
{
  int pinValue = param.asInt();
    if (pinValue == 1) {
       count0=1;
       button=1; 
       NanoSerial.print("O");    
    }  
}

BLYNK_WRITE(V1) // Speed
{
  int pinValue = param.asInt();
    if (pinValue == 1) {
       count0=1;
       button=2;
       NanoSerial.print("s");
  }
}

BLYNK_WRITE(V3) // Timer
{
  int pinValue = param.asInt();
  if (pinValue == 1 ){
       count0=1;
       button=4; 
       NanoSerial.print("t"); 
  }
}

BLYNK_WRITE(V4) //Auto
{
  int pinValue = param.asInt();
    if (pinValue == 1 ){
       count0=1;
       button=3;
       NanoSerial.print("a");  
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  // Debug console
  Serial.begin(9600);

  /////////////// wifimanager//////////////////
  WiFiManager wifiManager;
  wifiManager.setAPCallback(configModeCallback);
  wifiManager.setConfigPortalTimeout(180);
  wifiManager.autoConnect("nodemcu");
  Serial.println("connected...yeey :)");
  Blynk.config(auth);

  /////////////////////////////////Send data////////////////////////////////////
  pinMode(D3, INPUT);
  pinMode(D2, OUTPUT);
  NanoSerial.begin(57600);
}


void loop()
{
  Blynk.run();
  readReturnSignal();
  sent();
}
