#include <Arduino.h>
#include <TM1637Display.h>
#define CLK 3
#define DIO 2
TM1637Display display(CLK, DIO);
unsigned int TD=0;
unsigned int td=0;
unsigned int ST=0;
unsigned int sw=0;
byte SW_display=0;
byte sw_count=0;
byte show=0;
bool ST_count=0;

void Display(){
  
 td = currenttime;
 
  if (td-sw>1000&&sw_count<2){
    sw=td;
    SW_display++;
    checkstate_in=0;
    }
    
  if (buttoncount1>0 || checkstate_in==1){sw_count=1;SW_display=0;}
  
  if (timedown==5){sw_count=1;SW_display=0;}
  
      if (sw_count==0){      
          if(SW_display>=10&&Settime>0){SW_display=0; sw_count=1;display.clear();}
          show=0;
      }       
      if (sw_count==1){    
          if(SW_display>=5){SW_display=0; sw_count=0;display.clear();}
          if(SW_display>=5&&Settime==0){sw_count=3;}   
         show=1;
      }

  
  switch (show){
    case 0:
     if(td-TD>1000){
       display.showNumberDec(averagedust,false);
       TD=td;   
      }
       display.setBrightness(bright7);
      break;

    case 1:
    
     if (td-ST>700 && ST_count==0){
        ST=td;
        display.setBrightness(0);
        ST_count=1;
        }else 
       
     if (td-ST>300 && ST_count==1){
        display.setBrightness(bright7);
        ST=td;
        ST_count=0;
        }
        display.showNumberDec(timeshow2*100,true);
      break;
  }
}
