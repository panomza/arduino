float lastsent=0;
float lastread=0;
short int count_data =0;

void send_smart(){
  
  NodeSerial.print("<");
  NodeSerial.print(datasent);          
  NodeSerial.print(">");


}

void read_smart() {
//char datar = NodeSerial.read();// read from NodeSerial
//char datar = Serial.read();// for debugging


recvBytesWithStartEndMarkers();// recieve data
applyNewData();// parse data

//    if (datar=='P') {
//       Serial.print(datar);
//       Serial.println("ON OFF");
//       Bp=0; 
//    } else{Bp=1;}
//    if (datar=='s') {
//       Serial.print(datar);
//       Serial.println("Speed"); 
//       Bs=0;
//    } else{Bs=1;}
//    if (datar=='p') {
//       Serial.print(datar);
//       Serial.println("Plasma"); 
//       Bpm=0;
//    }else{Bpm=1;}

//void rundata()
//{
//  if (data==1){Bp=0;Serial.println("Bp trig");}else{Bp=1;}
//  if (data==2){Bs=0;Serial.println("Bs trig");}else{Bs=1;}
//  if (data==3){Bpm=0;Serial.println("Bpm trig");}else{Bs=1;}
//  if (data==4){Bt=0;Serial.println("Bp trig");}else{Bs=1;} 
//  if (data==5){Ba=0;Serial.println("Bp trig");}else{Bs=1;}
//
}



// Example 6 - Receiving binary data

const byte numBytes = 32;
byte receivedBytes[numBytes];
byte numReceived = 0;

boolean newData = false;



void recvBytesWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    byte startMarker = 0x3C;
    byte endMarker = 0x3E;
    byte rb;
   

    while (Serial.available() > 0 && newData == false) {
        rb = Serial.read();

        if (recvInProgress == true) {
            if (rb != endMarker) {
                receivedBytes[ndx] = rb;
                ndx++;
                if (ndx >= numBytes) {
                    ndx = numBytes - 1;
                }
            }
            else {
                receivedBytes[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                numReceived = ndx;  // save the number for use when printing
                ndx = 0;
                newData = true;
            }
        }

        else if (rb == startMarker) {
            recvInProgress = true;
        }
    }
}

void applyNewData() {
    if (newData == true) {
        Serial.println("Data is in: ");
        for (byte n = 0; n < numReceived; n+=2) {
          switch(receivedBytes[n]){
            case 'P' : {
              Serial.print("Power");
              Serial.println(receivedBytes[n+1]>'0'&&receivedBytes[n+1]<'2');
              Bp= receivedBytes[n+1]-'0';
              Serial.println(Bp);
              break;
            }
            case 'p' : {
              Serial.print("plasma");
              Serial.println(receivedBytes[n+1]>'0'&&receivedBytes[n+1]<'2');
              break;
            }
            case 's' : {
              Serial.print("speed");
              if (receivedBytes[n+1]-'0'<5&&receivedBytes[n+1]-'0'>=0){
                Serial.println(receivedBytes[n+1]-'0');
              }
                else{
                  Serial.println("error value of speed");
              }

              break;
            }
          }
        }
        Serial.println();
        newData = false;
    }
}
    
 
