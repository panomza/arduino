int trans=0;

void send_smart(){
  
  NodeSerial.print("d");
  NodeSerial.print(averagedust);          
}

void read_smart() {

if(currenttime-trans>100){
  datar = NodeSerial.read();
    if (datar=='O') {
       Serial.println("ON OFF");
       Bp=0; 
    } else{Bp=1;}
    if (datar=='s') {
       Serial.println("Speed"); 
       Bs=0;
    } else{Bs=1;}
    if (datar=='p') {
       Serial.println("Plasma"); 
       Bpm=0;
    }else{Bpm=1;}
    if (datar=='a') {
       Serial.println("Auto"); 
       Ba=0;
    }else{Ba=1;}
  trans=currenttime;
}
}

 
