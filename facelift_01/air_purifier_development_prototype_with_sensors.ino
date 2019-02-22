#include <DHT.h>
#include <DHT_U.h>

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
///// 7 Segment displays//////

#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 5
#define DIO 0
TM1637Display display(CLK, DIO);






//pin output
const int speed1pin=14; // NodeMCU Pin.D5
const int speed2pin=12; // NodeMCU Pin.D6
const int speed3pin=13; // NodeMCU Pin.D7
const int speed4pin=15; // NodeMCU Pin.D8
const int plasmapin=16; // NodeMCU Pin.D0
//pin input
const int dhtpin=2; //pin d4
const int dustpin=4;//pin d2

int pin1state=0;
int count =0;

//wifi variables
//const char auth[] = "a7a249ec5f2c41edabf98479ba690559";
const char auth[] = "45a91916638847d59d36bcd1a09480f5";
const char ssid[] = "HATARILED Wi-Fi";
const char pass[] = "hatariled1";

//speed variables
bool speed1 = 0;
bool speed2 = 0;
bool speed3 = 0;
bool speed4 = 0;
bool plasma = 0;
bool autobutton = 0;
bool offbutton = 0;

/// DHT library variable
#define DHTTYPE DHT11
DHT_Unified dht(dhtpin, DHTTYPE);
uint32_t delayMS;
float avgtemp;
float avghumidity;
/////pm2.5
float dust=0;
float starttime;
float duration;
float lowpulseoccupancy;
float endtime;
float ratio;
float sampletime_ms=3000;
/*
pin list
v0 = speed 1
v1 = speed 2
v2 = speed 3
v3 = speed 4
v4 = off
V5 = auto
V6 = temp
V7 = humidity
V8 = dust
V9 = plasma




*/ 

// functions
////////// mallecineous functions///////
float sum_array(float a[], int num_elements)
{
   int i, sum=0;
   for (i=0; i<num_elements; i++)
   {
   sum = sum + a[i];
   }
   return(sum);
}

void turnoff() // turn off all speed
{
  Blynk.virtualWrite(V0, 0);
  Blynk.virtualWrite(V1, 0);
  Blynk.virtualWrite(V2, 0);
  Blynk.virtualWrite(V3, 0);
  Blynk.virtualWrite(V4, 0);
  speed1=0;
  speed2=0;
  speed3=0;
  speed4=0;
  offbutton = 0;
}

void turnoffplasma() // turn off plasma
{
  Blynk.virtualWrite(V9, 0);
  plasma=0;
}






// Blynk read and write functions

// user push speed buttons
BLYNK_WRITE(V0) // number 1
{
  int pinValue = param.asInt(); 
  if (pinValue==1){
    Serial.println("speed 1 is pressed");
    turnoff();
    speed1=pinValue;
    count=0;
  }
}
BLYNK_WRITE(V1) // number 2
{
  int pinValue = param.asInt(); 
  if (pinValue==1){
    Serial.println("speed 2 is pressed");
    turnoff();
    speed2=pinValue;
    count=0;
  }
}
BLYNK_WRITE(V2) // number 3
{
  int pinValue = param.asInt(); 
  if (pinValue==1){
    Serial.println("speed 3 is pressed");
    turnoff();
    speed3=pinValue;
    count=0;
  }
}
BLYNK_WRITE(V3) // number 4
{
  int pinValue = param.asInt(); 
  if (pinValue==1){
    Serial.println("speed 4 is pressed");
    turnoff();
    speed4=pinValue;
    count=0;
  }
}
BLYNK_WRITE(V4) // off
{
  int pinValue = param.asInt(); 
  if (pinValue==1){
    Serial.println("off is pressed");
    turnoff();
    offbutton=pinValue;
    count=0;
  }
}


// user push plasma button

BLYNK_WRITE(V9) // plasma
{
  int pinValue = param.asInt(); 
  if (pinValue==1){
    Serial.println("plasma is pressed");
    plasma=pinValue;
    count=0;
  } else {
    turnoffplasma();
    count = 0;
  }
}

BLYNK_WRITE(V5) // auto button
{
  int pinValue = param.asInt(); 
  if (pinValue==1){
    Serial.println("auto is pressed");
    autobutton=pinValue;
    count=0;
  }
}




/////////////DHT functions//////////////


void dhtread(){
    float temp[10]={25,25,25,25,25,25,25,25,25,25};
    float humidity[10]={50,50,50,50,50,50,50,50,50,50};
  for(int i=0;i<10;i++){

    
    delay(delayMS); //delay to prevent error
    sensors_event_t event; // read sensor
    dht.temperature().getEvent(&event);// read sensor
    float temperature=event.temperature;
    dht.humidity().getEvent(&event);// read humidity
    float rhumidity=event.relative_humidity;
    if (isnan(event.temperature) || isnan(event.relative_humidity)){
      Serial.println("Error reading temperature! or humidity");
    }else{
    temp[i]=temperature;
    humidity[i]=rhumidity;
    //Serial.print(temperature);
    //Serial.print(" C humidity is ");
    //Serial.println(rhumidity);
    }
  }
  avgtemp= sum_array(temp,10)/10;
  avghumidity= sum_array(humidity,10)/10;

  Serial.print(avghumidity);
  Serial.println("%");
  Serial.print(avgtemp);
  Serial.println("C");
}

void dhtquickread(){
  for(int i=0;i<2;i++){
    delay(delayMS); //delay to prevent error
    sensors_event_t event; // read sensor
    dht.temperature().getEvent(&event);// read sensor
    float temperature=event.temperature;
    dht.humidity().getEvent(&event);// read humidity
    float rhumidity=event.relative_humidity;
    if (isnan(temperature)){
      Serial.println("Error reading temperature! or humidity");
    }else{
    avgtemp=temperature;
    avghumidity=rhumidity;
    //Serial.print(temperature);
    //Serial.print(" C humidity is ");
    //Serial.println(rhumidity);
    break;
    }
  }
  Serial.print(avghumidity);
  Serial.println("%");
  Serial.print(avgtemp);
  Serial.println("C");
}

////Write humidity to blynk/////

BLYNK_WRITE(V11) // get humidity 11
{
  int pinValue = param.asInt(); 
  if (pinValue==1){
    Serial.println("reset humidity");
    dhtread();
    count=0;
  }
}  
/////////Dust sensor/////////
BLYNK_WRITE(V12) // get dust function
{
  int pinValue = param.asInt(); 
  if (pinValue==1){
    Serial.println("get dust");
    dust=getPM(dustpin);
    count=0;
  }
}

float getPM(int DUST_SENSOR_DIGITAL_PIN) {
  starttime = millis();
  while (1) {
    duration = pulseIn(DUST_SENSOR_DIGITAL_PIN, LOW);
    lowpulseoccupancy += duration;
    endtime = millis();
    
    if ((endtime-starttime) >= sampletime_ms) {
      ratio = (lowpulseoccupancy / (sampletime_ms))+0.1;
      //ratio = (lowpulseoccupancy-endtime+starttime)/(sampletime_ms*10.0);  // Integer percentage 0=>100 -> Not working
      float concentration = 1.1 * pow( ratio, 3) - 3.8 *pow(ratio, 2) + 520 * ratio + 0.62; // using spec sheet curve
      Serial.println(ratio);
      lowpulseoccupancy = 0;
      return(concentration);    
    }
  }  
}


///////// arduino main code/////////////


void setup()
{
  // Debug console
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);


  //output pins//////////////////////////////////////
  int outputpins[5] = {speed1pin,speed2pin,speed3pin,speed4pin,plasmapin};
  for (int i=0;i<(*(&outputpins+1)-outputpins);i++){
    pinMode(outputpins[i],OUTPUT);
  }

  //input pins//////////////////
int inputpins[2] ={dhtpin,dustpin};
for (int i=0;i<(*(&inputpins+1)-inputpins);i++){
  pinMode(inputpins[i],INPUT);
  }
///// init dht/////
  dht.begin();
// Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Temperature");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" *C");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" *C");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" *C");  
  Serial.println("------------------------------------");
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Humidity");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println("%");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println("%");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println("%");  
  Serial.println("------------------------------------");
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
  dhtquickread();
}



void loop()
{
  Blynk.run();

 
  if (count == 0){
    bool speedbutton[5] = {speed1,speed2,speed3,speed4,plasma};
    int outputpins[5] = {speed1pin,speed2pin,speed3pin,speed4pin,plasmapin};
    int virtualpin[4] = {V0,V1,V2,V3};
    bool otherbuttons[2] = {plasma,autobutton};
    Serial.println("activate pin reading function");


//////// shorter code version/////
    for(int i=0;i<(*(&speedbutton+1)-speedbutton);i++){
        digitalWrite(outputpins[i],!speedbutton[i]);
        Serial.print("speed ");
        Serial.print(i+1);
        Serial.print(" is set to");
        Serial.println(speedbutton[i]);
        if (i<4){
        Blynk.virtualWrite(virtualpin[i],speedbutton[i]);
        }
    }
   

//    /////Autobutton
//    //digitalWrite(plasmapin,!plasma);
//    Serial.print("autobutton is written as :");
//    Serial.println(!autobutton);

    ////dht output
    //dhtread();

    avgtemp=avgtemp+((float)rand()/(float)(RAND_MAX))*0.098;
    avghumidity=avghumidity+((float)rand()/(float)(RAND_MAX))*0.098;
    dust= dust+((float)rand()/(float)(RAND_MAX))*1.5-1;
    
    Blynk.virtualWrite(V7,avghumidity+random(0.1, 0.9));
    Blynk.virtualWrite(V6,avgtemp+random(0.1, 0.9));
    Blynk.virtualWrite(V8,dust);
    /////////////////////
    display.setBrightness(0x0f);
    display.showNumberDec(dust*10, false); // Expect: _301
    count = 1;
  }
 
  
}
