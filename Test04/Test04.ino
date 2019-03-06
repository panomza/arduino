
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//////////////////////////Sent data\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#include <SoftwareSerial.h>
SoftwareSerial NanoSerial(D3, D2); // RX | TX

//wifi variables
//const char auth[] = "a7a249ec5f2c41edabf98479ba690559";
const char auth[] = "45a91916638847d59d36bcd1a09480f5";
const char ssid[] = "HATARILED Wi-Fi";
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
BLYNK_WRITE(V0) // number 1
{
  int pinValue = param.asInt(); 
  if (pinValue==1){
    clearspeed();
    Serial.println("speed 1 is pressed");
    speed1=pinValue;
  Blynk.virtualWrite(V0, 1);
  Blynk.virtualWrite(V1, 0);
  Blynk.virtualWrite(V2, 0);
  Blynk.virtualWrite(V3, 0);
  }
    else { speed1=0;}
}
BLYNK_WRITE(V1) // number 2
{
  int pinValue = param.asInt(); 
  if (pinValue==1){
    clearspeed();
    Serial.println("speed 2 is pressed");
    speed2=pinValue;
  Blynk.virtualWrite(V0, 0);
  Blynk.virtualWrite(V1, 1);
  Blynk.virtualWrite(V2, 0);
  Blynk.virtualWrite(V3, 0);
  }
    else { speed2=0;}
}
BLYNK_WRITE(V2) // number 3
{
  int pinValue = param.asInt(); 
  if (pinValue==1){
    clearspeed();
    Serial.println("speed 3 is pressed");
    speed3=pinValue;
  Blynk.virtualWrite(V0, 0);
  Blynk.virtualWrite(V1, 0);
  Blynk.virtualWrite(V2, 1);
  Blynk.virtualWrite(V3, 0);
  }
    else { speed3=0;}
}
BLYNK_WRITE(V3) // number 4
{
  int pinValue = param.asInt(); 
  if (pinValue==1){
    clearspeed();
    Serial.println("speed 4 is pressed");
    speed4=pinValue;
  Blynk.virtualWrite(V0, 0);
  Blynk.virtualWrite(V1, 0);
  Blynk.virtualWrite(V2, 0);
  Blynk.virtualWrite(V3, 1);
  }
    else { speed4=0;}
}
BLYNK_WRITE(V4) // off
{
  int pinValue = param.asInt(); 
  if (pinValue==1){
    Serial.println("off is pressed");
    turnoff();
  }
}

BLYNK_WRITE(V9) // plasma
{
  int pinValue = param.asInt();
  if (pinValue==1){
    Serial.println("plasma is pressed");
    plasma=pinValue;
  } 
  else { plasma=0;}
}

BLYNK_WRITE(V5) // auto button
{
  int pinValue = param.asInt(); 
  if (pinValue==1){
    Serial.println("auto is pressed");
    autobutton=pinValue;
  }
  else{autobutton = 0 ; }
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
  NanoSerial.begin(57600);           
}


void loop()
{
  Blynk.run();
  
  NanoSerial.print(autobutton);     NanoSerial.print(" ");
  NanoSerial.print(plasma);         NanoSerial.print(" ");
  NanoSerial.print(speed1);         NanoSerial.print(" ");
  NanoSerial.print(speed2);         NanoSerial.print(" ");
  NanoSerial.print(speed3);         NanoSerial.print(" ");
  NanoSerial.print(speed4);         NanoSerial.print("\n");

delay(100);
}
