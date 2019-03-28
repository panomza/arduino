#include <SoftwareSerial.h>

SoftwareSerial NodeSerial(7,8); // RX | TX
char datar;
int datasent=0;
///////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////

short int powert0; 
short int speedt0;
short int plasmat0;
short int auto0;
short int timer0;

// input pins

const short int Bpow    = 14;    // power button input pin
const short int Bspeed  = 15;    // speed input pin
const short int Bplasma = 16;    // plasma button input pin
const short int Bauto   = 18;    // Auto button input pin
const short int Btimer ;    // Timer button input pin

//output pins

const short int POW    = 13;      //power output pin
const short int PLASMA = 6;       // plasma button output pin
const short int M1     = 19;       // motor output pin
const short int M2     = 20;       // motor output pin
const short int M3     = 17;       // motor output pin
const short int M4     = 10;      // motor output pin
const short int BUZ    = 9;         // buzzer output pin
const short int AUTO   = 11; 

// state variables

//power
bool Bp         = 1;         //power button state
bool Lp         = 1;         //previous power button state 
bool stateP     = 1;         //power output state
bool powercount = 0;         // count if the power button is pushed

//plasma
bool Bpm        = 1;                  // plasma button state
bool Lpm        = 1;                  // previous plasma button state
bool statePM    = 1;        // plasma output state
bool plasmacount= 0;       // count if plasma has been pressed

//speed
bool Bs         = 1;                   // speed input state
bool Ls         = 1;                   // previous speed input state
bool stateS     = 0;         // speed state
unsigned short int index = 1;                // case counter

//Timer
bool Bt         = 1;
bool Lt         = 1;
bool stateT     = 1;
bool timercount = 0;
unsigned short int selectime = 0;

//Auto
bool Ba         = 1;
bool La         = 1;
bool stateA     = 1;
bool autocount  = 0;
unsigned short int Sauto;
float autotime  = 0;
float autotimer = 2000;

//delays
short int buttondelay=300;// delay between each button press in ms
float currenttime=0;
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
float beeptime=0;
bool beeppowervar=0;

////////////////////////////////////VOID/////////////////////////////////////////////////
///////////////////////////////////SETUP/////////////////////////////////////////////////

void setup() {
Serial.begin(9600);

  irrecv.enableIRIn(); // Start the receiver
  
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

    pinMode(ledPower,OUTPUT);
  for(int i=0;i<numaverage;i++){
  dust[i]=initialdust;
  }
  beepvar=1;

  pinMode(7, INPUT); 
  pinMode(8,OUTPUT);

  NodeSerial.begin(57600);
}

//////////////////////////////////////VOID////////////////////////////////////
//////////////////////////////////////LOOP////////////////////////////////////


void loop() {
currenttime=millis();


//beep();//beep version 1
//beeppower();//beep version2 for power on-off

//checkbuttons();
statebutton();
Remote();

//Display();
//sensor_dust();
powerset();
speedset();
plasmaset();
Auto();
read_smart();//read from the smart board
//rundata();
}
