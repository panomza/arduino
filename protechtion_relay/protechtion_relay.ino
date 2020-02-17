#include <Wire.h>
#include "Adafruit_MCP23017.h"
Adafruit_MCP23017 mcp;


const int out600L = 4;
const int out600R = 5;
const int out100L = 2;
const int out100R = 3;

const int fan_control = 9;

const int out_HL = 17;

int readHL = 0;

void setup() {
  mcp.begin();
  Serial.begin(9600);
  
 pinMode(out600L,OUTPUT);
 pinMode(out600R,OUTPUT);
 pinMode(out100L,OUTPUT);
 pinMode(out100R,OUTPUT);
 pinMode(fan_control,OUTPUT);

 pinMode(out_HL,INPUT);


mcp.pinMode(0, OUTPUT);
mcp.pinMode(1, OUTPUT);
mcp.pinMode(2, OUTPUT);
mcp.pinMode(3, OUTPUT);
mcp.pinMode(4, OUTPUT);
mcp.pinMode(5, OUTPUT);
mcp.pinMode(6, OUTPUT);
mcp.pinMode(7, OUTPUT);
mcp.pinMode(8, OUTPUT);
mcp.pinMode(9, OUTPUT);
mcp.pinMode(10, OUTPUT);
mcp.pinMode(11, OUTPUT);
mcp.pinMode(12, OUTPUT);
mcp.pinMode(13, OUTPUT);
mcp.pinMode(14, OUTPUT);
mcp.pinMode(15, OUTPUT);
 
  digitalWrite(out600L,0);
  digitalWrite(out600R,0);
  digitalWrite(out100L,0);
  digitalWrite(out100R,0);


mcp.digitalWrite(0,1);
delay(200);
mcp.digitalWrite(0,0);
mcp.digitalWrite(4,1);
delay(200);
mcp.digitalWrite(4,0);
mcp.digitalWrite(11,1);
delay(200);
mcp.digitalWrite(11,0);
mcp.digitalWrite(15,1);
delay(200);
mcp.digitalWrite(15,0);
mcp.digitalWrite(0,1);

delay(200);
mcp.digitalWrite(0,0);
mcp.digitalWrite(4,1);
delay(200);
mcp.digitalWrite(4,0);
mcp.digitalWrite(11,1);
delay(200);
mcp.digitalWrite(11,0);
mcp.digitalWrite(15,1);
delay(200);
mcp.digitalWrite(15,0);
mcp.digitalWrite(0,1);

delay(200);
mcp.digitalWrite(0,0);
mcp.digitalWrite(4,1);
delay(200);
mcp.digitalWrite(4,0);
mcp.digitalWrite(11,1);
delay(200);
mcp.digitalWrite(11,0);
mcp.digitalWrite(15,1);
delay(200);
mcp.digitalWrite(15,0);

delay(200);
mcp.digitalWrite(0,1);mcp.digitalWrite(4,1);mcp.digitalWrite(11,1);mcp.digitalWrite(15,1);
delay(500);
mcp.digitalWrite(0,0);mcp.digitalWrite(4,0);mcp.digitalWrite(11,0);mcp.digitalWrite(15,0);
mcp.digitalWrite(1,1);mcp.digitalWrite(5,1);mcp.digitalWrite(10,1);mcp.digitalWrite(14,1);
delay(500);
mcp.digitalWrite(1,0);mcp.digitalWrite(5,0);mcp.digitalWrite(10,0);mcp.digitalWrite(14,0);
mcp.digitalWrite(2,1);mcp.digitalWrite(6,1);mcp.digitalWrite(9,1);mcp.digitalWrite(13,1);
delay(500);
mcp.digitalWrite(2,0);mcp.digitalWrite(6,0);mcp.digitalWrite(9,0);mcp.digitalWrite(13,0);
mcp.digitalWrite(3,1);mcp.digitalWrite(7,1);mcp.digitalWrite(8,1);mcp.digitalWrite(12,1);
delay(500);
mcp.digitalWrite(3,0);mcp.digitalWrite(7,0);mcp.digitalWrite(8,0);mcp.digitalWrite(12,0);

mcp.digitalWrite(0,1);mcp.digitalWrite(4,1);mcp.digitalWrite(11,1);mcp.digitalWrite(15,1);
delay(500);
mcp.digitalWrite(0,0);mcp.digitalWrite(4,0);mcp.digitalWrite(11,0);mcp.digitalWrite(15,0);
mcp.digitalWrite(1,1);mcp.digitalWrite(5,1);mcp.digitalWrite(10,1);mcp.digitalWrite(14,1);
delay(500);
mcp.digitalWrite(1,0);mcp.digitalWrite(5,0);mcp.digitalWrite(10,0);mcp.digitalWrite(14,0);
mcp.digitalWrite(2,1);mcp.digitalWrite(6,1);mcp.digitalWrite(9,1);mcp.digitalWrite(13,1);
delay(500);
mcp.digitalWrite(2,0);mcp.digitalWrite(6,0);mcp.digitalWrite(9,0);mcp.digitalWrite(13,0);
mcp.digitalWrite(3,1);mcp.digitalWrite(7,1);mcp.digitalWrite(8,1);mcp.digitalWrite(12,1);
delay(2000);
mcp.digitalWrite(3,0);mcp.digitalWrite(7,0);mcp.digitalWrite(8,0);mcp.digitalWrite(12,0);

mcp.digitalWrite(0,1);mcp.digitalWrite(4,1);mcp.digitalWrite(11,1);mcp.digitalWrite(15,1);
}

void loop() {
//
readHL = analogRead(out_HL);
Serial.println(readHL);

if (readHL>152){mcp.digitalWrite(5,1);}else{mcp.digitalWrite(5,0);}

  digitalWrite(out600L,1);
  digitalWrite(out600R,1);
  digitalWrite(out100L,1);
  digitalWrite(out100R,1);

  
  analogWrite(fan_control,255);
//  delay(3000); 
//  analogWrite(fan_control,155);
//  delay(3000);
//  analogWrite(fan_control,0);
//  

}
