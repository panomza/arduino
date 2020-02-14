int i = 0;
int f = 0;

float f_data = 567.89;

//#include <SoftwareSerial.h>
//
//
//SoftwareSerial NanoSerial(11, 12); // RX | TX

void setup()

{  

  pinMode(11,OUTPUT);

  pinMode(12,OUTPUT);

  pinMode(7,OUTPUT);

  pinMode(14,INPUT);
  pinMode(15,INPUT);

  Serial.begin(9600);

//  NanoSerial.begin(57600);           

}

void loop() {
i=digitalRead(14);
f=digitalRead(15);

if(i==0){digitalWrite(11,1);}else{digitalWrite(11,0);}
if(f==0){digitalWrite(12,1);}else{digitalWrite(12,0);}

}
