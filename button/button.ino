#include <TonePlayer.h> 
TonePlayer tone1 (TCCR1A, TCCR1B, OCR1AH, OCR1AL, TCNT1H, TCNT1L);



float currenttime=0;
//////////////////////////////////////////Sensor/////////////////////////////////////////////////
///DHT Sensor/////
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float Temp ;
float Humi ;

////////Dust Sensor//////////
int measurePin = 19;
int ledPower = 12;

const int numaverage = 50;//number of values for taking average
float dust[numaverage];

unsigned short int count=0;
float initialdust=20;
float averagedust=initialdust;

float t0;// time of last reading
float timer=500;// time between each reading

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

float readdust(){
  digitalWrite(ledPower,0);
  delayMicroseconds(280);
  voMeasured = analogRead(measurePin);
  delayMicroseconds(40);
  digitalWrite(ledPower,1);
  delayMicroseconds(9680);

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
short int auto0;
short int timer0;

/// pin definition

// input pins
const short int Bpow = 14;      //power button input pin
const short int Bspeed = 15;    // speed input pin
const short int Bplasma = 16;   // plasma button input pin
const short int Btimer = 17;
const short int Bauto = 18;

//output pins

const short int POW=13;         //power output pin
const short int PLASMA=6;       // plasma button output pin
const short int M1 =  7;        // motor output pin
const short int M2 =  8;        // motor output pin
const short int M3 =  9;        // motor output pin
const short int M4 =  10;       // motor output pin
const short int BUZ = 5;        // buzzer output pin
const short int AUTO = 11; 


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

//Timer
bool Bt=1;
bool Lt=1;
bool stateT = 1;
bool timercount=0;
unsigned short int selectime = 0;

//Auto
bool Ba=1;
bool La=1;
bool stateA = 1;
bool autocount=0;
unsigned short int Sauto;
float autotime=0;
float autotimer=2000;

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

///////////////////////////////////////////Void//////////////////////////////////////
//////////////////////////////////////////Setup//////////////////////////////////////
void setup() {
pinMode (17, OUTPUT); // output pin is fixed (OC1A) 
tone1.tone (220); // 220 Hz 
delay (500); 
tone1.noTone (); 
tone1.tone (440);
delay (500); 
tone1.noTone (); 
tone1.tone (880); 
delay (500); 
tone1.noTone ();


Serial.begin(9600);

///////////////////////////////////////Capasitive Sent Control///////////////////////////////////
  int inputpins[5]={
    Bpow,Bspeed,Bplasma,Btimer,Bauto
    };

  int outputpins[8] = {
    POW,PLASMA,M1,M2,M3,M4,BUZ,AUTO
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
   dht.begin();
   ////Dust Sensor//////
  pinMode(ledPower,OUTPUT);
  for(int i=0;i<numaverage;i++){
  dust[i]=initialdust;
  }

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
    index=1;
    powert0 = millis();
    clearspeed();
    poweroff();
    powercount = 1;
} 
  else if ((Bp != Lp) && (Bp == 1)&& (millis()-powert0 > buttondelay)){
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

void poweroff(){

     if(stateP==1){statePM=1;}
      digitalWrite(PLASMA,1);
     if(stateP==1){stateA=1;}
      digitalWrite(AUTO,1);
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

 if ((Bs != Ls) && (stateP==0) && (Bs == 0)&& (millis()-speedt0 > buttondelay)&&(stateA==1)){  
     stateS=!stateS;
     index++;
     if(index>4){index=1;}
     Serial.print("Speed is set to: ");
     Serial.println(index);
     speedt0=millis(); // get the current time
     Ls=Bs;
 }
 else if ((Bs != Ls) && (Bs == 1)&& (millis()-speedt0 > buttondelay)){
    Ls=Bs;
  }
  
}

void applythespeedswitch(){
  if(stateP==0){
    switch (index) {
    case 0:
      clearspeed();
      digitalWrite(PLASMA,1);
      break;
    case 1:
      clearspeed();
      digitalWrite(M1,0);   
     // Serial.println("M1");
      break;
    case 2:
      clearspeed();
      digitalWrite(M2,0);
     // Serial.println("M2");
      break;
    case 3:
      clearspeed();
      digitalWrite(M3,0);
     // Serial.println("M3");
      break;
    case 4:
      clearspeed();
      digitalWrite(M4,0);
     // Serial.println("M4");
      break;
  }
  }
}


void TIMER(){
 if ((Bt != Lt) && (stateP==0) && (Bt == 0)&& (millis()-timer0 > buttondelay)){  
     stateT=!stateT;
     selectime++;
     if(selectime>4){selectime=1;}
     timer0=millis(); // get the current time
     Lt=Bt;
 }
 else if ((Bt != Lt) && (Bt == 1)&& (millis()-timer0 > buttondelay)){
    Lt=Bt;
  }
  
  switch (index) {
      case 1:
       unsigned int tr = millis();
     if(tr>10000){stateP=1;}      
//      digitalWrite(,1);
      break;
  }


  }


void Auto(){
  // set speed according to dust
    if(currenttime-autotime>autotimer && stateA==0){
        Serial.print("average dust is :");
        Serial.println(averagedust);
        if(averagedust>=40){index=4;Serial.println("speed is set to 4");}
        else if(averagedust>=30){index=3;Serial.println("speed is set to 3");}
        else if(averagedust>=20){index=2;Serial.println("speed is set to 2");}
        else{index=1;Serial.println("speed is set to 1");}
        autotime=currenttime;
        Serial.println("speed is set by the auto function");
    }
    // activate or deactivate auto function
    if ((Ba != La) && (stateP == 0) && (currenttime-auto0 > buttondelay) && (autocount ==0)){
        stateA=!stateA;
        digitalWrite(AUTO,stateA);
        Serial.print("Auto is set to: ");
        Serial.println(stateA); 
        La=Ba;
        auto0 = currenttime;
        autocount =1;
    } else if ((Ba != La) && (Ba == 1)&& (currenttime-auto0 > buttondelay)){
      La=Ba;
      autocount = 0;
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
   Temp = t;
   Humi = h;
  
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
      count++;
    dust[count]=readdust();
    Serial.print("Dust is :");
    averagedust=takeaverage(dust);
    Serial.println(averagedust);
          
    ///// get index for the next reading
    if ((count>numaverage)){
      count =0;
    }
    t0=millis(); 
  } 
}

//////////////////////////////////////////Display//////////////////////////////////////////

void Display(){
//  Serial.println("display started");
  unsigned short int td = millis();
//  Serial.println("display started 1");
  if(td-TD>timedisplay)
  {
    TD=td;
     display.setBrightness(0x0f);
     display.showNumberDec(averagedust, false);
     Serial.println("display started 2");
  }
//  Serial.println("display started 2");
}



////////////////////////////////////////VIOD////////////////////////////////////////////////
////////////////////////////////////////LOOP/////////////////////////////////////////

void loop(){
//////////////////////////////////////////Capasitive Sent Control///////////////////////////////////////

  Bs      =  digitalRead(Bspeed);
  Bp      =  digitalRead(Bpow);
  Bpm     =  digitalRead(Bplasma);
  Ba      =  digitalRead(Bauto);
// Serial.println(statePM);
currenttime=millis();
Remote();  
powerset();
speedset();
plasmaset();
Auto();
//sensor_DHT();
sensor_dust();
Display();
applythespeedswitch();

















}
