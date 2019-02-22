
int Bpow = A0;
int Bp;
int Lp;
int stateP = LOW;
int POW=13;

const int Bspeed = A1;
const int M1 =  7;
const int M2 =  8;
const int M3 =  9;
const int M4 =  10;

int Bstate;
int Lstate;
int stateS = LOW;
int i = 0; 

void setup() {
  pinMode(Bpow, INPUT);
  pinMode(POW, OUTPUT);
  
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT); 
  pinMode(M3, OUTPUT); 
  pinMode(M4, OUTPUT);       
  pinMode(Bspeed, INPUT);  
  Serial.begin(9600);   
}

void loop()
{
 // Serial.println(i);
  Bstate = digitalRead(Bspeed);
  Bp = digitalRead(Bpow);
  
 if ((Bp != Lp) && (Lp == HIGH))
    {  stateP=!stateP;
    digitalWrite(POW,stateP);
    i=1;
    delay(200);
    }
    Lp=!Bp;
    
 if(stateP==0){i=0;}
    
 if ((Bstate != Lstate) && (Lstate == HIGH)&&(stateP==1))
    {  
    stateS=!stateS;
    i=i+1;
    delay(200);
    }
    Lstate=!Bstate;

  switch (i) {
      case 0:
      digitalWrite(M4,HIGH);
      digitalWrite(M1,HIGH);  
      digitalWrite(M2,HIGH);
      digitalWrite(M3,HIGH);
      Serial.println("M1");
      break;
    case 1:
      digitalWrite(M1,LOW);   
      Serial.println("M1");
      break;
    case 2:
      digitalWrite(M2,LOW);   digitalWrite(M1,HIGH);
      Serial.println("M2");
      break;
    case 3:
      digitalWrite(M3,LOW);   digitalWrite(M2,HIGH);
      Serial.println("M3");
      break;
    case 4:
      digitalWrite(M4,LOW);   digitalWrite(M3,HIGH);
      Serial.println("M4");
      break;
    case 5:
    digitalWrite(M4,HIGH);
          i=1;
      break;
  }
}

