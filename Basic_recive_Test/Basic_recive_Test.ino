
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial NodeSerial(12,11); // RX | TX

unsigned int  current_time;


byte check=0;
unsigned int de=0;
unsigned int desent=0;

int Bpower =0;
int Bspeed =0;
int Btimer =0;
int Bauto =0;

void setup() {

  pinMode(12, INPUT); 
  pinMode(11,OUTPUT);

  Serial.begin(115200);

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

char datar ;
String dataj;
void recive_data_ESP()
{
  if(NodeSerial.available()>0){
        
    datar = NodeSerial.read(); 
    dataj += datar;
    
    StaticJsonDocument<100> jsonBuffer;
    deserializeJson(jsonBuffer, dataj); 
    Serial.println(dataj);
    if (datar=='\n'){
            // Test if parsing succeeds.
      
      // Get the root object in the document
      JsonObject root = jsonBuffer.as<JsonObject>();
    Serial.println(dataj);
   
      String Power = root ["power"];
      String Speed = root ["speed"];
      String Timer = root ["timer"];
      String Auto = root ["auto"];

      Bpower = root ["power"];
      Bspeed = root ["speed"];
      Btimer = root ["timer"];
      Bauto = root ["auto"];

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
//
//void sent_data_esp()
//{
//   if(current_time-desent>1000){
//      DynamicJsonDocument jsonBuffer(JSON_OBJECT_SIZE(3) + 100);
//      JsonObject root = jsonBuffer.to<JsonObject>();
//      JsonObject state = root.createNestedObject("state");
//      JsonObject state_desired = state.createNestedObject("desired");
//    
//    
//      state_desired["power" ] = Bpower;
//      state_desired["speed"] = Bspeed;
//      state_desired["timer"] = Btimer;
//      state_desired["auto"] = Bauto;
//
//      char status_bord[measureJson(root) + 1];
//      serializeJson(root, status_bord, sizeof(status_bord));
//      
//      NodeSerial.print(status_bord);
//      NodeSerial.print("\n");
//
//      desent=current_time;
//   }
//}

 
void loop() {
  
  current_time=millis();
  
  recive_data_ESP();

//  sent_data_esp();
  
//  fail_check();

} 
