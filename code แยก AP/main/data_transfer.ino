

unsigned int sent=0;


void send_smart(){

 if(currenttime-sent>1000){

      DynamicJsonDocument jsonBuffer(JSON_OBJECT_SIZE(3) + 100);
      JsonObject root = jsonBuffer.to<JsonObject>();
      JsonObject state = root.createNestedObject("state");
      JsonObject state_desired = state.createNestedObject("desired");
    
    
      state_desired["power" ] = stateP;
      state_desired["speed"] = index;
      state_desired["timer"] = timeshow2;
      state_desired["auto"] = stateA;
      state_desired["dust"] = averagedust;

      char status_bord[measureJson(root) + 1];
      serializeJson(root, status_bord, sizeof(status_bord));
      
      NodeSerial.print(status_bord);
      NodeSerial.print("\n");


 
   sent=currenttime;
 }
 
}


void read_smart() {


  if(NodeSerial.available()>0){
     datar = NodeSerial.read();
     Serial.println(datar);
   if (datar=='O'||datar=='s'||datar=='a'||datar=='t'||datar=='w'){
        if (datar=='O' ) {Bp=0;}
        if (datar=='s' ) {Bs=0;}
        if (datar=='a' ) {Ba=0;}
        if (datar=='t' ) {Bt=0;checkstate_in=1;}
        if (datar=='w' ) {set_wifi=0;Wi=1;}

        NodeSerial.print("F");
        NodeSerial.print("\n");
      }
  }
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
    
 
