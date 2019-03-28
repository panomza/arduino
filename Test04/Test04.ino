
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


// wifimanager
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

int select_timer = 0;
int select_speed = 0;
int on_off = 2;
float lastread = 0;
int Lpm = 0;
int statePM = 0;
int La = 0;
int stateA = 0;

#include <SoftwareSerial.h>
SoftwareSerial NanoSerial(D3, D2); // RX | TX

//wifi variables
//const char auth[] = "a7a249ec5f2c41edabf98479ba690559";
const char auth[] = "d7c89935fa6449caabdb6753b6d80b11";



bool plasma = 0;
bool Auto   = 0;
bool offbutton = 0;
bool speed1 = 0;
bool speed2 = 0;
bool speed3 = 0;
bool speed4 = 0;
float lastSpeed = 0;


void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());

  Serial.println(myWiFiManager->getConfigPortalSSID());
}


 


void clearspeed()
{
  speed1    = 0;
  speed2    = 0;
  speed3    = 0;
  speed4    = 0;
}


/// send to stupid board


void readReturnSignal(float current_time) { 
  
  char datar = NanoSerial.read();

  if (datar=='P')
      {
       Serial.print(datar);
       Serial.println("ON");
       Blynk.virtualWrite(V0, 1);
       Serial.println("ON is pressed");
       select_speed=1; 
      } else
  if (datar=='p')
      {
       Serial.println("OFF is pressed");
       Blynk.virtualWrite(V5, 0);
       Blynk.virtualWrite(V0, 0);
       on_off = 0;
       select_speed = 0;
       select_timer = 0;
       statePM=0;
       stateA=0;
      }
  if (datar=='s')
  {
    select_speed++;
  }
}

void selectspeed()
{
//  Serial.println(select_speed);
  switch (select_speed) {
      case 1:
        clearspeed();
        Serial.println("speed 1 ");
        Blynk.virtualWrite(V5, 1);
   

        break;
      case 2:
        clearspeed();
        Serial.println("speed 2 ");
        Blynk.virtualWrite(V5, 2);
   
        break;
      case 3:
        clearspeed();
        Serial.println("speed 3 ");
        Blynk.virtualWrite(V5, 3);

        break;
      case 4:
        clearspeed();
        Serial.println("speed 4 ");
        Blynk.virtualWrite(V5, 4);
        break;
      case 5:
        clearspeed();
        Serial.println("speed 1 ");
        Blynk.virtualWrite(V5, 1);
        break;
    }
}

// Blynk read and write functions
// user push speed buttons

BLYNK_WRITE(V0) // ON-OFF
{
  int pinValue = param.asInt();

    if (pinValue == 1) {
        NanoSerial.print("P");
        on_off++;
    if(on_off>2){on_off=1;}
    
    }
}

BLYNK_WRITE(V1) // Speed
{
  int pinValue = param.asInt();
  if (pinValue == 1 && on_off == 1 && millis() - lastSpeed > 50) {
    
      NanoSerial.print("s");
    
      if(select_speed>4){select_speed=1;}
  }
}



BLYNK_WRITE(V2) //Plasma
{  

  int pinValue = param.asInt();

  if ((pinValue != Lpm) && pinValue == 1 && on_off == 1)
  {
    NanoSerial.print("p");
    statePM = !statePM;
    pinValue = Lpm;
    Serial.println("Plasma ON");
  }
  else {
    Lpm = pinValue;
  }

}

BLYNK_WRITE(V3) // Timer
{
  int pinValue = param.asInt();
  if (pinValue == 1 && on_off == 1) {
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

  if ((pinValue != La) && pinValue == 1 && on_off == 1)
  {
    stateA = !stateA;
    pinValue = La;
    Serial.println("AutoON");
    Serial.println(stateA);

  }
  else {
    La = pinValue;
  }

}


void led_app()
{
  WidgetLED led1(V7);
  if(statePM==1){led1.setValue(255);}else{led1.setValue(0);}
  WidgetLED led2(V8);
  if(stateA==1){led2.setValue(255);}else{led2.setValue(0);}
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


  NanoSerial.begin(57600);
}


void loop()
{
  Blynk.run();
  float current_time = millis();
  readReturnSignal(current_time);
  selectspeed();
  led_app();
}
