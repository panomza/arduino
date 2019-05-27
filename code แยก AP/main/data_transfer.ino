unsigned int trans=0;
unsigned int recive=0;
unsigned int sent=0;
unsigned int datasent=0;
char datar;


void send_smart(){


 if(currenttime-sent>400){

      NodeSerial.print("P");NodeSerial.print(stateP);NodeSerial.print("\n");
      NodeSerial.print("S");NodeSerial.print(index);NodeSerial.print("\n");
      NodeSerial.print("T");NodeSerial.print(timedown);NodeSerial.print("\n");
      NodeSerial.print("A");NodeSerial.print(stateA);NodeSerial.print("\n");
      NodeSerial.print("d");NodeSerial.print(averagedust);NodeSerial.print("\n");
 
   sent=currenttime;
 }
}

void read_smart() {
  
  while(NodeSerial.available()>0){
    
  datar = NodeSerial.read();
  
    if (datar=='O' ) {Bp=0;}
    if (datar=='s' ) {Bs=0;}
    if (datar=='a' ) {Ba=0;}
    if (datar=='t' ) {Bt=0;}
  }
  
}

 
