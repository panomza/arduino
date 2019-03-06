
#include <SoftwareSerial.h>

SoftwareSerial NodeSerial(2,3); // RX | TX

void setup() {

  pinMode(2, INPUT); 

  pinMode(3, OUTPUT); 

  Serial.begin(9600);

  NodeSerial.begin(57600);

 }

void loop() {

  while (NodeSerial.available() > 0) {
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
    if(plasma==1){digitalWrite(12,1);}
  else{digitalWrite(12,0);}
    if(speed2==1){digitalWrite(7,1);}
  else{digitalWrite(7,0);}
    if(speed3==1){digitalWrite(8,1);}
  else{digitalWrite(8,0);}
    if(speed4==1){digitalWrite(9,1);}
  else{digitalWrite(9,0);}
   if(autobutton==1){digitalWrite(11,1);}
  else{digitalWrite(11,0);}
  }

} 
