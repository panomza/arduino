#include <SoftwareSerial.h>

SoftwareSerial NodeSerial(11,12); // RX | TX
char datar;
int datasent=0;
///////////////////////////////////////////////////////////////////////////

#include <IRremote.h>
  const int RECV_PIN = 21;
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

///////////////////////////////////////////////////////////////////////////


// input pins

const short int Bpow    = 17;    // power button input pin
const short int Bspeed  = 16;    // speed input pin
//const short int Bplasma = 30;    // plasma button input pin
const short int Bauto   = 14;    // Auto button input pin
const short int Btimer  = 15;    // Timer button input pin

//output pins

const short int POW    = 5;      //power output pin
const short int PLASMA = 30;       // plasma button output pin
const short int M1     = 19;       // motor output pin
const short int M2     = 8;       // motor output pin
const short int M3     = 7;       // motor output pin
const short int M4     = 10;      // motor output pin
const short int BUZ    = 9;         // buzzer output pin
const short int AUTO   = 18; 
const short int dim    = 6; 


// state variables

//power
bool Bp         = 1;         //power button state
bool Lp         = 1;         //previous power button state 
bool stateP     = 1;         //power output state
bool powercount = 0;         // count if the power button is pushed
int powert0;

//plasma
bool Bpm        = 1;                  // plasma button state
bool Lpm        = 1;                  // previous plasma button state
bool statePM    = 1;        // plasma output state
bool plasmacount= 0;       // count if plasma has been pressed
int plasmat0;

//speed
bool Bs         = 1;                   // speed input state
bool Ls         = 1;                   // previous speed input state
bool stateS     = 0;         // speed state
unsigned int index = 0;                // case counter
short int speedt0;

//Timer
bool Bt         = 1;
bool Lt         = 1;
bool stateT     = 1;
short int Settime=0;
unsigned short int selectime = 0;
int timer0;
float timedown=0;
int timeshow0=0;
float timeshow1=0;
float timeshow2=0;

//Auto
bool Ba         = 1;
bool La         = 1;
bool stateA     = 0;
bool autocount  = 0;
int auto0;
unsigned short int Sauto;
short int autotime  = 0;
short int autotimer = 5000;

//delays
short int buttondelay=300;// delay between each button press in ms
unsigned int currenttime=0;
unsigned short int songindex=0;

int measurePin = A6;
int ledPower = 4;
const int numaverage = 150; ///number of values for taking average
float dust[numaverage];
unsigned short int count;
float initialdust=0;
float averagedust=initialdust;

//beep
bool beepvar=0;
bool beepstarted=0;
bool beeppowervar=0;
short int beeptime=0;

////////////////////////////////////VOID/////////////////////////////////////////////////
///////////////////////////////////SETUP/////////////////////////////////////////////////

void setup() {
Serial.begin(9600);


  irrecv.enableIRIn(); // Start the receiver

   int inputpins[4]={
    Bpow,Bspeed,Btimer,Bauto
    };

   int outputpins[8] = {
    POW,M1,M2,M3,M4,BUZ,AUTO,dim 
  };

  for(int j=0;j< sizeof(inputpins)/sizeof(1);j++){
    pinMode(inputpins[j],INPUT);
  }
  for(int j=0;j< sizeof(outputpins)/sizeof(1);j++){
    pinMode(outputpins[j],OUTPUT);
  }

  
  for(int i=0;i<numaverage;i++){
  dust[i]=initialdust;
  }

  beepvar=1;
  clearspeed();
  powoff();
  
  digitalWrite(POW,1);
 
  pinMode(11, INPUT); 
  pinMode(12,OUTPUT);

  pinMode(ledPower,OUTPUT);
  
  NodeSerial.begin(57600);
}

//////////////////////////////////////VOID////////////////////////////////////
//////////////////////////////////////LOOP////////////////////////////////////


void loop() {


currenttime= millis();

Dimmer();

beep();//beep version 1

//beeppower();//beep version2 for power on-off

statebutton();

Remote();

Display();

sensor_dust();

powerset();

speedset();

//plasmaset();

TIMER();

Auto();

read_smart();//read from the smart board

send_smart();

}
