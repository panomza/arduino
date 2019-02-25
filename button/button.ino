
/// pin definition

// input pins
const int Bspeed = A1;    // speed input pin
const int Bpow = A0;      //power button input pin
const int Bplasma = A2;   // plasma button input pin


//output pins

const int POW=13;         //power output pin
const int PLASMA=6;       // plasma button output pin
const int M1 =  7;        // motor output pin
const int M2 =  8;        // motor output pin
const int M3 =  9;        // motor output pin
const int M4 =  10;       // motor output pin
const int BUZ = 4;        // buzzer output pin



// state variables

//power
int Bp;               //power button state
int Lp;               //previous power button state 
int stateP = LOW;     //power output state

//plasma
int Bpm;                  // plasma button state
int Lpm;                  // previous plasma button state
int statePM = LOW;        // plasma output state

//speed
int Bs;                   // speed input state
int Ls;                   // previous speed input state
int stateS = LOW;         // speed state
int i = 0;                // case counter


void setup() {
  String inputnames = {
    
    }
  int inputpins={
    
    }
  String outputnames={
    
  }
  int outputpins = {
    
  }
  pinMode(Bplasma, INPUT);
  pinMode(POW, OUTPUT);

  pinMode(Bpow, INPUT);
  pinMode(PLASMA, OUTPUT);
  
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT); 
  pinMode(M3, OUTPUT); 
  pinMode(M4, OUTPUT);       
  pinMode(Bspeed, INPUT);  
  Serial.begin(9600);   

  pinMode(BUZ,OUTPUT);
}

void loop(){
 // Serial.println(i);
  Bs      =  digitalRead(Bspeed);
  Bp      =  digitalRead(Bpow);
  Bpm     =  digitalRead(Bplasma);
  
 if ((Bp != Lp) && (Lp == HIGH)){  
     stateP=!stateP;
     digitalWrite(POW,stateP); 
     i=1;delay(400); }
     Lp=!Bp; 
  
 if(stateP==0){i=0;}

 if ((Bpm != Lpm) && (Lpm == HIGH)&&(stateP==1)){  
     statePM=!statePM;
     digitalWrite(PLASMA,statePM); 
     delay(350);}
     Lpm=!Bpm; 
    
 if ((Bs != Ls) && (Ls == HIGH)&&(stateP==1)){  
     stateS=!stateS;
     i=i+1;
     delay(350);}
     Ls=!Bs;

  switch (i) {
    case 0:
      digitalWrite(M4,HIGH);
      digitalWrite(M1,HIGH);  
      digitalWrite(M2,HIGH);
      digitalWrite(M3,HIGH);
      digitalWrite(PLASMA,HIGH);
      break;
    case 1:
      digitalWrite(M1,LOW);   
     // Serial.println("M1");
      break;
    case 2:
      digitalWrite(M2,LOW);   digitalWrite(M1,HIGH);
     // Serial.println("M2");
      break;
    case 3:
      digitalWrite(M3,LOW);   digitalWrite(M2,HIGH);
     // Serial.println("M3");
      break;
    case 4:
      digitalWrite(M4,LOW);   digitalWrite(M3,HIGH);
     // Serial.println("M4");
      break;
    case 5:
    digitalWrite(M4,HIGH);
    i=1;
      break;
  }
}

