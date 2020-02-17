//#include <Arduino.h>
#include <TM1637Display.h>
char text;
 int g=0;
// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3

TM1637Display display(CLK, DIO);

const short int v1 = 14;
unsigned long int in;
unsigned long int pwmA = 0; // 50% duty (0-320 = 0-100% duty cycle)
int pwmB = 0; // 10% duty (0-320 = 0-100% duty cycle)



void setup() {
  
  pinMode(13, OUTPUT);  //pwmA
  pinMode(12, OUTPUT); //pwmB
  pinMode(v1, INPUT); 
  Serial.begin(9600);
  
//  pinMode(3, OUTPUT);  //pwmC
//  pinMode(11, OUTPUT); //pwmD
  
}

void PWM(){
  
  TCCR1A = 0;            //clear timer registers
  TCCR1B = 0;
  TCNT1 = 0;

  TCCR1B |= _BV(CS10);   //no prescaler
  ICR1 =160;            //PWM mode counts up 320 then down 320 counts (25kHz)
 

  OCR1A = 80;          //0-320 = 0-100% duty cycle
  TCCR1A |= _BV(COM1A1); //output A clear rising/set falling

  OCR1B = 150;          //0-320 = 0-100% duty cycle
  TCCR1A |= _BV(COM1B1); //output B clear rising/set falling

  TCCR1B |= _BV(WGM13);  //PWM mode with ICR1 Mode 10
  TCCR1A |= _BV(WGM11);  //WGM13:WGM10 set 1010

//  TCCR2A = 0;            //clear timer registers
//  TCCR2B = 0;
//  TCNT2 = 0;
//
//  TCCR2B |= _BV(CS10);   //no prescaler
//   ICR2 = 320;            //PWM mode counts up 320 then down 320 counts (25kHz)
//
// 
//  OCR2A = pwmC;          //0-320 = 0-100% duty cycle
//  TCCR2A |= _BV(COM1A1); //output A clear rising/set falling
//
//  OCR2B = pwmD;          //0-320 = 0-100% duty cycle
//  TCCR2A |= _BV(COM1B1); //output B clear rising/set falling
//
//  TCCR2B |= _BV(WGM13);  //PWM mode with ICR1 Mode 10
//  TCCR2A |= _BV(WGM11);  //WGM13:WGM10 set 1010
}

void loop() {

  PWM();

  if(Serial.available()>0){
    text=Serial.read();
   
    Serial.println(text);

    if(text=='1'){g=500;}
    if(text=='2'){g=1000;}
    if(text=='3'){g=2000;}
    if(text=='4'){g=3000;}
    
    
  }
  
//  in = analogRead(v1);
  pwmA =g; 


//  Serial.println(pwmA);
//  display.setBrightness(0x0f);
//  display.showNumberDec(in, false); // Expect: ___0
  }
