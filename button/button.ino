
/// pin definition

// input pins
const int Bspeed = 15;    // speed input pin
const int Bpow = 14;      //power button input pin
const int Bplasma = 16;   // plasma button input pin


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
bool Bp;               //power button state
bool Lp;               //previous power button state 
bool stateP = LOW;     //power output state

//plasma
bool Bpm;                  // plasma button state
bool Lpm;                  // previous plasma button state
bool statePM = LOW;        // plasma output state

//speed
bool Bs;                   // speed input state
bool Ls;                   // previous speed input state
bool stateS = LOW;         // speed state
unsigned short int i = 0;                // case counter


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
  }
  

}

void loop(){

 // read inputs
 // Serial.println(i);
  Bs      =  digitalRead(Bspeed);
  Bp      =  digitalRead(Bpow);
  Bpm     =  digitalRead(Bplasma);

 //apply read input to the output




 //apply power
 if ((Bp != Lp) && (Lp == 1)){  
     stateP=!stateP;
     digitalWrite(POW,stateP);
     Serial.print("Power is set to: ");
     Serial.println(stateP); 
     i=1;
     delay(400);

 }
      Lp=!Bp; 






// turn off the machine (everything)
 if(stateP==0){i=0;}



// apply the state of plasma
 if ((Bpm != Lpm) && (Lpm == 1)&&(stateP==1)){  
     statePM=!statePM;
     digitalWrite(PLASMA,statePM); 
     Serial.print("plasma is set to: ");
     Serial.println(statePM);
     delay(350);
     }
 Lpm=!Bpm; 


// apply the state of speed

 if ((Bs != Ls) && (Ls == HIGH)&&(stateP==1)){  
     stateS=!stateS;
     i=i+1;
     if(i>4){i=1;}
     Serial.print("Speed is set to: ");
     Serial.println(i);
     delay(350);}
     Ls=!Bs;

  switch (i) {
    case 0:
      digitalWrite(M4,1);
      digitalWrite(M1,1);  
      digitalWrite(M2,1);
      digitalWrite(M3,1);
      digitalWrite(PLASMA,1);
      break;
    case 1:
      digitalWrite(M1,LOW); digitalWrite(M4,HIGH);   
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
  }
}

