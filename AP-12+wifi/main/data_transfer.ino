
unsigned int sent=0;

void send_smart(){

 if(currenttime-sent>600){

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

     
   if (datar=='O'||datar=='s'||datar=='a'||datar=='t'||datar=='w'){
        
    
        if (datar=='O' ) {Bp=0;}
        if (datar=='s' ) {Bs=0;}
        if (datar=='a' ) {Ba=0;}
        if (datar=='t' ) {Bt=0;checkstate_in=1;}
        if (datar=='w' ) {set_wifi=0;Wi=1;}

        
      }
  }
}

 
