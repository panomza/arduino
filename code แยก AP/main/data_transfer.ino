int trans=0;

void send_smart(){
  
  NodeSerial.print("d");
  NodeSerial.print(averagedust);          
}

void read_smart() {

if(currenttime-trans>50){

  datar = NodeSerial.read();
    if (datar=='O') {
       Bp=0; 
    } else{Bp=1;}
    if (datar=='s') {
       Bs=0;
    } else{Bs=1;}
    if (datar=='p') {
       Bpm=0;
    }else{Bpm=1;}
    if (datar=='a') {
       Ba=0;
    }else{Ba=1;}
  trans=currenttime;
}
}

 
