//#include <SoftwareSerial.h>
//#include <ArduinoJson.h>
#include <avr/wdt.h>
#include <EEPROM.h>

#include <TimerOne.h>
#include <Wire.h>

//SoftwareSerial NodeSerial(6, 7); // RX | TX

///////////////////////////////////////////////////////////////////////////

#include <IRremote.h>
int RECV_PIN = 8;
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
const short int Bfilter = 10;    // filter button input pin


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
byte speed_led = 10;

////////////////////Timer////////////////////

bool Bt         = 1;
bool Lt         = 1;
byte Settime = 0;
unsigned int timer0;
unsigned int timedown = 0;        // remaining time
byte timer_led = 10;
unsigned int timetrig = 0;
unsigned int runtime = 0;


/////////////////Auto////////////////////

bool Ba         = 1;
bool La         = 1;
bool stateA     = 0;    //auto state
bool autocount  = 0;
unsigned int autotime = 0;
unsigned int auto0 = 0;

/////////////////Reset filter////////////////////

bool Bf         = 1;
bool Lf         = 1;
bool filtercount  = 0;
unsigned int filtertime = 0;
unsigned int filter0 = 0;

///////////////delays////////////////////

unsigned int buttondelay = 50; // delay between each button press in ms
unsigned int currenttime = 0;


//////////////dust sensor///////////////

const short int measurePin = 31;
const short int ledPower = 11;
const short int numaverage = 100; ///number of values for taking average
unsigned int count;
unsigned int dust[numaverage];
unsigned int averagedust = 0;
unsigned int panadust = 0;

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

//bool wfcount = 0;
//byte wifi = 0;
//bool Wi = 0;

///////////////Bright////////////////

byte bright7 = 7;
byte brightdim = 30;
bool ck = 0;
bool Rd         = 1;           // speed input state
bool Ld        = 1;           // previous speed input state
bool dimcount = 0;               // case counter
unsigned int Rdim0 = 0;

unsigned long time_filter = 0;
unsigned long time_update = 0;
unsigned long min_filter = 0;
byte alarm = 0;

//char datar;


////////////////////////////////////VOID/////////////////////////////////////////////////
///////////////////////////////////SETUP/////////////////////////////////////////////////

void setup() {

  Serial.begin(9600);
//  NodeSerial.begin(57600);

   Wire.begin();  // Connection start
   Wire.setClock(60000L);
  
  tm1637_init_pin_for_sent_I2C();
  
  irrecv.enableIRIn(); // Start the receiver
  
//  wdt_enable(WDTO_120MS); // Watch dog function start

  int inputpins[4] = {Bpow, Bspeed, Btimer, Bfilter};
  
  int outputpins[6] = { M1, M2, M3, M4, BUZ,ledPower };

  for (int j = 0; j < sizeof(inputpins) / sizeof(1); j++) {
    pinMode(inputpins[j], INPUT);
  }

  for (int j = 0; j < sizeof(outputpins) / sizeof(1); j++) {
    pinMode(outputpins[j], OUTPUT);
  }

  digitalWrite(outputpins[6],0);
  
  beepvarS = 1;

  clearspeed();
  
//  pinMode(6, INPUT);
//  pinMode(7, OUTPUT);
//  Serial.println("Bord Reset");
}

//////////////////////////////////////VOID////////////////////////////////////
//////////////////////////////////////LOOP////////////////////////////////////

int l=0;
unsigned t10 =0;
unsigned t11 =0;
bool tt =0;

void loop() {


if(currenttime-t10>2000){t10=currenttime;sensor_pana();tt=!11;}
//Serial.println(tt);

//t10 = millis();
  currenttime = millis();

  Dimmer();

  beep();

  statebutton();

  Remote();

  Display();

//  sensor_dust();

//  sensor_pana();

  powerset();

  speedset();

  TIMER();

  Auto();

  filter();

//  read_smart();

//  send_smart();

//  simulate_hang(); //stalls if timedown > 35 and stateA ==1

//  wdt_reset(); // Watch dog reset

//t11 = millis();
}
