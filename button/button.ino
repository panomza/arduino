////////////////////////////////////////DATA////////////////////////////////////////////////
//recive data
#include <SoftwareSerial.h>
SoftwareSerial NodeSerial(1,0); // RX | TX
//////////////////////////////////////////Sensor/////////////////////////////////////////////////
///DHT Sensor/////
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

////////Dust Sensor//////////
int measurePin = A5;
int ledPower = 12;

unsigned int samplingTime = 280;
unsigned int deltaTime = 40;
unsigned int sleepTime = 9680;
const int numaverage = 50; ///number of values for taking average
float dust[numaverage];
unsigned int count=0;
float initialdust=20;
float t0;// time of last reading
float timer=500;// time between each reading

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

float readdust(){
  digitalWrite(ledPower,LOW);
  delayMicroseconds(samplingTime);
  voMeasured = analogRead(measurePin);
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH);
  delayMicroseconds(sleepTime);

  calcVoltage = voMeasured*(5.0/1024);
  dustDensity = (40*calcVoltage-10);
  if ( dustDensity < 0)
  {
    dustDensity = 0.00;
  }
  return dustDensity;
}

float takeaverage(float input[]){
  
  float sum=0;
  for(int i = 0; i < int(numaverage) ; i++){
    sum+=input[i];
    //Serial.println(i);
    //Serial.println(input[i]);
  }
  return sum/numaverage;
}

//////////////////////////////////////Capasitive Sent Control////////////////////////////////////
//set time variables
short int powert0; 
short int speedt0;
short int plasmat0;

/// pin definition

// input pins
const short int Bspeed = 15;    // speed input pin
const short int Bpow = 14;      //power button input pin
const short int Bplasma = 16;   // plasma button input pin


//output pins

const short int POW=13;         //power output pin
const short int PLASMA=6;       // plasma button output pin
const short int M1 =  7;        // motor output pin
const short int M2 =  8;        // motor output pin
const short int M3 =  9;        // motor output pin
const short int M4 =  10;       // motor output pin
const short int BUZ = 4;        // buzzer output pin


// state variables

//power
bool Bp=1;               //power button state
bool Lp=1;               //previous power button state 
bool stateP = 1;     //power output state
bool powercount=0;        // count if the power button is pushed

//plasma
bool Bpm=1;                  // plasma button state
bool Lpm=1;                  // previous plasma button state
bool statePM = 1;        // plasma output state
bool plasmacount=0;       // count if plasma has been pressed

//speed
bool Bs=1;                   // speed input state
bool Ls=1;                   // previous speed input state
bool stateS = 0;         // speed state
unsigned short int index = 1;                // case counter

//delays
short int buttondelay=300;// delay between each button press in ms

/////////////////////////////////////////Remote//////////////////////////////////////////////

#include <IRremote.h>
  const int RECV_PIN = 3;
  IRrecv irrecv(RECV_PIN);
  decode_results results;
#define OUTPUT_COUNT 5

    unsigned long last = millis();
    long remote_key[]={0xDF40BF,0xDF609F,0xDF48B7,0xDF50AF,0xDF708F};
    const byte outputPins[OUTPUT_COUNT] = {0, 1, 2, 3,4};
    bool status1[5] = {0,0,0,0,0};
    struct keypad {
    boolean state;
};
keypad output[OUTPUT_COUNT];

///////////////////////////////////////Display///////////////////////////////////////////////
#include <Arduino.h>
#include <TM1637Display.h>
#define CLK 5
#define DIO 4
TM1637Display display(CLK, DIO);
unsigned short int timedisplay=1000;
unsigned short int TD=0;

void setup() {
///////////////////////////////////////DATA//////////////////////////////////////////////////
//recive data
  pinMode(1, INPUT); 
  pinMode(0, OUTPUT); 
  NodeSerial.begin(57600);
  
///////////////////////////////////////Capasitive Sent Control///////////////////////////////////
  int inputpins[3]={
    Bpow,Bspeed,Bplasma
    };

  int outputpins[7] = {
    POW,PLASMA,M1,M2,M3,M4,BUZ
  };

  for(int j=0;j< sizeof(inputpins)/sizeof(1);j++){
    pinMode(inputpins[j],INPUT);
    Serial.print(inputpins[j]);
    Serial.println(" is set as input");
  }
  for(int j=0;j< sizeof(outputpins)/sizeof(1);j++){
    pinMode(outputpins[j],OUTPUT);
    Serial.print(outputpins[j]);
    Serial.println(" is set as output");
    digitalWrite(outputpins[j],1);
  }
  ////set up the time
  speedt0=millis();
  powert0=millis();
  plasmat0=millis();

/////////////////////////////////////////Remote////////////////////////////////////////////////

  irrecv.enableIRIn(); // Start the receiver

//////////////////////////////////////////Sensor///////////////////////////////////////////////
   ////DHT Sensor////
   Serial.println("DHTxx test!");
   dht.begin();
   ////Dust Sensor//////
  pinMode(ledPower,OUTPUT);
  for(int i=0;i<numaverage;i++){
  dust[i]=initialdust;
  }
  t0=millis();
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
 
 /////////////////////////////////// assign power on and off//////////////////////////////////
void powerset(){
  if ((Bp != Lp) && (Bp == 0) && (millis()-powert0 > buttondelay) && (powercount==0)){
    stateP=!stateP;
    digitalWrite(POW,stateP);
    Serial.print("Power is set to: ");
    Serial.println(stateP); 
    applythespeedswitch(); // apply the switch for speed when turning on
    Lp=Bp;
    powert0 = millis();
    powercount = 1;
    if(stateP==1){clearspeed();
    digitalWrite(PLASMA,1);
    }
    // if(stateP==0){Melody();}
  } else if ((Bp != Lp) && (Bp == 1)&& (millis()-powert0 > buttondelay)){
    Lp=Bp;
    powercount = 0;
  }
}

//////////////////////////////////////// Button plasma///////////////////////////////////////
void plasmaset(){
    if ((Bpm != Lpm) && (stateP == 0) && (millis()-plasmat0 > buttondelay) && (plasmacount ==0)){
    statePM=!statePM;
    digitalWrite(PLASMA,statePM);
    Serial.print("Plasma is set to: ");
    Serial.println(statePM); 
    Lpm=Bpm;
    plasmat0 = millis();
    plasmacount =1;
    }
   else if ((Bpm != Lpm) && (Bpm == 1)&& (millis()-plasmat0 > buttondelay)){
    Lpm=Bpm;
    plasmacount = 0;
  }
}
/////////////////////////////////////speed clear///////////////////////////////////////
void clearspeed(){
      digitalWrite(M4,1);
      digitalWrite(M1,1);  
      digitalWrite(M2,1);
      digitalWrite(M3,1);
}

 //////////////////////////////////// set up the speed///////////////////////////////
void speedset(){

 if ((Bs != Ls) && (stateP==0) && (Bs == 0)&& (millis()-speedt0 > buttondelay)){  
     stateS=!stateS;
     index++;
     if(index>4){index=1;}
     Serial.print("Speed is set to: ");
     Serial.println(index);
     speedt0=millis(); // get the current time
     Ls=Bs;
     applythespeedswitch();
 }
 else if ((Bs != Ls) && (Bs == 1)&& (millis()-speedt0 > buttondelay)){
    Ls=Bs;
  }
  
}

void applythespeedswitch(){
    switch (index) {
    case 0:
      clearspeed();
      digitalWrite(PLASMA,1);
      break;
    case 1:
      clearspeed();
      digitalWrite(M1,LOW);   
     // Serial.println("M1");
      break;
    case 2:
      clearspeed();
      digitalWrite(M2,LOW);
     // Serial.println("M2");
      break;
    case 3:
      clearspeed();
      digitalWrite(M3,LOW);
     // Serial.println("M3");
      break;
    case 4:
      clearspeed();
      digitalWrite(M4,LOW);
     // Serial.println("M4");
      break;
  }
}


/////////////////////////////////////////Remote/////////////////////////////////////////////

void Remote(){
    unsigned long currentMillis = millis();
    if (irrecv.decode(&results)) {
         if (currentMillis - last > 50) {

           if ( (results.value != 0xFFFFFFFF) && (results.value != 0x00) ) {
              for (int val=0;val<OUTPUT_COUNT;val++) {       
                  if ( results.value == remote_key[val] )  {
                    Serial.println("remote button is pressed");
                    status1[val]=!status1[val];
                    switch (val) {
                      case 0: //on-off
                        Bp=0;
                        break;
                      case 1: // speed
                        Bs=0;
                        break;
                      case 2: // plasma
                        Bpm=0;
                        break;
                      case 3: // timer
                        break;
                      case 4: // ionizer
                        break;
                    }
                  }       
              }
           }

           for (int i=0;i<OUTPUT_COUNT;i++){
               //digitalWrite(outputPins[i], output[i].state);
//               digitalWrite(outputPins[i], status1[i]);  
           }

        last = currentMillis;      // record time
        irrecv.resume(); // Receive the next value

    }
    }
    if (millis()-last>300){
      for (int i=0;i<OUTPUT_COUNT;i++){
        if (status1[i]){
         status1[i]=0;
         Serial.println("switch back to normal");
         switch (i) {
                      case 0: //on-off
                        Bp=1;
                        break;
                      case 1: // speed
                        Bs=1;
                        break;
                      case 2: // plasma
                        Bpm=1;
                        break;
                      case 3: // timer
                        break;
                      case 4: // ionizer
                        break;
           }
        }
      }
    }
}
//////////////////////////////////////////Sensor///////////////////////////////////////////////
void sensor_DHT(){
   float h = dht.readHumidity();
   float t = dht.readTemperature();

   if (isnan(h) || isnan(t)) {
   Serial.println("Failed to read from DHT sensor!");
      return;
   }
   if(millis()-t0>timer){
   Serial.print("Humidity: "); 
   Serial.print(h);
   Serial.print(" %\t");
   Serial.print("Temperature: "); 
   Serial.print(t);
   Serial.println(" *C ");
   }
}

void sensor_dust(){
    if(millis()-t0>timer){
    dust[count]=readdust();
    Serial.print("Dust is :");
    Serial.print(takeaverage(dust));
    NodeSerial.print(takeaverage(dust));
      
    ///// get index for the next reading
    if ((count>numaverage-2)){
      count =0;
    }else{
      count +=1;
    }
    t0=millis();
  } 
}

//////////////////////////////////////////Display//////////////////////////////////////////

void Display(){
  unsigned short int td = millis();
  if(td-TD>timedisplay)
  {
    TD=td;
     display.setBrightness(0x0f);
     display.showNumberDec(takeaverage(dust), false);
  }
}

///////////////////////////////////////Data recive//////////////////////////////////////////
void data_recive(){

 if (NodeSerial.available() > 0){
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
 }
}

////////////////////////////////////////VIOD////////////////////////////////////////////////
////////////////////////////////////////LOOP/////////////////////////////////////////

void loop(){
//////////////////////////////////////////Capasitive Sent Control///////////////////////////////////////

  Bs      =  digitalRead(Bspeed);
  Bp      =  digitalRead(Bpow);
  Bpm     =  digitalRead(Bplasma);

Remote();  
powerset();
speedset();
plasmaset();
sensor_DHT();
sensor_dust();
Display();
//data_recive();

















}
