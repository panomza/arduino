

short int t0;         // time of last reading
short int timer=100;  // time between each reading

float voMeasured = 0;
float calcVoltage = 0;
unsigned int dustDensity = 0;


float readdust(){
  digitalWrite(ledPower,0);
  delayMicroseconds(280);
  voMeasured = analogRead(measurePin);
  delayMicroseconds(40);
  digitalWrite(ledPower,1);
  delayMicroseconds(9680);

  calcVoltage = voMeasured*(6.72/1024);
  
  dustDensity = (((calcVoltage)/0.51)*100);
  if ( dustDensity < 0)
  {
    dustDensity = 0.00;
  }
return dustDensity;
}

int takeaverage(int input[]){
  
  int sum=0;
  for(int i = 0; i < int(numaverage) ; i++){
    sum+=input[i];
  }
  return sum/numaverage;
}

void sensor_dust() {

    if(averagedust>=1000){averagedust=999;} 
    
    if(currenttime-t0>timer){
      count++;
      dust[count]=readdust();
      averagedust=takeaverage(dust);

    ///// get index for the next reading
    if ((count>numaverage)){
      count =0;
    }
    t0=currenttime;
  } 

}
