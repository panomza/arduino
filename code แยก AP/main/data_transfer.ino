int trans=0;
int recive=0;
int sent=0;


void send_smart(){


 if(currenttime-sent>300){
      NodeSerial.print("d");
      NodeSerial.print(averagedust);  
      
      NodeSerial.print("x");
      NodeSerial.print(timedown);
      
      if(stateP==0&&sent==0){NodeSerial.print("O");}
      if(stateP==1&&sent==0){NodeSerial.print("F");} 

      
           sent=currenttime;
 }
}

void read_smart() {
  
 datar = NodeSerial.read();
 
    if (datar=='O' && recive==0) {Bp=0;recive=1;}else{recive=0;}
    if (datar=='s' && recive==0) {Bs=0;recive=1;}else{recive=0;}
    if (datar=='a' && recive==0) {Ba=0;recive=1;}else{recive=0;}
    if (datar=='t' && recive==0) {Bt=0;recive=1;}else{recive=0;}
 
  
}

 
