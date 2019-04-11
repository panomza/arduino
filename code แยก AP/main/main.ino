#include <SoftwareSerial.h>

SoftwareSerial NodeSerial(7,8); // RX | TX
char datar;
int datasent=0;
///////////////////////////////////////////////////////////////////////////

//#include <IRremote.h>
//  const int RECV_PIN = 3;
//  IRrecv irrecv(RECV_PIN);
//  decode_results results;
//#define OUTPUT_COUNT 5
//
//    unsigned long last = millis();
//    long remote_key[]={0xDF40BF,0xDF609F,0xDF48B7,0xDF50AF,0xDF708F};
//    const byte outputPins[OUTPUT_COUNT] = {0, 1, 2, 3,4};
//    bool status1[5] = {0,0,0,0,0};
//    struct keypad {
//    boolean state;
//};
//keypad output[OUTPUT_COUNT];

///////////////////////////////////////////////////////////////////////////

// input pins

const short int Bpow    = 31;    // power button input pin
const short int Bspeed  = 23;    // speed input pin
const short int Bplasma = 21;    // plasma button input pin
const short int Bauto   = 20;    // Auto button input pin
const short int Btimer  = 22;    // Timer button input pin

//output pins

const short int POW    = 28;      //power output pin
const short int PLASMA = 14;       // plasma button output pin
const short int M1     = 12;       // motor output pin
const short int M2     = 30;       // motor output pin
const short int M3     = 10;       // motor output pin
const short int M4     = 11;      // motor output pin
const short int BUZ    = 13;         // buzzer output pin
const short int AUTO   = 19; 
const short int dim    = 29; 
const short int T1     = 17;       // motor output pin
const short int T2     = 18;       // motor output pin
const short int T3     = 15;       // motor output pin
const short int T4     = 16;

// state variables

//power
bool Bp         = 1;         //power button state
bool Lp         = 1;         //previous power button state 
bool stateP     = 1;         //power output state
bool powercount = 0;         // count if the power button is pushed
short int powert0;

//plasma
bool Bpm        = 1;                  // plasma button state
bool Lpm        = 1;                  // previous plasma button state
bool statePM    = 0;        // plasma output state
bool plasmacount= 0;       // count if plasma has been pressed
short int plasmat0;

//speed
bool Bs         = 1;                   // speed input state
bool Ls         = 1;                   // previous speed input state
bool stateS     = 0;         // speed state
unsigned short int index = 1;                // case counter
short int speedt0;

//Timer
bool Bt         = 1;
bool Lt         = 1;
bool stateT     = 1;
bool timercount = 0;
unsigned short int selectime = 0;
short int timer0;

//Auto
bool Ba         = 1;
bool La         = 1;
bool stateA     = 0;
bool autocount  = 0;
short int auto0;
unsigned short int Sauto;
short int autotime  = 0;
short int autotimer = 2000;

//delays
short int buttondelay=300;// delay between each button press in ms
short int currenttime=0;
unsigned short int songindex=0;

int measurePin = 19;
int ledPower = 12;
const int numaverage = 20; ///number of values for taking average
float dust[numaverage];
unsigned short int count;
float initialdust=20;
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

//  irrecv.enableIRIn(); // Start the receiver

   int inputpins[5]={
    Bpow,Bspeed,Bplasma,Btimer,Bauto
    };

   int outputpins[13] = {
    POW,PLASMA,M1,M2,M3,M4,BUZ,AUTO,dim,T1,T2,T3,T4
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

    pinMode(ledPower,OUTPUT);
  for(int i=0;i<numaverage;i++){
  dust[i]=initialdust;
  }
  beepvar=1;
  clearspeed();
  powoff();
 
  pinMode(7, INPUT); 
  pinMode(8,OUTPUT);

  NodeSerial.begin(57600);
}

//////////////////////////////////////VOID////////////////////////////////////
//////////////////////////////////////LOOP////////////////////////////////////


void loop() {
currenttime=millis();

digitalWrite (dim,1);

beep();//beep version 1

//beeppower();//beep version2 for power on-off

statebutton();

//Remote();

//Display();

//sensor_dust();

powerset();

speedset();

plasmaset();

TIMER();

Auto();

//read_smart();//read from the smart board

}
