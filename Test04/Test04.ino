
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include "DHT.h"
#define DHTPIN 3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


// wifimanager
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

#include <ArduinoJson.h> 

#include <SoftwareSerial.h>
//SoftwareSerial NanoSerial(2, 0); // RX | TX
SoftwareSerial NanoSerial(D2, D3); // RX | TX

//wifi variables

const char auth[] = "d7c89935fa6449caabdb6753b6d80b11";


void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/// read the stupid board

char datar;

char data_bord ;
String dataj_bord;

unsigned int dust=0;
float timer=0;
unsigned int Speed=0;
unsigned int Power=0;
unsigned int Auto=0;




byte state_button = 0;

// Blynk read button and Trasfer functions///////////////////////////////////////////////////////////


int h = 0;
int t = 0;
unsigned int time_DHT = 0;


byte button=0;
byte num=10;

BLYNK_WRITE(V0) // ON-OFF
{
  while(button<num){
      NanoSerial.print("O"); 
      button++;
      Serial.println(button);
     
  } 
  button=0;   
}

BLYNK_WRITE(V1) // Speed
{
  while(button<num){
      NanoSerial.print("s"); 
      button++;
      Serial.println(button);
      ;
  } 
  button=0;           
}

BLYNK_WRITE(V3) // Timer
{
  while(button<num){
      NanoSerial.print("t"); 
      button++;
      Serial.println(button);
      
  } 
  button=0;          
}

BLYNK_WRITE(V4) //Auto
{  
   while(button<num){
      NanoSerial.print("a"); 
      button++;
     
  } 
  button=0;           
}

  /////////////// wifimanager//////////////////




/////////////////////////////////////////////////////////////////////////////////////////////

void setup()
{

//  Serial.begin(9600);

  dht.begin();
  
  WiFiManager wifiManager;  
  wifiManager.setAPCallback(configModeCallback);
  wifiManager.setConfigPortalTimeout(180);
  wifiManager.autoConnect("Air Purifier");
  
  Blynk.config(auth);

  /////////////////////////////////Send data////////////////////////////////////
  
  pinMode(D2, INPUT);
  pinMode(D3, OUTPUT);
  
//  pinMode(0, INPUT);
//  pinMode(2, OUTPUT);
  
//  pinMode(3, INPUT);
//  pinMode(1, OUTPUT);

  NanoSerial.begin(57600);
  
}





void loop()
{
  Blynk.run();
  
//  receive_bord();
  
//  Sensor_DHT();

//  wifi();

}
