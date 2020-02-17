

byte count_filter = 0;

unsigned int trig_filter = 0;


void filter(){
  
  if (stateP==1){count_filter=0; min_filter=0;}
  
  if (currenttime-trig_filter>1000 && stateP==0){
      count_filter++;
      if(count_filter==60){
         count_filter=0;
         min_filter++;
         
         if(min_filter==30){ EEPROM.put(0, time_update);}
         
//         Serial.println(time_update);
      }  
    trig_filter=currenttime;   
    
    time_update = time_filter + min_filter; 
  }



    if (time_update==4000){alarm = 27;}else{alarm = 26;}



  if ((Bf != Lf) && (Bf == 0)&& (currenttime-filter0 > buttondelay)&&filtercount==0 && stateP==0){  
     Lf=Bf;
     filtercount=1;
     filter0=currenttime;      // get the current time
     beepvarB=1;
     time_update=0;
     min_filter=0;
     EEPROM.put(0, 0);

 }
   else if ((Bf != Lf) && (Bf == 1)&& (currenttime-filter0 > buttondelay)&&filtercount==1 && stateP==0){
      Lf=Bf;
      filtercount=0;
      time_filter = EEPROM.get(0,time_update);
      Serial.println(time_filter);
  }
}
