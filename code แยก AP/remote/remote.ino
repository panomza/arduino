void Remote(){
    unsigned long currentMillis = millis();
    if (irrecv.decode(&results)) {
         if (currentMillis - last > 50) {

           if ( (results.value != 0xFFFFFFFF) && (results.value != 0x00) ) {
              for (int val=0;val<OUTPUT_COUNT;val++) {       
                  if ( results.value == remote_key[val] )  {
                    Serial.println("remote button is pressed");
                    status1[val]=!status1[val];
                    switch (val) {
                      case 0: //on-off
                        Bp=0;
                        break;
                      case 1: // speed
                        Bs=0;
                        break;
                      case 2: // plasma
                        Bpm=0;
                        break;
                      case 3: // timer
                        break;
                      case 4: // ionizer
                        break;
                    }
                  }       
              }
           }

           for (int i=0;i<OUTPUT_COUNT;i++){
               //digitalWrite(outputPins[i], output[i].state);
//               digitalWrite(outputPins[i], status1[i]);  
           }

        last = currentMillis;      // record time
        irrecv.resume(); // Receive the next value

    }
    }
    if (millis()-last>300){
      for (int i=0;i<OUTPUT_COUNT;i++){
        if (status1[i]){
         status1[i]=0;
         Serial.println("switch back to normal");
         switch (i) {
                      case 0: //on-off
                        Bp=1;
                        break;
                      case 1: // speed
                        Bs=1;
                        break;
                      case 2: // plasma
                        Bpm=1;
                        break;
                      case 3: // timer
                        break;
                      case 4: // ionizer
                        break;
           }
        }
      }
    }
}
