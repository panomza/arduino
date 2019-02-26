#include <IRremote.h>

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);
decode_results results;

#define OUTPUT_COUNT 5

unsigned long last = millis();

long remote_key[]={0xDF40BF,0xDF609F,0xDF48B7,0xDF50AF,0xDF708F};

const byte outputPins[OUTPUT_COUNT] = {2, 3, 4, 5,6};

bool status1[5] = {0,0,0,0,0};

struct keypad {
  boolean state;
};

keypad output[OUTPUT_COUNT];

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver

  for (int i=0;i<OUTPUT_COUNT;i++) {
       pinMode(outputPins[i], OUTPUT);
       output[i].state = 0;
   }
}

void loop() {
    unsigned long currentMillis = millis();
    if (irrecv.decode(&results)) {
         if (currentMillis - last > 50) {

           if ( (results.value != 0xFFFFFFFF) && (results.value != 0x00) ) {
              for (int val=0;val<OUTPUT_COUNT;val++) {       
                  if ( results.value == remote_key[val] )  {

                    status1[val]=!status1[val];
  /*
                      if (output[val].state==0) {
                          Serial.print ("ch[");
                          Serial.print(val);
                          Serial.println("] ON");
                          output[val].state=1;
                      } else {                      
                          output[val].state=0;
                          Serial.print ("ch[");
                          Serial.print(val);
                          Serial.println("] OFF");                        
                      }
  */
  
                  }       
              }
           }

           for (int i=0;i<OUTPUT_COUNT;i++)
               //digitalWrite(outputPins[i], output[i].state);
               digitalWrite(outputPins[i], status1[i]);
  
           }

        last = currentMillis;      // record time
        irrecv.resume(); // Receive the next value

    }


    if (millis()-last>1000){
      for (int i=0;i<OUTPUT_COUNT;i++){
        if (status1[i]){
          status1[i]=0;
          digitalWrite(outputPins[i], status1[i]);
        }
      }
    }
    
    
}

