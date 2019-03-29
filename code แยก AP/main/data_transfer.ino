

float lastsent=0;
float lastread=0;
short int count_data =0;

void send_smart(){
  
  NodeSerial.print("d");
  NodeSerial.print(averagedust);          



}

void read_smart() {
datar = NodeSerial.read();

    if (datar=='O') {
       Serial.print(datar);
       Serial.println("ON OFF");
       Bp=0; 
    } else{Bp=1;}
    if (datar=='s') {
       Serial.print(datar);
       Serial.println("Speed"); 
       Bs=0;
    } else{Bs=1;}
    if (datar=='p') {
       Serial.print(datar);
       Serial.println("Plasma"); 
       Bpm=0;
    }else{Bpm=1;}
    if (datar=='a') {
       Serial.print(datar);
       Serial.println("Auto"); 
       Ba=0;
    }else{Ba=1;}

}

 
