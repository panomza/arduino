/*
  This code will fetch the latest data from your antares project device.
  Your Antares project device must have a structure like this:
  {
    "Temperature": "some-value",
    "Humidity": "some-value"
  }
  For more information please visit https://antares.id/id/docs.html
*/

#include "AntaresESP8266HTTP.h"

#define ACCESSKEY "your-access-key"
#define WIFISSID "your-wifi-ssid"
#define PASSWORD "your-wifi-password"

#define projectName "your-project-name"
#define deviceName "your-device-name"

AntaresESP8266HTTP antares(ACCESSKEY);

void setup() {
  Serial.begin(115200);
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID,PASSWORD);
}

void loop() {
  Serial.println(antares.retrieveLatestData(projectName, deviceName));
  delay(10000);
}
