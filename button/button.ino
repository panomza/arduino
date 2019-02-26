

//set time variables
short int powert0; 
short int speedt0;
short int plasmat0;

/// pin definition

// input pins
const short int Bspeed = 15;    // speed input pin
const short int Bpow = 14;      //power button input pin
const short int Bplasma = 16;   // plasma button input pin


//output pins

const short int POW=13;         //power output pin
const short int PLASMA=6;       // plasma button output pin
const short int M1 =  7;        // motor output pin
const short int M2 =  8;        // motor output pin
const short int M3 =  9;        // motor output pin
const short int M4 =  10;       // motor output pin
const short int BUZ = 4;        // buzzer output pin



// state variables

//power
bool Bp=1;               //power button state
bool Lp=1;               //previous power button state 
bool stateP = 1;     //power output state
bool powercount=0;        // count if the power button is pushed

//plasma
bool Bpm=1;                  // plasma button state
bool Lpm=1;                  // previous plasma button state
bool statePM = 0;        // plasma output state
bool plasmacount=0;       // count if plasma has been pressed

//speed
bool Bs=1;                   // speed input state
bool Ls=1;                   // previous speed input state
bool stateS = 0;         // speed state
unsigned short int index = 1;                // case counter


//delays
short int buttondelay=500;// delay between each button press in ms





void setup() {
    Serial.begin(9600); 
  int inputpins[3]={
    Bpow,Bspeed,Bplasma
    };

  int outputpins[7] = {
    POW,PLASMA,M1,M2,M3,M4,BUZ
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
}


void powerset(){
//apply power

 // assign power on and off

  if ((Bp != Lp) && (Bp == 0) && (millis()-powert0 > buttondelay) && (powercount==0)){
    stateP=!stateP;
    digitalWrite(POW,stateP);
    Serial.print("Power is set to: ");
    Serial.println(stateP); 
    applythespeedswitch(); // apply the switch for speed when turning on
    Lp=Bp;
    powert0 = millis();
    powercount = 1;
    if(stateP==1){
      clearspeed();
      digitalWrite(PLASMA,1);
    }
  } else if ((Bp != Lp) && (Bp == 1)&& (millis()-powert0 > buttondelay)){
    Lp=Bp;
    powercount = 0;
  }
}

void plasmaset(){
    if ((Bpm != Lpm) && (Bpm == 0) && (millis()-plasmat0 > buttondelay) && (plasmacount ==0)){
    statePM=!statePM;
    digitalWrite(PLASMA,statePM);
    Serial.print("Plasma is set to: ");
    Serial.println(statePM); 
    Lpm=Bpm;
    plasmat0 = millis();
    plasmacount =1;
  } else if ((Bpm != Lpm) && (Bpm == 1)&& (millis()-plasmat0 > buttondelay)){
    Lpm=Bpm;
    plasmacount = 0;
  }
}




void clearspeed(){
      digitalWrite(M4,1);
      digitalWrite(M1,1);  
      digitalWrite(M2,1);
      digitalWrite(M3,1);
}

void applythespeedswitch(){
    switch (index) {
    case 0:
      //clearspeed();
      //digitalWrite(PLASMA,1);
      break;
    case 1:
      clearspeed();
      digitalWrite(M1,LOW);   
     // Serial.println("M1");
      break;
    case 2:
      clearspeed();
      digitalWrite(M2,LOW);
     // Serial.println("M2");
      break;
    case 3:
      clearspeed();
      digitalWrite(M3,LOW);
     // Serial.println("M3");
      break;
    case 4:
      clearspeed();
      digitalWrite(M4,LOW);
     // Serial.println("M4");
      break;
  }
}


void speedset(){ // set up the speed

 if ((Bs != Ls) && (stateP==0) && (Bs == 0)&& (millis()-speedt0 > buttondelay)){  
     stateS=!stateS;
     index++;
     if(index>4){index=1;}
     Serial.print("Speed is set to: ");
     Serial.println(index);
     speedt0=millis(); // get the current time
     Ls=Bs;
     applythespeedswitch();
 } else if ((Bs != Ls) && (Bs == 1)&& (millis()-plasmat0 > buttondelay)){
    Ls=Bs;
  }
  
}






void loop(){

 // read inputs
 // Serial.println(i);
  Bs      =  digitalRead(Bspeed);
  Bp      =  digitalRead(Bpow);
  Bpm     =  digitalRead(Bplasma);
  //Serial.println(Bs);

 //apply read input to the output


//apply power

powerset();

// turn off the machine (everything)
// if(stateP==0){index=0;}



// apply the state of plasma
plasmaset();


// apply the state of speed

speedset();
}

