
const int Bpow = A0;
const int POW=13;
int Bp;
int Lp;
int stateP = LOW;


const int Bplasma = A2;
const int PLASMA=6;
int Bpm;
int Lpm;
int statePM = LOW;


const int Bspeed = A1;
const int M1 =  7;
const int M2 =  8;
const int M3 =  9;
const int M4 =  10;

int Bs;
int Ls;
int stateS = LOW;
int i = 0; 

int BUZ = 4; 

void setup() {
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

