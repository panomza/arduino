
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
<<<<<<< HEAD
const short int Btimer = 18;
const short int Bauto = 17;
=======
const short int Btimer = 17;
const short int Bauto = 18;
>>>>>>> 45305bd0dd51906c88fe5434b51470c5851d3124

//output pins

const short int POW=13;         //power output pin
<<<<<<< HEAD
const short int PLASMA=11;       // plasma button output pin
=======
const short int PLASMA=6;       // plasma button output pin
>>>>>>> 45305bd0dd51906c88fe5434b51470c5851d3124
const short int M1 = 7;        // motor output pin
const short int M2 =  8;        // motor output pin
const short int M3 =  9;        // motor output pin
const short int M4 =  10;       // motor output pin
const short int BUZ;        // buzzer output pin
<<<<<<< HEAD
const short int AUTO = 12; 
=======
const short int AUTO = 11; 
>>>>>>> 45305bd0dd51906c88fe5434b51470c5851d3124


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
float currenttime=0;
int measurePin = 19;
int ledPower = 12;

const int numaverage = 20; ///number of values for taking average
float dust[numaverage];

unsigned short int count;
float initialdust=20;
float averagedust=initialdust;

void setup() {
Serial.begin(9600);
  
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

    pinMode(ledPower,OUTPUT);
  for(int i=0;i<numaverage;i++){
  dust[i]=initialdust;
  }

}





void TIMER(){
  Serial.println(selectime);
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
  
  switch (selectime) {
      case 0:
       unsigned int tr = millis();
     if(tr>10000){stateP=1;}      
//      digitalWrite(,1);
      break;
  }
}




void loop() {
<<<<<<< HEAD
  Bp      =  digitalRead(Bpow);
  Bs      =  digitalRead(Bspeed);
  Bpm     =  digitalRead(Bplasma);
  Ba      =  digitalRead(Bauto);
  
=======




 
currenttime=millis();
 
>>>>>>> 45305bd0dd51906c88fe5434b51470c5851d3124
powerset();
speedset();
plasmaset();
Auto();
applythespeedswitch();
Display();
sensor_dust();
}
