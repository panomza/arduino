int measurePin = A5;
int ledPower = 13;

unsigned int samplingTime = 280;
unsigned int deltaTime = 40;
unsigned int sleepTime = 9680;
const int numaverage = 50; ///number of values for taking average
float dust[numaverage];
unsigned int count=0;
float initialdust=20;
float t0;// time of last reading
float timer=200;// time between each reading


float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;


float readdust(){
  digitalWrite(ledPower,LOW);
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(measurePin);

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH);
  delayMicroseconds(sleepTime);

  calcVoltage = voMeasured*(5.0/1024);
  dustDensity = 170*calcVoltage-100;

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


void setup(){
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);
  for(int i=0;i<numaverage;i++){
    dust[i]=initialdust;
  }
  t0=millis();
}


void loop(){
  if(millis()-t0>timer){
    dust[count]=readdust();
    Serial.println(takeaverage(dust));
    
  
    ///// get index for the next reading
    if ((count>numaverage-2)){
      count =0;
    }else{
      count +=1;
    }
    t0=millis();
  }
  
}
