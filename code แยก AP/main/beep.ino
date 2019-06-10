
#include <TonePlayer.h> 
TonePlayer tone1 (TCCR1A, TCCR1B, OCR1AH, OCR1AL, TCNT1H, TCNT1L);  

/////////////////song definition////////////

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978





void beep(){
  if (currenttime-bwf>700&&wifi==1&&wfcount==0){
      bwf=currenttime;
      bnum++;
      tone1.tone (880);
      wfcount=1;
      }else if (currenttime-bwf>150&&bnum>0&&wfcount==1){
                bwf=currenttime;
                tone1.noTone();
                wfcount=0;
                }
     if (bnum==6){wifi=0;bnum=0;tone1.noTone();wfcount=0;}           

  
  if (beepvarB==1 && beepstarted==0){
    tone1.tone (1500);
    beeptime=currenttime;
    beepstarted=1;
  } else if (currenttime-beeptime>50 && beepstarted ==1){
    tone1.noTone();
    beepvarB=0;
    beepstarted=0;
  }

  if (beepvarS==1 && beepstartedS==0){
    tone1.tone (2000);
    beeptimeS=currenttime;
    beepstartedS=1;
  } else if (currenttime-beeptimeS>400 && beepstartedS ==1){
    tone1.noTone();
    beepvarS=0;
    beepstartedS=0;
  }

  
if (currenttime-soundtime>4&&beeppowervar>0){play++;soundtime=currenttime;}

if (beeppowervar==1&&play==25&&songindex==0){tone1.tone (1661);beeppowervar=2;}
if (beeppowervar==2&&play==50&&songindex==0){tone1.tone (1865);beeppowervar=3;}
if (beeppowervar==3&&play==75&&songindex==0){tone1.tone (1976);beeppowervar=4;}
if (beeppowervar==4&&play==100&&songindex==0){tone1.tone (2217);beeppowervar=5;}
if (beeppowervar==5&&play==125&&songindex==0){tone1.tone (2489);beeppowervar=6;}
if (beeppowervar==6&&play==190&&songindex==0){tone1.noTone ();beeppowervar=0;play=0;}

if (beeppowervar==1&&play==25&&songindex==1){tone1.tone (2300);beeppowervar=2;}
if (beeppowervar==2&&play==50&&songindex==1){tone1.tone (2093);beeppowervar=3;}
if (beeppowervar==3&&play==75&&songindex==1){tone1.tone (1760);beeppowervar=4;}
if (beeppowervar==4&&play==100&&songindex==1){tone1.tone (1480);beeppowervar=5;}
if (beeppowervar==5&&play==125&&songindex==1){tone1.tone (1319);beeppowervar=6;}
if (beeppowervar==6&&play==190&&songindex==1){tone1.noTone ();beeppowervar=0;play=0;}

}
