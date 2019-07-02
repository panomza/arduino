#include <SoftwareSerial.h>

SoftwareSerial NodeSerial(11, 12); // RX | TX

///////////////////////////////////////////////////////////////////////////

#include <IRremote.h>
const int RECV_PIN = 21;
IRrecv irrecv(RECV_PIN);
decode_results results;
#define OUTPUT_COUNT 5

long remote_key[] = {0xDF40BF, 0xDF609F, 0xDF48B7, 0xDF50AF, 0xDF708F};
const byte outputPins[OUTPUT_COUNT] = {0, 1, 2, 3, 4};
bool status1[5] = {0, 0, 0, 0, 0};
struct keypad {
  boolean state;
};
keypad output[OUTPUT_COUNT];

///////////////////////////////////////////////////////////////////////////


// input pins

const short int Bpow    = 14;    // power button input pin
const short int Bspeed  = 15;    // speed input pin
const short int Bauto   = 17;    // Auto button input pin
const short int Btimer  = 16;    // Timer button input pin

//output pins

const short int POW    = 5;      //power output pin
const short int M1     = 4;       // motor output pin
const short int M2     = 7;       // motor output pin
const short int M3     = 8;       // motor output pin
const short int M4     = 10;      // motor output pin
const short int BUZ    = 9;         // buzzer output pin
const short int AUTO   = 20;
const short int dim    = 6;
const short int timerled    = 18;

//////////////////////////////////////////////////////////////////////////
// state variables

//////////////////////power//////////////////////

bool Bp         = 1;         //power button state
bool Lp         = 1;         //previous power button state
bool stateP     = 1;         //power output state
bool powercount = 0;         // count if the power button is pushed
unsigned int powert0 = 0;


/////////////////////speed////////////////////

bool Bs         = 1;           // speed input state
bool Ls         = 1;           // previous speed input state
bool speedcount = 0;
byte index = 0;                // case counter
unsigned int speedt0 = 0;

////////////////////Timer////////////////////

bool Bt         = 1;
bool Lt         = 1;
bool BTcount = 0;
byte Settime = 0;
byte statetime = 0;
unsigned int timer0;
float timedown = 0;
unsigned int timeshow0 = 0;
float timeshow1 = 0;
float timeshow2 = 0;

unsigned int timetrig = 0;
unsigned int runtime = 0;
unsigned int buttontime0 = 0;
unsigned int buttontime1 = 0;
byte buttoncount0 = 0;
byte buttoncount1 = 0;
bool beepout = 0;
bool checkstate_in = 0;

/////////////////Auto////////////////////

bool Ba         = 1;
bool La         = 1;
bool stateA     = 0;
bool autocount  = 0;
unsigned int auto0 = 0;
unsigned int autotime = 0;


///////////////delays////////////////////

unsigned int buttondelay = 200; // delay between each button press in ms
unsigned int currenttime = 0;


//////////////dust sensor///////////////

const short int measurePin = A6;
const short int ledPower = 19;
const short int numaverage = 150; ///number of values for taking average
unsigned int count;
unsigned int dust[numaverage];
unsigned int averagedust = 0;


///////////////beep///////////////////

bool songindex = 0;
bool beepvarB = 0;
bool beepvarS = 0;
bool beepstarted = 0;
bool beepstartedS = 0;
byte beeppowervar = 0;
unsigned int beeptime = 0;
unsigned int beeptimeS = 0;
int play = 0;
int soundtime = 0;
unsigned int bwf = 0;
byte bnum = 0;
bool wfcount = 0;
byte wifi = 0;
bool Wi = 0;

///////////////Bright////////////////

byte bright7 = 0;
byte brightdim = 30;


char datar;


////////////////////////////////////VOID/////////////////////////////////////////////////
///////////////////////////////////SETUP/////////////////////////////////////////////////

void setup() {

  Serial.begin(9600);


  irrecv.enableIRIn(); // Start the receiver

  int inputpins[4] = {Bpow, Bspeed, Btimer, Bauto};

  int outputpins[9] = {POW, M1, M2, M3, M4, BUZ, AUTO, dim, timerled};

  for (int j = 0; j < sizeof(inputpins) / sizeof(1); j++) {
    pinMode(inputpins[j], INPUT);
  }

  for (int j = 0; j < sizeof(outputpins) / sizeof(1); j++) {
    pinMode(outputpins[j], OUTPUT);
  }



  beepvarS = 1;

  clearspeed();

  digitalWrite(POW, 0);
  
  statetime=0;

  pinMode(11, INPUT);
  pinMode(12, OUTPUT);

  pinMode(ledPower, OUTPUT);

  NodeSerial.begin(57600);
  pinMode(A7, OUTPUT);
}

//////////////////////////////////////VOID////////////////////////////////////
//////////////////////////////////////LOOP////////////////////////////////////


void loop() {


  currenttime = millis();

  Dimmer();

//  beep();

  statebutton();

//  Remote();

  Display();

  sensor_dust();

  powerset();

  speedset();

  TIMER();

  Auto();

//  read_smart();

//  send_smart();


}
