#include <Arduino.h>
#include <TM1637Display.h>
#define CLK 5
#define DIO 6
TM1637Display display(CLK, DIO);
unsigned int TD=0;
unsigned int td=0;
unsigned int ST=0;
unsigned int ST_count=0;
unsigned int SW_display=0;
unsigned int sw=0;
unsigned int sw_count=0;
unsigned int show=0;


void Display(){
 td = currenttime;
 
  if (td-sw>1000&&sw_count<2){
    sw=td;
    SW_display++;
    }
    
  if (Bt==0){sw_count=1;SW_display=0;}
  if (timedown==5){sw_count=1;SW_display=0;}
      if (sw_count==0){      
          if(SW_display>=5&&Settime>0){SW_display=0; sw_count=1;}
          show=0;
      }       
      if (sw_count==1){    
          if(SW_display>=5){SW_display=0; sw_count=0;}
          if(SW_display>=5&&Settime==0){sw_count=3;}   
         show=1;
      }

  
  switch (show){
    case 0:
     if(td-TD>2000){
       TD=td;
       display.setBrightness(7);
       display.showNumberDec(averagedust,false,2,1);
     send_smart();
      }
      break;

    case 1:
       if(td-ST>300 && ST_count==0){
       ST=td;
       display.setBrightness(0);
       ST_count=1;
       }else 
       if (td-ST>300 && ST_count==1){
        display.setBrightness(7);
        ST=td;
        ST_count=0;
        }
       
       display.showNumberDec(timedown, false,2,1);
      break;
  }
}
