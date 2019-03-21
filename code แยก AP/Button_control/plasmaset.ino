void plasmaset(){
    Bpm     =  digitalRead(Bplasma);
    if ((Bpm != Lpm) && (stateP == 0) && (millis()-plasmat0 > buttondelay) && (plasmacount ==0)){
    statePM=!statePM;
    digitalWrite(PLASMA,statePM);
    Serial.print("Plasma is set to: ");
    Serial.println(statePM); 
    Lpm=Bpm;
    plasmat0 = millis();
    plasmacount =1;
    }
   else if ((Bpm != Lpm) && (Bpm == 1)&& (millis()-plasmat0 > buttondelay)){
    Lpm=Bpm;
    plasmacount = 0;
  }
}
