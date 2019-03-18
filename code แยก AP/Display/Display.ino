#include <Arduino.h>
#include <TM1637Display.h>
#define CLK 5
#define DIO 4
TM1637Display display(CLK, DIO);
unsigned short int timedisplay=1000;
unsigned short int TD=0;

void setup() {
  // put your setup code here, to run once:

}
void Display(){
  unsigned short int td = millis();
  if(td-TD>timedisplay)
  {
    TD=td;
     display.setBrightness(0x0f);
     display.showNumberDec(takeaverage(dust), false);
  }
}

void loop() {
  Display();
}
