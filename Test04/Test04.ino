
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

  int select_timer=0;
  int select_speed=0;
  int on_off = 0;
  float lastread=0;
  int Lpm = 0;
  int statePM=0;
  int La= 0;
  int stateA=0;
  
#include <SoftwareSerial.h>
SoftwareSerial NanoSerial(D3, D2); // RX | TX

//wifi variables
//const char auth[] = "a7a249ec5f2c41edabf98479ba690559";
const char auth[] = "d7c89935fa6449caabdb6753b6d80b11";
const char ssid[] = "HTR-MK";
const char pass[] = "hatariled1";


bool plasma = 0;
bool Auto   = 0;
bool offbutton = 0;
bool speed1=0;
bool speed2=0;
bool speed3=0;
bool speed4=0;
float lastSpeed=0;


void turnoff() // turn off all speed
{
  Blynk.virtualWrite(V0, 0);
  Blynk.virtualWrite(V1, 0);
  Blynk.virtualWrite(V2, 0);
  Blynk.virtualWrite(V3, 0);
  Blynk.virtualWrite(V4, 0);
  Blynk.virtualWrite(V5, 0);
  Blynk.virtualWrite(V6, 0);
  
  offbutton = 0;
  plasma    = 0;
  Auto      = 0;
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


/// send to stupid board

void send_stupid(){
  NanoSerial.print("<");
  NanoSerial.print(Auto);          NanoSerial.print("  ");
  NanoSerial.print(plasma);        NanoSerial.print("  ");
  NanoSerial.print(speed1);        NanoSerial.print("  ");
  NanoSerial.print(speed2);        NanoSerial.print("  ");
  NanoSerial.print(speed3);        NanoSerial.print("  ");
  NanoSerial.print(speed4);        NanoSerial.print(">");

}




// Blynk read and write functions
// user push speed buttons

BLYNK_WRITE(V0) // ON-OFF
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
      speed1=1;
        break;
        
      case 2:
      Serial.println("OFF is pressed");
      turnoff();
      on_off=0;
      select_speed=0;
      select_timer=0;
        break;
    }
  }
  send_stupid();
}

BLYNK_WRITE(V1) // Speed
{
  int pinValue = param.asInt(); 
  if (pinValue==1 && on_off==1&& millis()-lastSpeed>50){
    select_speed++;
  
    switch (select_speed){
      case 1:
      clearspeed();
      Serial.println("speed 1 ");
      Blynk.virtualWrite(V5,1);
      speed1=1;
        break;
      case 2:
      clearspeed();
      Serial.println("speed 2 ");
      Blynk.virtualWrite(V5,2);
      speed2=1;
        break;
      case 3:
      clearspeed();
      Serial.println("speed 3 ");
      Blynk.virtualWrite(V5,3);
      speed3=1;
        break;
      case 4:
      clearspeed();
      Serial.println("speed 4 ");
      Blynk.virtualWrite(V5,4);
      speed4=1;
        break;
      case 5:
      clearspeed();
      select_speed=1;
      speed1=1;
      Blynk.virtualWrite(V5,1);
        break;
    }
  }
    send_stupid();
}



BLYNK_WRITE(V2) //Plasma
{


  int pinValue = param.asInt();
  
  if ((pinValue != Lpm) && pinValue == 1 && on_off==1)
  {
    statePM=!statePM;
    pinValue = Lpm;
    Serial.println("Plasma ON");
    Blynk.virtualWrite(V2,statePM);
    Serial.println(statePM);
    plasma =statePM;
  }
  else { 
    Lpm=pinValue;
    
  }
  send_stupid();
}

BLYNK_WRITE(V3) // Timer
{
  int pinValue = param.asInt(); 
  if (pinValue==1 && on_off==1){
    select_timer++;
  }
    switch (select_timer){
      case 1:
      Serial.println("Timer 1 ");
      Blynk.virtualWrite(V6,1);
        break;
      case 2:
      Serial.println("Timer 2 ");
      Blynk.virtualWrite(V6,2);
        break;
      case 3:
      Serial.println("Timer 3 ");
      Blynk.virtualWrite(V6,3);
        break;
      case 4:
      Serial.println("Timer 4 ");
      Blynk.virtualWrite(V6,4);
        break;
      case 5:
      select_timer=0;
      Blynk.virtualWrite(V6,0);
        break;
    }
    send_stupid();
}

BLYNK_WRITE(V4) //Auto
{


  int pinValue = param.asInt();
  
  if ((pinValue != La) && pinValue == 1 && on_off==1)
  {
    stateA=!stateA;
    pinValue = La;
    Serial.println("AutoON");
    Blynk.virtualWrite(V4,stateA);
    Serial.println(stateA);
    Auto = stateA;
    
  }
  else { 
    La=pinValue;   
  }
  send_stupid();

}



void readReturnSignal(float current_time){
   if (NanoSerial.read()=='<') {
          Auto       = NanoSerial.parseInt(); 
          plasma     = NanoSerial.parseInt();
          speed1     = NanoSerial.parseInt();
          speed2     = NanoSerial.parseInt();
          speed3     = NanoSerial.parseInt();
          speed4     = NanoSerial.parseInt();
          Serial.print("speed1");      Serial.print(" : "); Serial.print(speed1);
          Serial.print("\tspeed2");      Serial.print(" : "); Serial.print(speed2);
          Serial.print("\tspeed3");      Serial.print(" : "); Serial.print(speed3);
          Serial.print("\tspeed4");      Serial.print(" : "); Serial.print(speed4);
          Serial.print("\tplasma");    Serial.print(" : "); Serial.print(plasma);
          Serial.print("\tAuto");      Serial.print(" : "); Serial.println(Auto); 
          lastread=current_time;
          
    }
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

/////////////////////////////////Sent data////////////////////////////////////
  pinMode(D3,INPUT);
  pinMode(D2,OUTPUT);


  NanoSerial.begin(57600);           
}


void loop()
{
  Blynk.run();
  float current_time=millis();
  readReturnSignal(current_time);

}
