
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
const short int Btimer = 18;
const short int Bauto = 17;

//output pins

const short int POW=13;         //power output pin
const short int PLASMA=11;       // plasma button output pin
const short int M1 = 7;        // motor output pin
const short int M2 =  8;        // motor output pin
const short int M3 =  9;        // motor output pin
const short int M4 =  10;       // motor output pin
const short int BUZ;        // buzzer output pin
const short int AUTO = 12; 


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

//delays
short int buttondelay=300;// delay between each button press in ms

void setup() {
Serial.begin(9600);
  
   int inputpins[5]={
    Bpow,Bspeed,Bplasma,Btimer,Bauto
    };

  int outputpins[8] = {
    POW,PLASMA,M1,M2,M3,M4,BUZ,AUTO
  };
/*
  for(int j=0;j< sizeof(inputpins)/sizeof(1);j++){
    pinMode(inputpins[j],INPUT);
    Serial.print(inputpins[j]);
    Serial.println(" is set as input");
  }*/
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

}


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


void Auto(){
   if(stateA==0){
      if(50>=40){index=4;}
      else if(50>=30){index=3;}
      else if(50>=20){index=2;}
      else if(05>=15){index=1;}
   }
    if ((Ba != La) && (stateP == 0) && (millis()-auto0 > buttondelay) && (autocount ==0)){
    stateA=!stateA;
    digitalWrite(AUTO,stateA);
    Serial.print("Auto is set to: ");
    Serial.println(stateA); 
    La=Ba;
    auto0 = millis();
    autocount =1;
    }
   else if ((Ba != La) && (Ba == 1)&& (millis()-auto0 > buttondelay)){
    La=Ba;
    autocount = 0;
  }
}
void loop() {
  Bp      =  digitalRead(Bpow);
  Bs      =  digitalRead(Bspeed);
  Bpm     =  digitalRead(Bplasma);
  Ba      =  digitalRead(Bauto);
  
powerset();
speedset();
plasmaset();
Auto();
applythespeedswitch();
}
