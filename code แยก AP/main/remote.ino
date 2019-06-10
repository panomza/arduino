unsigned int last = 0;
unsigned int currentMillis = 0;

void Remote(){

currentMillis = millis();
    
    if (irrecv.decode(&results)) {
         if (currentMillis - last > 50) {
           if ( (results.value != 0xFFFFFFFF) && (results.value != 0x00) ) {
              for (int val=0;val<OUTPUT_COUNT;val++) {       
                  if ( results.value == remote_key[val] )  {
                    
                    timedim=brightdim;
                    
                    status1[val]=!status1[val];
                    switch (val) {
                      case 0: //on-off
                        Bp=0;
                        break;
                      case 1: // speed
                        Bs=0;
                        break;
                      case 2: // plasma
                       
                        break;
                      case 3: // timer
                        Bt=0;
                        checkstate_in=1;
                        break;
                      case 4: // ionizer
                      Ba=0;
                        break;
                    }
                  }       
              }
           }

        last = currentMillis;      // record time
        irrecv.resume(); // Receive the next value

    }
  }
    if (currentMillis - last>500){
      for (int i=0;i<OUTPUT_COUNT;i++){
          if (status1[i]){
           status1[i]=0;
           switch (i) {
                      case 0: //on-off
                        Bp=1;
                        break;
                      case 1: // speed
                        Bs=1;
                        break;
                      case 2: // plasma
                        
                        break;
                      case 3: // timer
                        Bt=1;
                        checkstate_in=0;
                        break;
                      case 4: // ionizer
                        Ba=1;
                        break;
           }
        }
      }
    }
}
