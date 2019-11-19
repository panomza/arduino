
#include <FS.h>
#define BLYNK_PRINT Serial
#include <Ethernet.h>
#include <BlynkSimpleEsp8266.h>

//////////////////// wifimanager
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include <ArduinoJson.h>

char blynk_token[40]="";
char Bord_Set[32] = "";
bool shouldSaveConfig = false;
String Bord ;

bool button1 = 0;
bool button2 = 0;
bool button3 = 0;
bool button4 = 0;
bool button6 = 0;
bool button7 = 0;
bool button8 = 0;
bool button9 = 0;
unsigned int timecount = 0;

void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
}

void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

void setup()
{
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  digitalWrite(0,1);
  digitalWrite(1,1);
  digitalWrite(2,1);
  digitalWrite(3,1);
  
// Serial.begin(9600);
 
 SPIFFS.begin();

  Serial.println("mounting FS...");
  if (SPIFFS.begin()) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success()) {
          Serial.println("\nparsed json");
          strcpy(blynk_token, json["blynk_token"]);
          strcpy(Bord_Set, json["bord_set"]);

        } else {
          Serial.println("failed to load json config");
        }
        configFile.close();
      }
    }
  } else {
    Serial.println("failed to mount FS");
  }
  
  WiFiManagerParameter custom_blynk_token("blynk", "blynk token", blynk_token, 33);
  WiFiManagerParameter custom_Bord_set("bord", "Bord Set", Bord_Set, 33);
  
  WiFiManager wifiManager;  
  wifiManager.setSaveConfigCallback(saveConfigCallback); 
  
  wifiManager.addParameter(&custom_blynk_token);
  wifiManager.addParameter(&custom_Bord_set);
  wifiManager.setTimeout(60); 

  if (!wifiManager.autoConnect("Smart Relay")) {
    
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    ESP.reset();
    delay(5000);
  }

  Serial.println("wifi connected");
  
  strcpy(blynk_token, custom_blynk_token.getValue());
  strcpy(Bord_Set, custom_Bord_set.getValue());
  Bord = Bord_Set;

  //save the custom parameters to FS
  if (shouldSaveConfig) {
    Serial.println("saving config");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["blynk_token"] = blynk_token;
    json["bord_set"] = Bord_Set;

    File configFile = SPIFFS.open("/config.json", "w");
    
    if (!configFile) {
      Serial.println("failed to open config file for writing");
    }
    json.printTo(Serial);
    json.printTo(configFile);
    configFile.close();
  }else{Serial.println("failed");}
    
  Blynk.config(blynk_token); 
}


void loop()
{
  
  Blynk.run();

  if (millis() - timecount > 5000){
      timecount = millis();
      
   if( Bord == "master"){
      Blynk.virtualWrite(V1,button1);
      Blynk.virtualWrite(V2,button2);
      Blynk.virtualWrite(V3,button3);
      Blynk.virtualWrite(V4,button4);
      }
   if( Bord == "slave"){
      Blynk.virtualWrite(V6,button6);
      Blynk.virtualWrite(V7,button7);
      Blynk.virtualWrite(V8,button8);
      Blynk.virtualWrite(V9,button9);
      }
   
      Serial.print("ch1 : ");
      Serial.println(button1);
      Serial.print("ch2 : ");
      Serial.println(button2);
      Serial.print("ch3 : ");
      Serial.println(button3);
      Serial.print("ch4 : ");
      Serial.println(button4);
      Serial.print("ch6 : ");
      Serial.println(button6);
      Serial.print("ch7 : ");
      Serial.println(button7);
      Serial.print("ch8 : ");
      Serial.println(button8);
      Serial.print("ch9 : ");
      Serial.println(button9);
    }

}
