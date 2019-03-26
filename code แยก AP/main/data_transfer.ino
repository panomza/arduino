

float lastsent=0;
float lastread=0;
short int count_data =0;
    char autoB;
    bool plasma=0;
    bool speed1=0;
    bool speed2=0;
    bool speed3=0;
    bool speed4=0;
 int data;
    
void send_smart(){
  
  NodeSerial.print("<");
  NodeSerial.print(autoB);          NodeSerial.print("  ");
  NodeSerial.print(plasma);        NodeSerial.print("  ");
  NodeSerial.print(speed1);        NodeSerial.print("  ");
  NodeSerial.print(speed2);        NodeSerial.print("  ");
  NodeSerial.print(speed3);        NodeSerial.print("  ");
  NodeSerial.print(speed4);        NodeSerial.print("\n");

}

void read_smart() {
 
    if (NodeSerial.read()=='<'&& currenttime-lastread>50) {
     
      data = NodeSerial.read(); 
     while (data != '>' && data ==-1){
      
       Serial.println(data);
        switch(data)
       {
          case ('a') : 
            autoB      = NodeSerial.parseInt(); 
           Serial.println("auto");
            break;
         case ('plasma') : 
            plasma     = NodeSerial.parseInt();
            break;         
         case ('speed1') : 
           speed1     = NodeSerial.parseInt();
           break; 
          case ('speed2') : 
            speed2     = NodeSerial.parseInt();
            break;   
          case ('speed3') : 
            speed3     = NodeSerial.parseInt();
            break; 
          case ('speed4') : 
           speed4     = NodeSerial.parseInt();
           break; 
      }
      data = NodeSerial.read(); 
  }     
         

//          
//          Serial.print("speed1");      Serial.print(" : "); Serial.print(speed1);
//          Serial.print("\tspeed2");      Serial.print(" : "); Serial.print(speed2);
//          Serial.print("\tspeed3");      Serial.print(" : "); Serial.print(speed3);
//          Serial.print("\tspeed4");      Serial.print(" : "); Serial.print(speed4);
//          Serial.print("\tplasma");    Serial.print(" : "); Serial.print(plasma);
//          Serial.print("\tAuto");      Serial.print(" : "); Serial.println(autoB); 
          lastread=currenttime;
          send_smart(); 
        
    } 
    
} 

//void rundata(){
//    if(AutoB==1&&count_data==0){ Ba=0; count_data=1;Serial.println("auto data ");}  else{Ba=1;  count_data=0;}
//    if(plasma==1&&count_data==0){ Bpm=0; count_data=1;Serial.println("plasma data ");}  else{Bpm=1;  count_data=0;}
//    if(speed1==1&&count_data==0){ index=1;Serial.println("speed1 data ");}  
//    if(speed2==1&&count_data==0){ index=2;Serial.println("speed2 data ");}  
//    if(speed3==1&&count_data==0){ index=3;Serial.println("speed3 data ");}  
//    if(speed4==1&&count_data==0){ index=4;Serial.println("speed4 data ");} 
// }
 
