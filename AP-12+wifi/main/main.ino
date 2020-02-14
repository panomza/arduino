#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include "Adafruit_MCP23017.h"
Adafruit_MCP23017 mcp;
#include <avr/wdt.h>#include <avr/wdt.h>

SoftwareSerial NodeSerial(20, 21); // RX | TX

///////////////////////////////////////////////////////////////////////////

#include <IRremote.h>
const int RECV_PIN = 8;
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
const short int Btimer  = 16;    // Timer button input pin

//output pins


const short int POW     = 9; 
const short int s1     = 10;        // speeed output pin
const short int s2     = 11;       // speeed output pin
const short int s3     = 12;       // speeed output pin
const short int s4     = 13;       // speeed output pin
const short int AUTO   = 14;
const short int timerled    = 6;
const short int h1     = 5;
const short int h2     = 4;
const short int h4     = 3;
const short int h8     = 2;
const short int dim    = 8;
const short int wifi_L   = 0;
const short int filtor = 1;

const short int BUZ    = 9;         // buzzer output pin
const short int M1     = 4;         // motor output pin
const short int M2     = 5;         // motor output pin
const short int M3     = 6;         // motor output pin
const short int M4     = 7;         // motor output pin



//////////////////////////////////////////////////////////////////////////
// state variables

//////////////////////power//////////////////////

bool Bp         = 1;         //power button state
bool Lp         = 1;         //previous power button state
byte stateP     = 1;         //power output state
bool powercount = 0;         // count if the power button is pushed
unsigned int powert0 = 0;


/////////////////////speed////////////////////

bool Bs         = 1;           // speed input state
bool Ls         = 1;           // previous speed input state
bool speedcount = 0;           // check if button is pressed in the last loop
byte index = 0;                // case counter
unsigned int speedt0 = 0;

////////////////////Timer////////////////////

bool Bt         = 1;
bool Lt         = 1;
byte Settime = 0;
unsigned int timer0;
unsigned int timedown = 0;        // remaining time

unsigned int timetrig = 0;
unsigned int runtime = 0;


/////////////////Auto////////////////////

bool Ba         = 1;
bool La         = 1;
bool stateA     = 0;    //auto state
bool autocount  = 0;
unsigned int autotime = 0;
unsigned int auto0 = 0;


///////////////delays////////////////////

unsigned int buttondelay = 200; // delay between each button press in ms
unsigned int currenttime = 0;


//////////////dust sensor///////////////

const short int measurePin = A6;
const short int ledPower = 17;
const short int numaverage = 100; ///number of values for taking average
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
bool ck = 0;
bool Rd         = 1;           // speed input state
bool Ld        = 1;           // previous speed input state
bool dimcount = 0;               // case counter
unsigned int Rdim0 = 0;


char datar;


////////////////////////////////////VOID/////////////////////////////////////////////////
///////////////////////////////////SETUP/////////////////////////////////////////////////

void setup() {

  Serial.begin(9600);
  NodeSerial.begin(57600);
  mcp.begin();
  tm1637_init_pin_for_sent_I2C();
  irrecv.enableIRIn(); // Start the receiver
  
  wdt_enable(WDTO_120MS); // Watch dog function start

  int inputpins[3] = {Bpow, Bspeed, Btimer};

  int ledpins[12] = { POW, s1, s2, s3, s4, AUTO, dim, timerled, h1, h2, h4, h8};

  int outputpins[6] = { M1, M2, M3, M4, BUZ, ledPower };

  for (int j = 0; j < sizeof(inputpins) / sizeof(1); j++) {
    pinMode(inputpins[j], INPUT);
  }

  for (int j = 0; j < sizeof(ledpins) / sizeof(1); j++) {
    mcp.pinMode(ledpins[j], OUTPUT);
    mcp.digitalWrite(ledpins[j],0);
  }

  for (int j = 0; j < sizeof(outputpins) / sizeof(1); j++) {
    pinMode(outputpins[j], OUTPUT);
  }

  digitalWrite(outputpins[6],0);
  
  beepvarS = 1;

  clearspeed();
  
  pinMode(20, INPUT);
  pinMode(21, OUTPUT);
  Serial.println("Bord Reset");
}

//////////////////////////////////////VOID////////////////////////////////////
//////////////////////////////////////LOOP////////////////////////////////////


void loop() {

  currenttime = millis();

  Dimmer();

  beep();

  statebutton();

  Remote();

  Display();

  sensor_dust();

  powerset();

  speedset();

  TIMER();

  Auto();

  read_smart();

  send_smart();

//  simulate_hang(); //stalls if timedown > 35 and stateA ==1

  wdt_reset(); // Watch dog reset
}
