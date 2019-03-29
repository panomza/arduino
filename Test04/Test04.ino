
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


short int dust=0;


void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
}


 
short int select_timer = 0;
short int select_speed = 0;

const int m1 = D4;
const int m2 = D5;
const int m3 = D6;
const int m4 = D7;



/// send to stupid board


void readReturnSignal(float current_time) { 
  
  char datar = NanoSerial.read();

  if (datar=='O')
      {
       Serial.print(datar);
       Serial.println("ON");
       Blynk.virtualWrite(V0, 1);
       Serial.println("ON is pressed");
       select_speed = 1; 
      } else
  if (datar=='F')
      {
       Serial.println("OFF is pressed");
       Blynk.virtualWrite(V5, 0);
       Blynk.virtualWrite(V0, 0);
       WidgetLED led1(V7);
       led1.setValue(0);
       WidgetLED led2(V8);
      led2.setValue(0);
       select_speed = 0; 
      }else

//////////////////////////////SPEED////////////////////
  if (datar=='l'){select_speed=1;}else
  if (datar=='m'){select_speed=2;}else
  if (datar=='h'){select_speed=3;}else
  if (datar=='t'){select_speed=4;}else 

////////////////////////plasma////////////////////////
  if (datar=='P')
      {
      Serial.println("Plasma On");
      WidgetLED led1(V7);
      led1.setValue(255);
      }else
      
  if (datar=='p')
      {
      Serial.println("Plasma Off");
      WidgetLED led1(V7);
      led1.setValue(0);
      }else
      
  if (datar=='A')
      {
      Serial.println("Plasma On");
      WidgetLED led2(V8);
      led2.setValue(255);
      }else
      
  if (datar=='a')
      {
      Serial.println("Plasma Off");
      WidgetLED led2(V8);
      led2.setValue(0);
      }else
    
  if (datar=='d')
      {
        dust = NanoSerial.parseInt(); 
        Blynk.virtualWrite(V9, dust);
      }

}
void selectspeed()
{
//  Serial.println(select_speed);
  switch (select_speed) {

      case 0:
            clearspeed();
            break;
      case 1:
        clearspeed();
        digitalWrite(m1,0);
        Serial.println("speed 1 ");
        Blynk.virtualWrite(V5, 1);
        break;
      case 2:
        clearspeed();
        digitalWrite(m2,0);
        Serial.println("speed 2 ");  
        Blynk.virtualWrite(V5, 2); 
        break;
      case 3:
        clearspeed();
        digitalWrite(m3,0);
        Serial.println("speed 3 ");
        Blynk.virtualWrite(V5, 3);
        break;
      case 4:
        clearspeed();
        digitalWrite(m4,0);
        Serial.println("speed 4 ");       
        Blynk.virtualWrite(V5, 4);
        break;
    }
}

void clearspeed()
{
  digitalWrite(m1,1);
  digitalWrite(m2,1);
  digitalWrite(m3,1);
  digitalWrite(m4,1);
}
// Blynk read button and Trasfer functions

BLYNK_WRITE(V0) // ON-OFF
{
  int pinValue = param.asInt();
    if (pinValue == 1) {
        NanoSerial.print("O"); 
    }
}

BLYNK_WRITE(V1) // Speed
{
  int pinValue = param.asInt();
    if (pinValue == 1) {
      NanoSerial.print("s");
  }
}

BLYNK_WRITE(V2) //Plasma
{  

 int pinValue = param.asInt();
    if (pinValue == 1) {
    NanoSerial.print("p");
  }
}

BLYNK_WRITE(V3) // Timer
{
  int pinValue = param.asInt();
  if (pinValue == 1) {
    select_timer++;
  }
  switch (select_timer) {
    case 1:
      Serial.println("Timer 1 ");
      Blynk.virtualWrite(V6, 1);
      break;
    case 2:
      Serial.println("Timer 2 ");
      Blynk.virtualWrite(V6, 2);
      break;
    case 3:
      Serial.println("Timer 3 ");
      Blynk.virtualWrite(V6, 3);
      break;
    case 4:
      Serial.println("Timer 4 ");
      Blynk.virtualWrite(V6, 4);
      break;
    case 5:
      select_timer = 0;
      Blynk.virtualWrite(V6, 0);
      break;
  }
}

BLYNK_WRITE(V4) //Auto
{
  int pinValue = param.asInt();
    if (pinValue == 1 ){
   NanoSerial.print("a");
  }
}


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

  pinMode(m1,OUTPUT);
  pinMode(m2,OUTPUT);
  pinMode(m3,OUTPUT);
  pinMode(m4,OUTPUT);


  NanoSerial.begin(57600);
}


void loop()
{
  Blynk.run();
  float current_time = millis();
  readReturnSignal(current_time);
  selectspeed();
}
