#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float Temp ;
float Humi ;
float timer=500;
float t0;


void setup() {
  dht.begin();
}

void loop() {
   float h = dht.readHumidity();
   float t = dht.readTemperature();
   Temp = t;
   Humi = h;
   

   if(millis()-t0>timer){
    t0=millis();
   Serial.print("\tHumidity: "); 
   Serial.print(h);
   Serial.print(" %\t");
   Serial.print("Temperature: "); 
   Serial.print(t);
   Serial.println(" *C ");
   }

}
