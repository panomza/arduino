int i_data = 1234;
int plasma = 14;
float f_data = 567.89;

#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

SoftwareSerial NanoSerial(D3, D2); // RX | TX

void setup()

{  

  pinMode(D3,INPUT);

  pinMode(D2,OUTPUT);

  Serial.begin(9600);

  NanoSerial.begin(57600);           

}

void loop() {

  Serial.print(i_data); Serial.print("\t");

  Serial.println(f_data);
  

 // NanoSerial.print(i_data); NanoSerial.print(" ");
  NanoSerial.print(plasma); NanoSerial.print(" ");

  //NanoSerial.print(f_data); NanoSerial.print("\n");

  delay(100);

}
