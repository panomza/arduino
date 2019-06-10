
unsigned int sent=0;



void send_smart(){

 if(currenttime-sent>400){

      NodeSerial.print("P");NodeSerial.print(stateP);NodeSerial.print("\n");
      NodeSerial.print("S");NodeSerial.print(index);NodeSerial.print("\n");
      NodeSerial.print("T");NodeSerial.print(timeshow2);NodeSerial.print("\n");
      NodeSerial.print("A");NodeSerial.print(stateA);NodeSerial.print("\n");
      NodeSerial.print("d");NodeSerial.print(averagedust);NodeSerial.print("\n");

 
   sent=currenttime;
 }
}



void read_smart() {

  if(NodeSerial.available()>0){
    datar = NodeSerial.read();

    if (datar=='O' ) {Bp=0;}
    if (datar=='s' ) {Bs=0;}
    if (datar=='a' ) {Ba=0;}
    if (datar=='t' ) {Bt=0;checkstate_in=1;}
    if (datar=='w' ) {set_wifi=0;Wi=1;}
  }
}

 
