#include <Arduino.h>
#include <TM1637Display.h>
#define CLK 11
#define DIO 12
TM1637Display display(CLK, DIO);
float sensorPin = A1; 
float light = 0;
unsigned short int timedisplay=1000;
unsigned short int TD=0;

void setup()
{
  pinMode(3,INPUT);
  Serial.begin(9600);
}

void loop()
{
  light = analogRead(sensorPin);
  unsigned short int td = millis();
  if(td-TD>timedisplay)
  {
    TD=td;
     display.setBrightness(0x0f);
     display.showNumberDec(light, false);
  }
}
