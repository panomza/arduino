#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
void setup() {
   Serial.begin(9600); 
   Serial.println("DHTxx test!");
   dht.begin();
}

void loop() {

   float h = dht.readHumidity();
   float t = dht.readTemperature();

   if (isnan(h) || isnan(t)) {
     Serial.println("Failed to read from DHT sensor!");
      return;
   }
   Serial.print("Humidity: "); 
   Serial.print(h);
   Serial.print(" %\t");
   Serial.print("Temperature: "); 
   Serial.print(t);
   Serial.println(" *C ");
   } 
