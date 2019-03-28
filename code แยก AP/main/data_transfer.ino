

float lastsent=0;
float lastread=0;
short int count_data =0;

void send_smart(){
  
  NodeSerial.print("<");
  NodeSerial.print(datasent);          
  NodeSerial.print(">");


}

void read_smart() {
datar = NodeSerial.read();

    if (datar=='P') {
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

//void rundata()
//{
//  if (data==1){Bp=0;Serial.println("Bp trig");}else{Bp=1;}
//  if (data==2){Bs=0;Serial.println("Bs trig");}else{Bs=1;}
//  if (data==3){Bpm=0;Serial.println("Bpm trig");}else{Bs=1;}
//  if (data==4){Bt=0;Serial.println("Bp trig");}else{Bs=1;} 
//  if (data==5){Ba=0;Serial.println("Bp trig");}else{Bs=1;}
//
}

 
