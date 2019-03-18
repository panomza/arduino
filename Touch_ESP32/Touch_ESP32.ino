#define TOUCH_PIN T0 //connected to 4
#define LED_PIN A13 //connected to 15
//#include <rtc.h>
int touch_value;
 
void setup()
{
Serial.begin(9600);
Serial.println("ESP32 Touch Test");
pinMode(LED_PIN, OUTPUT);
digitalWrite (LED_PIN, LOW);
}
 
void loop()
{
touch_value = touchRead(TOUCH_PIN);
Serial.println(touch_value); // get value using T0
//Serial.println(rtc_clk_cpu_freq_get());
delay(100);

if (touch_value < 60)
{
digitalWrite (LED_PIN, HIGH);
}
else
{
digitalWrite (LED_PIN, LOW);
}

}
