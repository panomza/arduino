
#include <SoftwareSerial.h>
bool countplasmad=0;
SoftwareSerial NodeSerial(1,0); // RX | TX

void setup() {

  pinMode(1, INPUT); 
  pinMode(6,OUTPUT);
  pinMode(0, OUTPUT); 

  //Serial.begin(9600);

  NodeSerial.begin(57600);

 }

void loop() {
 
    bool autobutton = NodeSerial.parseInt(); 
    bool plasma     = NodeSerial.parseInt();
    bool speed1     = NodeSerial.parseInt();
    bool speed2     = NodeSerial.parseInt();
    bool speed3     = NodeSerial.parseInt();
    bool speed4     = NodeSerial.parseInt();
     
    if (NodeSerial.read() == '\n') {
          Serial.print("speed1");      Serial.print(" : "); Serial.print(speed1);
          Serial.print("\tspeed2");      Serial.print(" : "); Serial.print(speed2);
          Serial.print("\tspeed3");      Serial.print(" : "); Serial.print(speed3);
          Serial.print("\tspeed4");      Serial.print(" : "); Serial.print(speed4);
          Serial.print("\tplasma");    Serial.print(" : "); Serial.print(plasma);
          Serial.print("\tauto");      Serial.print(" : "); Serial.println(autobutton); 
          
    }
    if((plasma==1)){
    digitalWrite(13,1);
 
  }
  else {
    
    digitalWrite(13,0);

  }

} 
