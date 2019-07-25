
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial NodeSerial(2,3); // RX | TX


float lastsent=0;
float lastread=0;

    bool Auto=0;
    bool plasma=0;
    bool speed1=0;
    bool speed2=0;
    bool speed3=0;
    bool speed4=0;

void setup() {

  pinMode(2, INPUT); 
  pinMode(3,OUTPUT);

  Serial.begin(9600);

  NodeSerial.begin(57600);

 }

void send_smart(){
  NodeSerial.print("<");
  NodeSerial.print(Auto);          NodeSerial.print("  ");
  NodeSerial.print(plasma);        NodeSerial.print("  ");
  NodeSerial.print(speed1);        NodeSerial.print("  ");
  NodeSerial.print(speed2);        NodeSerial.print("  ");
  NodeSerial.print(speed3);        NodeSerial.print("  ");
  NodeSerial.print(speed4);        NodeSerial.print("\n");

}

char datar ;
String dataj;

void loop() {
    float current_time=millis();

   
  if(NodeSerial.available()>0){
        
    datar = NodeSerial.read(); 
    dataj += datar;
   StaticJsonDocument<200> jsonBuffer;
    
      DeserializationError error =  deserializeJson(jsonBuffer, dataj); 
    if (datar=='\n'){
 Serial.println(dataj);

    
   

    

      // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    NodeSerial.print("failed");
    dataj = datar;
    return;
  }
    
      // Get the root object in the document
      JsonObject root = jsonBuffer.as<JsonObject>();
    
   
      String Power = root ["state"]["desired"]["power"];
      String Speed = root ["state"]["desired"]["speed"];
      String Timer = root ["state"]["desired"]["timer"];
      String Auto = root ["state"]["desired"]["auto"];
      
    
    if(Power||Speed||Timer||Auto==0){
      
      Serial.println("failed");
      }else{
        Serial.print("Power = "); Serial.println(Power);
      Serial.print("Speed = "); Serial.println(Speed);
      Serial.print("timer = "); Serial.println(Timer);
      Serial.print("Auto  = "); Serial.println(Auto);}
      // Print values.
      
    
dataj = datar;
       }
//    if (current_time-lastsent>1000){
//    Serial.println(datar);
//      lastsent=current_time;
    }

} 
