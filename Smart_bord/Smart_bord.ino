#ifdef ESP32
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>

////////////////// wifimanager ///////////////
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

////////////////// Blynk ////////////////////
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//char datar;
char data_bord ;
String dataj_bord;

int Rpower = 0;
int Rspeed = 0;
int Rtimer = 0;
int Rauto  = 0;

byte buttonP = 0;
byte buttonS = 0;
byte buttonT = 0;
byte buttonA = 0;

unsigned int dust=0;
float timer=0;
unsigned int Speed=0;
unsigned int Power=0;
unsigned int Auto=0;

unsigned int current_time =0;

byte state_button = 0;

const char auth[] = "d7c89935fa6449caabdb6753b6d80b11";

////////////////// DTH //////////////////////
#include "DHT.h"
#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

////////////////// Serial //////////////////
#include <SoftwareSerial.h>
SoftwareSerial NanoSerial(D2, D3); // RX | TX



///////////////// AWS //////////////////////
#else
#error Platform not supported
#endif
#include <WiFiClientSecure.h>
#include <ArduinoJson.h> //https://github.com/bblanchon/ArduinoJson (use v6.xx)
#include <time.h>
#define emptyString String()

//Follow instructions from https://github.com/debsahu/ESP-MQTT-AWS-IoT-Core/blob/master/doc/README.md
//Enter values in secrets.h ▼
#include "secrets.h"

#ifndef PIO_PLATFORM
//#define USE_PUB_SUB  //uncomment to use PubSubClient(https://github.com/knolleary/pubsubclient)
#endif

#if !(ARDUINOJSON_VERSION_MAJOR == 6 and ARDUINOJSON_VERSION_MINOR >= 7)
#error "Install ArduinoJson v6.7.0-beta or higher"
#endif

const int MQTT_PORT = 8883;
const char MQTT_SUB_TOPIC[] = "$aws/things/" THINGNAME "/shadow/update";
const char MQTT_PUB_TOPIC[] = "$aws/things/" THINGNAME "/shadow/update";

#ifdef USE_SUMMER_TIME_DST
uint8_t DST = 1;
#else
uint8_t DST = 0;
#endif

WiFiClientSecure net;

#ifdef ESP8266
BearSSL::X509List cert(cacert);
BearSSL::X509List client_crt(client_cert);
BearSSL::PrivateKey key(privkey);
#endif

#ifdef USE_PUB_SUB
#include <PubSubClient.h>
#if defined(USE_PUB_SUB) and defined(PIO_PLATFORM) // PIO has issues, needs MQTT.h definition or else freaks out
#include <MQTT.h>
#endif
PubSubClient client(net);
#else
#include <MQTT.h>
MQTTClient client;
#endif
int asd = 0;
unsigned long lastMillis = 0;
time_t now;
time_t nowish = 1510592825;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void configModeCallback (WiFiManager *myWiFiManager) {
      Serial.println("Entered config mode");
      Serial.println(WiFi.softAPIP());
      Serial.println(myWiFiManager->getConfigPortalSSID());
  }


void NTPConnect(void)
  {
      Serial.print("Setting time using SNTP");
      configTime(TIME_ZONE * 3600, DST * 3600, "pool.ntp.org", "time.nist.gov");
      now = time(nullptr);
      while (now < nowish)
      {
        delay(500);
        Serial.print(".");
        now = time(nullptr);
      }
      Serial.println("done!");
      struct tm timeinfo;
      gmtime_r(&now, &timeinfo);
      Serial.print("Current time: ");
      Serial.print(asctime(&timeinfo));
  }

#ifdef USE_PUB_SUB

//void messageReceivedPubSub(char *topic, byte *payload, unsigned int length)
//{
//  Serial.print("Received [");
//
//  Serial.print("]: ");
//  for (int i = 0; i < length; i++)
//  {
//    Serial.println((char)payload[i]);   
//  }
//Serial.println("---");
//}



void pubSubErr(int8_t MQTTErr)
  {
    if (MQTTErr == MQTT_CONNECTION_TIMEOUT)
      Serial.print("Connection tiemout");
    else if (MQTTErr == MQTT_CONNECTION_LOST)
      Serial.print("Connection lost");
    else if (MQTTErr == MQTT_CONNECT_FAILED)
      Serial.print("Connect failed");
    else if (MQTTErr == MQTT_DISCONNECTED)
      Serial.print("Disconnected");
    else if (MQTTErr == MQTT_CONNECTED)
      Serial.print("Connected");
    else if (MQTTErr == MQTT_CONNECT_BAD_PROTOCOL)
      Serial.print("Connect bad protocol");
    else if (MQTTErr == MQTT_CONNECT_BAD_CLIENT_ID)
      Serial.print("Connect bad Client-ID");
    else if (MQTTErr == MQTT_CONNECT_UNAVAILABLE)
      Serial.print("Connect unavailable");
    else if (MQTTErr == MQTT_CONNECT_BAD_CREDENTIALS)
      Serial.print("Connect bad credentials");
    else if (MQTTErr == MQTT_CONNECT_UNAUTHORIZED)
      Serial.print("Connect unauthorized");
  }
#else

//////////////////////////// Sent data to AWS /////////////////////

void sendData(void)
  {
      DynamicJsonDocument jsonBuffer(JSON_OBJECT_SIZE(1) + 100);
      JsonObject root = jsonBuffer.to<JsonObject>();
      JsonObject state = root.createNestedObject("state");
      JsonObject state_desired = state.createNestedObject("desired");
//      JsonObject state_reported = state.createNestedObject("reported");     

         
      state_desired["dust"]  = dust;
      state_desired["power"] = Power;
      state_desired["speed"] = Speed;
      state_desired["timer"] = timer;
      state_desired["auto"]  = Auto;
      
    
//      Serial.print("Sending  : ");
//      serializeJson(root,Serial);//send command      Serial.println(root);   
//      Serial.print("\n");
 
      char shadow[measureJson(root) + 1];
      serializeJson(root, shadow, sizeof(shadow));//send command
        
    #ifdef USE_PUB_SUB
      if (!client.publish(MQTT_PUB_TOPIC, shadow, false))
        pubSubErr(client.state());
    #else
      if (!client.publish(MQTT_PUB_TOPIC, shadow, false, 0))
        lwMQTTErr(client.lastError());
    #endif   
  }
  
void send_button_state(void)
  {
      DynamicJsonDocument jsonBuffer(JSON_OBJECT_SIZE(1) + 100);
      JsonObject root = jsonBuffer.to<JsonObject>();
      JsonObject state = root.createNestedObject("state");
      JsonObject state_reported = state.createNestedObject("reported");     

    
      state_reported["Bpower"] = buttonP;
      state_reported["Bspeed"] = buttonS;
      state_reported["Btimer"] = buttonT;
      state_reported["Bauto"]  = buttonA;
      

      char shadows[measureJson(root) + 1];
      serializeJson(root, shadows, sizeof(shadows));//send command
        
    #ifdef USE_PUB_SUB
      if (!client.publish(MQTT_PUB_TOPIC, shadows, false))
        pubSubErr(client.state());
    #else
      if (!client.publish(MQTT_PUB_TOPIC, shadows, false, 0))
        lwMQTTErr(client.lastError());
    #endif   


  }


//////////////////// Receive data from AWS ///////////////////////



String datasent;

byte Bpower = 0;
byte Bspeed = 0;
byte Btimer = 0;
byte Bauto = 0;


void messageReceived(String &topic, String &payload)
  {
//      Serial.println("Recieved : " + payload);
//      Serial.println("\n");
    
       StaticJsonDocument<200> jsonBuffer;
    
       deserializeJson(jsonBuffer, payload);
    
      // Get the root object in the document
      JsonObject root = jsonBuffer.as<JsonObject>();
    
   
      Rpower = root ["state"]["desired"]["power"];
      Rspeed = root ["state"]["desired"]["speed"];
      Rtimer = root ["state"]["desired"]["timer"];
      Rauto = root ["state"]["desired"]["auto"];
      
      Bpower = root ["state"]["reported"]["Bpower"];
      Bspeed = root ["state"]["reported"]["Bspeed"];
      Btimer = root ["state"]["reported"]["Btimer"];
      Bauto = root ["state"]["reported"]["Bauto"];

//       Print values.
//      Serial.print("Power = "); Serial.println(Rpower);
//      Serial.print("Speed = "); Serial.println(Rspeed);
//      Serial.print("timer = "); Serial.println(Rtimer);
//      Serial.print("Auto  = "); Serial.println(Rauto);



  }




void lwMQTTErr(lwmqtt_err_t reason)
  {
      if (reason == lwmqtt_err_t::LWMQTT_SUCCESS)
        Serial.print("Success");
      else if (reason == lwmqtt_err_t::LWMQTT_BUFFER_TOO_SHORT)
        Serial.print("Buffer too short");
      else if (reason == lwmqtt_err_t::LWMQTT_VARNUM_OVERFLOW)
        Serial.print("Varnum overflow");
      else if (reason == lwmqtt_err_t::LWMQTT_NETWORK_FAILED_CONNECT)
        Serial.print("Network failed connect");
      else if (reason == lwmqtt_err_t::LWMQTT_NETWORK_TIMEOUT)
        Serial.print("Network timeout");
      else if (reason == lwmqtt_err_t::LWMQTT_NETWORK_FAILED_READ)
        Serial.print("Network failed read");
      else if (reason == lwmqtt_err_t::LWMQTT_NETWORK_FAILED_WRITE)
        Serial.print("Network failed write");
      else if (reason == lwmqtt_err_t::LWMQTT_REMAINING_LENGTH_OVERFLOW)
        Serial.print("Remaining length overflow");
      else if (reason == lwmqtt_err_t::LWMQTT_REMAINING_LENGTH_MISMATCH)
        Serial.print("Remaining length mismatch");
      else if (reason == lwmqtt_err_t::LWMQTT_MISSING_OR_WRONG_PACKET)
        Serial.print("Missing or wrong packet");
      else if (reason == lwmqtt_err_t::LWMQTT_CONNECTION_DENIED)
        Serial.print("Connection denied");
      else if (reason == lwmqtt_err_t::LWMQTT_FAILED_SUBSCRIPTION)
        Serial.print("Failed subscription");
      else if (reason == lwmqtt_err_t::LWMQTT_SUBACK_ARRAY_OVERFLOW)
        Serial.print("Suback array overflow");
      else if (reason == lwmqtt_err_t::LWMQTT_PONG_TIMEOUT)
        Serial.print("Pong timeout");
  }



void lwMQTTErrConnection(lwmqtt_return_code_t reason)
  {
      if (reason == lwmqtt_return_code_t::LWMQTT_CONNECTION_ACCEPTED)
        Serial.print("Connection Accepted");
      else if (reason == lwmqtt_return_code_t::LWMQTT_UNACCEPTABLE_PROTOCOL)
        Serial.print("Unacceptable Protocol");
      else if (reason == lwmqtt_return_code_t::LWMQTT_IDENTIFIER_REJECTED)
        Serial.print("Identifier Rejected");
      else if (reason == lwmqtt_return_code_t::LWMQTT_SERVER_UNAVAILABLE)
        Serial.print("Server Unavailable");
      else if (reason == lwmqtt_return_code_t::LWMQTT_BAD_USERNAME_OR_PASSWORD)
        Serial.print("Bad UserName/Password");
      else if (reason == lwmqtt_return_code_t::LWMQTT_NOT_AUTHORIZED)
        Serial.print("Not Authorized");
      else if (reason == lwmqtt_return_code_t::LWMQTT_UNKNOWN_RETURN_CODE)
        Serial.print("Unknown Return Code");
  }
#endif



void connectToMqtt(bool nonBlocking = false)
    {
      Serial.print("MQTT connecting ");
      while (!client.connected())
      {
        if (client.connect(THINGNAME))
        {
          Serial.println("connected!");
          if (!client.subscribe(MQTT_SUB_TOPIC))
    #ifdef USE_PUB_SUB
            pubSubErr(client.state());
    #else
            lwMQTTErr(client.lastError());
    #endif
        }
        else
        {
          Serial.print("failed, reason -> ");
    #ifdef USE_PUB_SUB
          pubSubErr(client.state());
    #else
          lwMQTTErrConnection(client.returnCode());
    #endif
          if (!nonBlocking)
          {
            Serial.println(" < try again in 5 seconds");
            delay(5000);
          }
          else
          {
            Serial.println(" <");
          }
        }
        if (nonBlocking)
          break;
      }
  }



void connectToWiFi(String init_str)
    {
      if (init_str != emptyString)
        Serial.print(init_str);
      while (WiFi.status() != WL_CONNECTED)
      {
        Serial.print(".");
        delay(1000);
      }
      if (init_str != emptyString)
        Serial.println("ok!");
  }



void checkWiFiThenMQTT(void)
  {
      connectToWiFi("Checking WiFi");
      connectToMqtt();
  }

unsigned long previousMillis = 0;
const long interval = 5000;

void checkWiFiThenMQTTNonBlocking(void)
  {
      connectToWiFi(emptyString);
      if (millis() - previousMillis >= interval && !client.connected()) {
        previousMillis = millis();
        connectToMqtt(true);
      }
  }



void checkWiFiThenReboot(void)
  {
      connectToWiFi("Checking WiFi");
      Serial.print("Rebooting");
      ESP.restart();
  }




void setup()
    {
      Serial.begin(115200);
    
    #ifdef ESP32
      WiFi.setHostname(THINGNAME);
    #else
      WiFi.hostname(THINGNAME);
    #endif
    
      WiFiManager wifiManager;  
      wifiManager.setAPCallback(configModeCallback);
      wifiManager.setConfigPortalTimeout(180);
      wifiManager.autoConnect("Air Purifier");
    
      Blynk.config(auth);
      
      dht.begin();
      
    
      NTPConnect();
    
    #ifdef ESP32
      net.setCACert(cacert);
      net.setCertificate(client_cert);
      net.setPrivateKey(privkey);
    #else
      net.setTrustAnchors(&cert);
      net.setClientRSACert(&client_crt, &key);
    #endif
    
    #ifdef USE_PUB_SUB
      client.setServer(MQTT_HOST, MQTT_PORT);
      client.setCallback(messageReceivedPubSub);
    #else
      client.begin(MQTT_HOST, MQTT_PORT, net);
      client.onMessage(messageReceived);
    #endif
      connectToMqtt();

      pinMode(D2,OUTPUT);
      pinMode(D3,INPUT);

      
  NanoSerial.begin(57600);
}





void loop()
{
  current_time=millis();
  
    Blynk.run();

    now = time(nullptr);

    receive_bord();

    button_key();

    senddata();
    
    wifi();

    Sensor_DHT();
    
    if (!client.connected())
       {
        checkWiFiThenMQTT();
       }
       else
       {
        client.loop();
       }
}
