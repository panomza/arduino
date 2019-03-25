
#include <SoftwareSerial.h>

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
  NodeSerial.print(Auto);          NodeSerial.print("  ");
  NodeSerial.print(plasma);        NodeSerial.print("  ");
  NodeSerial.print(speed1);        NodeSerial.print("  ");
  NodeSerial.print(speed2);        NodeSerial.print("  ");
  NodeSerial.print(speed3);        NodeSerial.print("  ");
  NodeSerial.print(speed4);        NodeSerial.print("\n");

}

void loop() {
    float current_time=millis();

     
    if (NodeSerial.read()=='<'&& current_time-lastread>1000) {
          Auto       = NodeSerial.parseInt(); 
          plasma     = NodeSerial.parseInt();
          speed1     = NodeSerial.parseInt();
          speed2     = NodeSerial.parseInt();
          speed3     = NodeSerial.parseInt();
          speed4     = NodeSerial.parseInt();
          Serial.print("speed1");      Serial.print(" : "); Serial.print(speed1);
          Serial.print("\tspeed2");      Serial.print(" : "); Serial.print(speed2);
          Serial.print("\tspeed3");      Serial.print(" : "); Serial.print(speed3);
          Serial.print("\tspeed4");      Serial.print(" : "); Serial.print(speed4);
          Serial.print("\tplasma");    Serial.print(" : "); Serial.print(plasma);
          Serial.print("\tAuto");      Serial.print(" : "); Serial.println(Auto); 
          lastread=current_time;
          
    }
    if (current_time-lastsent>1000){
      send_smart();
      lastsent=current_time;
    }

} 
