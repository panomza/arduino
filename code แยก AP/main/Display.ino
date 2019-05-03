#include <Arduino.h>
#include <TM1637Display.h>
#define CLK 5
#define DIO 4
TM1637Display display(CLK, DIO);
unsigned short int timedisplay=1000;
unsigned short int TD=0;
unsigned short int td=0;
unsigned int SW_display=0;
unsigned int sw=0;
unsigned int sw_count=0;


void Display(){
 td = millis();
 SW_display = millis();

  
  if (SW_display-sw>5000 && sw_count==0){
      sw=SW_display;
      sw_count=1;
      
     if(td-TD>timedisplay){
       TD=td;
       display.setBrightness(7);
       display.showNumberDec(averagedust, false);
//     send_smart();
      }
      
  } else 
  
  if (SW_display-sw>10000 && sw_count==1){
   sw=SW_display;
   sw_count=0;
   display.showNumberDec(timedown, false);
  }
}
