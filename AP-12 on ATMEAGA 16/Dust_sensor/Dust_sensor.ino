int measurePin = 19;
int ledPower = 12;

const int numaverage = 20; ///number of values for taking average
float dust[numaverage];

unsigned short int count;
float initialdust=20;
float averagedust=initialdust;

float t0;// time of last reading
float timer=500;// time between each reading

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

float readdust(){
  digitalWrite(ledPower,LOW);
  delayMicroseconds(280);
  voMeasured = analogRead(measurePin);
  delayMicroseconds(40);
  digitalWrite(ledPower,HIGH);
  delayMicroseconds(9680);

  calcVoltage = voMeasured*(5.0/1024);
  dustDensity = (40*calcVoltage-10);
  if ( dustDensity < 0)
  {
    dustDensity = 0.00;
  }
  return dustDensity;
}

float takeaverage(float input[]){
  
  float sum=0;
  for(int i = 0; i < int(numaverage) ; i++){
    sum+=input[i];
    //Serial.println(i);
    //Serial.println(input[i]);
  }
  return sum/numaverage;
}
void setup() {
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);
  for(int i=0;i<numaverage;i++){
  dust[i]=initialdust;
  }
}

void loopsensor_dust() {
    if(millis()-t0>timer){
      count++;
    dust[count]=readdust();
    Serial.print("Dust is :");
    averagedust=takeaverage(dust);
    Serial.println(averagedust);
      
    ///// get index for the next reading
    if ((count>numaverage)){
      count =0;
    }
    t0=millis();
  } 

}
