
#include <avr/wdt.h>

///////////////////////////////////////////////////////////////////////////

#include <IRremote.h>
int RECV_PIN = 23;
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

const short int Bpow    = 20;    // power button input pin
const short int Bspeed  = 21;    // speed input pin
const short int Btimer  = 22;    // Timer button input pin

//output pins


const short int POW     = 10; 
const short int s1     = 24;        // speeed output pin
const short int s2     = 25;       // speeed output pin
const short int s3     = 26;       // speeed output pin
const short int s4     = 27;       // speeed output pin
const short int AUTO   = 28;
const short int timerled    = 4;
const short int h1     = 3;
const short int h2     = 2;
const short int h4     = 1;
const short int h8     = 0;
const short int dim    = 13;
const short int wifi_L   = 29;
const short int filtor = 30;

const short int BUZ    = 12;         // buzzer output pin
const short int M1     = 19;         // motor output pin
const short int M2     = 18;         // motor output pin
const short int M3     = 17;         // motor output pin
const short int M4     = 16;         // motor output pin



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

const short int measurePin = 31;
const short int ledPower = 11;
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
//unsigned int bwf = 0;
byte bnum = 0;


///////////////Bright////////////////

byte bright7 = 7;
byte brightdim = 30;
bool ck = 0;
bool Rd         = 1;           // speed input state
bool Ld        = 1;           // previous speed input state
bool dimcount = 0;               // case counter
unsigned int Rdim0 = 0;




////////////////////////////////////VOID/////////////////////////////////////////////////
///////////////////////////////////SETUP/////////////////////////////////////////////////

void setup() {

  Serial.begin(9600);

  
  tm1637_init_pin_for_sent_I2C();
  
  irrecv.enableIRIn(); // Start the receiver
  
//  wdt_enable(WDTO_120MS); // Watch dog function start

  int inputpins[3] = {Bpow, Bspeed, Btimer};

  int ledpins[14] ={ POW, s1, s2, s3, s4, AUTO, dim, timerled, h1, h2, h4, h8,wifi_L,filtor};
  
  int outputpins[6] = { M1, M2, M3, M4, BUZ,ledPower };

  for (int j = 0; j < sizeof(inputpins) / sizeof(1); j++) {
    pinMode(inputpins[j], INPUT);
  }
  
  for (int j = 0; j < sizeof(ledpins) / sizeof(1); j++) {
    pinMode(ledpins[j], OUTPUT);
  }

  for (int j = 0; j < sizeof(outputpins) / sizeof(1); j++) {
    pinMode(outputpins[j], OUTPUT);
  }

  digitalWrite(outputpins[6],0);
  
  beepvarS = 1;

  clearspeed();
  
//  Serial.println("Bord Reset");
}

//////////////////////////////////////VOID////////////////////////////////////
//////////////////////////////////////LOOP////////////////////////////////////

int HHH=0;
void loop() {

  currenttime = millis();
delay(300);
HHH++;
if(HHH>9){HHH=0;}
//  Dimmer();

//  beep();

//  statebutton();

//  Remote();

  Display();

//  sensor_dust();

//  powerset();

//  speedset();

//  TIMER();

//  Auto();



//  wdt_reset(); // Watch dog reset
}
