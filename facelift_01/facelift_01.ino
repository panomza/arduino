#include<string.h>
#include <LiquidCrystal.h> // include the library code:
byte buff[2];
int pin = 8;//DSM501A input D8
unsigned long duration;
unsigned long starttime;
unsigned long endtime;
unsigned long sampletime_ms = 5000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); 
int i=0;

void setup()
{
  Serial.begin(9600);
  pinMode(8,INPUT);
  starttime = millis(); 
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}
void loop()
{
 
  duration = pulseIn(pin, LOW);
  lowpulseoccupancy += duration;
  endtime = millis();


    
  if ((endtime-starttime) > sampletime_ms)
  {
   
    
    ratio = (lowpulseoccupancy-endtime+starttime + sampletime_ms)/(sampletime_ms*10.0);  // Integer percentage 0=>100
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
    Serial.print("lowpulseoccupancy:");
    Serial.print(lowpulseoccupancy);
    Serial.print("\n");
    Serial.print("ratio:");
    Serial.print(ratio);
    Serial.print("\n");
    Serial.print("DSM501A:  ");
    Serial.println(concentration);
    Serial.print(";\n\n");
    
    lowpulseoccupancy = 0;
    starttime = millis();

    lcd.setCursor(0,0);
    lcd.print("DustSensor"); // Prints "DstSensorDSM501A" on the LCD 
    delay(1000);
    lcd.setCursor(0,1);
    lcd.print(concentration); // Prints "DstSensorDSM501A" on the LCD 
    delay(1000);
    lcd.clear(); // Clears the LCD screen
  }

}
