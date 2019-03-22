
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
  int select_speed=0;
  int on_off = 0;
//////////////////////////Sent data\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#include <SoftwareSerial.h>
SoftwareSerial NodeSerial(D3, D2); // RX | TX

//wifi variables
//const char auth[] = "a7a249ec5f2c41edabf98479ba690559";
const char auth[] = "d7c89935fa6449caabdb6753b6d80b11";
const char ssid[] = "HTR-MK";
const char pass[] = "hatariled1";


bool plasma = 0;
bool autobutton = 0;
bool offbutton = 0;
bool speed1=0;
bool speed2=0;
bool speed3=0;
bool speed4=0;


void turnoff() // turn off all speed
{
  Blynk.virtualWrite(V0, 0);
  Blynk.virtualWrite(V1, 0);
  Blynk.virtualWrite(V2, 0);
  Blynk.virtualWrite(V3, 0);
  Blynk.virtualWrite(V4, 0);
  Blynk.virtualWrite(V5, 0);
  Blynk.virtualWrite(V9, 0);
  
  offbutton = 0;
  plasma    = 0;
  autobutton= 0;
  speed1    = 0;
  speed2    = 0;
  speed3    = 0;
  speed4    = 0;
}

void clearspeed()
{
  speed1    = 0;
  speed2    = 0;
  speed3    = 0;
  speed4    = 0;
}


// Blynk read and write functions
// user push speed buttons

BLYNK_WRITE(V1) // number 1
{
  int pinValue = param.asInt(); 
  if (pinValue==1 && on_off==1){
    select_speed++;
  }
    switch (select_speed){
      case 1:
      Serial.println("speed 1 ");
      Blynk.virtualWrite(V5,1);
        break;
      case 2:
      Serial.println("speed 2 ");
      Blynk.virtualWrite(V5,2);
        break;
      case 3:
      Serial.println("speed 3 ");
      Blynk.virtualWrite(V5,3);
        break;
      case 4:
      Serial.println("speed 4 ");
      Blynk.virtualWrite(V5,4);
        break;
      case 5:
      select_speed=1;
      Blynk.virtualWrite(V5,1);
        break;
    }
}

BLYNK_WRITE(V0) // ON
{
  int pinValue = param.asInt(); 


  if (pinValue==1){

    on_off++;

    switch(on_off){
      case 1:
      Blynk.virtualWrite(V0, 1);
      Serial.println("ON is pressed");
      Blynk.virtualWrite(V5, 1);
      select_speed=1;
        break;
        
      case 2:
      Blynk.virtualWrite(V0, 0);
      Serial.println("OFF is pressed");
      Blynk.virtualWrite(V1, 0);
      Blynk.virtualWrite(V5, 0);
      on_off=0;
        break;
    }
  }
}



void setup()
{
  // Debug console
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

/////////////////////////////////Sent data\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  pinMode(D3,INPUT);
  pinMode(D2,OUTPUT);

  Serial.begin(9600);
  NodeSerial.begin(57600);           
}


void loop()
{
   // Serial.println(select_speed); 
  Blynk.run();

  NodeSerial.print(autobutton);     NodeSerial.print(" ");
  NodeSerial.print(plasma);         NodeSerial.print(" ");
  NodeSerial.print(speed1);        NodeSerial.print(" ");
  NodeSerial.print(speed2);        NodeSerial.print(" ");
  NodeSerial.print(speed3);         NodeSerial.print(" ");
  NodeSerial.print(speed4);         NodeSerial.print("\n");


delay(100);
}
