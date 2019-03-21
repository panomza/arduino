#include <toneAC.h>
/////////////////song definition////////////
/*************************************************
 * Public Constants
 *************************************************/

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978


//##############**"HE IS A PIRATE" Theme song of Pirates of caribbean**##############//
int Pirates_note[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0
};
int change_speed[]={
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
};
int turn_off[]={
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};

int Pirates_duration[] = {
    12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};
//###########End of He is a Pirate song#############//

///// play song////

// Melody liberated from the toneMelody Arduino example sketch by Tom Igoe.
int melody[] = { 262, 196, 196, 220, 196, 0, 247, 262 };
int noteDurations[] = { 8, 16, 16, 8, 8, 8, 8, 8 };

float midi[127];
int a = 440; // a is 440 hz...



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

const int numaverage = 20;//number of values for taking average
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
const short int M3 =  17;        // motor output pin
const short int M4 =  19;       // motor output pin
//const short int BUZ = 9;        // buzzer output pin
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
Serial.begin(9600);
///////////////////////////////////////Capasitive Sent Control///////////////////////////////////
  int inputpins[5]={
    Bpow,Bspeed,Bplasma,Btimer,Bauto
    };

  int outputpins[7] = {
    POW,PLASMA,M1,M2,M3,M4,AUTO
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
  /////////////////set up tone conversion///////////////
  for (int x = 0; x < 127; ++x)
{
   midi[x] = (a / 32) * (2 ^ ((x - 9) / 12));
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

///////////////play sound///////////
void play_sound(){
    for (int thisNote = 0; thisNote < sizeof(Pirates_note) / sizeof(int); thisNote++) {
    int noteDuration = 1000/Pirates_duration[thisNote];
    toneAC(Pirates_note[thisNote], 10, noteDuration, true); // Play thisNote at full volume for noteDuration in the background.
    delay(noteDuration * 4 / 3); // Wait while the tone plays in the background, plus another 33% delay between notes.
  }
  toneAC();
}
void play_sound_change_speed(){
    for (int thisNote = 0; thisNote < sizeof(change_speed) / sizeof(int); thisNote++) {
    int noteDuration = 1000/Pirates_duration[thisNote];
    toneAC(change_speed[thisNote], 10, noteDuration, true); // Play thisNote at full volume for noteDuration in the background.
    delay(noteDuration * 4 / 3); // Wait while the tone plays in the background, plus another 33% delay between notes.
  }
  toneAC();
}
void play_sound_turn_off(){
    for (int thisNote = 0; thisNote < sizeof(turn_off) / sizeof(int); thisNote++) {
    int noteDuration = 1000/Pirates_duration[thisNote];
    toneAC(turn_off[thisNote], 10, noteDuration, true); // Play thisNote at full volume for noteDuration in the background.
    delay(noteDuration * 4 / 3); // Wait while the tone plays in the background, plus another 33% delay between notes.
  }
  toneAC();
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

if(Bp==0 && stateP==1){

  play_sound();
}
if(Bs==0){
  play_sound_change_speed();
}

if(Bp==0 && stateP==0){

  play_sound_turn_off();
}

}
