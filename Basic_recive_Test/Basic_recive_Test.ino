
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial NodeSerial(2,3); // RX | TX

unsigned int  current_time;
char datar ;
String dataj;

byte check=0;
unsigned int de=0;
unsigned int desent=0;

int Bpower =0;
int Bspeed =0;
int Btimer =0;
int Bauto =0;

void setup() {

  pinMode(2, INPUT); 
  pinMode(3,OUTPUT);

  Serial.begin(9600);

  NodeSerial.begin(57600);

 }

void send_smart(){


}



void fail_check()
{
    if(current_time-de>500&&check==1)
    {    
      DynamicJsonDocument jsonBuffer(JSON_OBJECT_SIZE(3) + 100);
      JsonObject root = jsonBuffer.to<JsonObject>();

      root["failed"] = check;

      char fail[measureJson(root) + 1];
      serializeJson(root, fail, sizeof(fail));

      Serial.println("failed");
      Serial.println();
      NodeSerial.print(fail);
      NodeSerial.print("\n");

      de=current_time;
  }
}

void recive_data_ESP()
{
  if(NodeSerial.available()>0){
        
    datar = NodeSerial.read(); 
    dataj += datar;
    
    StaticJsonDocument<400> jsonBuffer;
    DeserializationError error =  deserializeJson(jsonBuffer, dataj); 
    
    if (datar=='\n'){
            // Test if parsing succeeds.
        if (error) 
          {
           check=1;  
           dataj = datar;
         
          }else{check=0;}
    
      // Get the root object in the document
      JsonObject root = jsonBuffer.as<JsonObject>();
    
   
      String Power = root ["state"]["desired"]["power"];
      String Speed = root ["state"]["desired"]["speed"];
      String Timer = root ["state"]["desired"]["timer"];
      String Auto = root ["state"]["desired"]["auto"];

      Bpower = root ["state"]["desired"]["power"];
      Bspeed = root ["state"]["desired"]["speed"];
      Btimer = root ["state"]["desired"]["timer"];
      Bauto = root ["state"]["desired"]["auto"];

    if (Bpower ==0){Bspeed =0;Btimer=0;Bauto=0;}
    if(Power == "null" ||Speed =="null" || Timer =="null" ||Auto =="null")
      {
      check=1;     
      }
      else{
        check=0;control_status();
        
        }  
        dataj = datar;
       }
       
    }
}

void sent_data_esp()
{
   if(current_time-desent>1000){
      DynamicJsonDocument jsonBuffer(JSON_OBJECT_SIZE(3) + 100);
      JsonObject root = jsonBuffer.to<JsonObject>();
      JsonObject state = root.createNestedObject("state");
      JsonObject state_desired = state.createNestedObject("desired");
    
    
      state_desired["power" ] = Bpower;
      state_desired["speed"] = Bspeed;
      state_desired["timer"] = Btimer;
      state_desired["auto"] = Bauto;

      char status_bord[measureJson(root) + 1];
      serializeJson(root, status_bord, sizeof(status_bord));
      
      NodeSerial.print(status_bord);
      NodeSerial.print("\n");

      desent=current_time;
   }
}

 
void loop() {
  
  current_time=millis();
  
  recive_data_ESP();

  sent_data_esp();
  
  fail_check();

} 
