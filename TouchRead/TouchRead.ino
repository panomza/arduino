int led=33;
void setup()
{
  Serial.begin(115200);
  Serial.println("ESP32 Touch Test");
}

void loop()
{
  Serial.println(touchRead(T4));  // get value using T0
  if(touchRead(T4)<60){digitalWrite(led,1);}
  else{digitalWrite(led,0);}
  delay(1000);
}
