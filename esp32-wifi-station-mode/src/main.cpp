#include <Arduino.h>
#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to WiFi");

  WiFi.mode(WIFI_STA); // station (client) mode only
  /*
  Other modes:
      WIFI_AP: creates its own network (the SoftAP sketches)
      WIFI_AP_STA: both at once
      WIFI_OFF:  radio off
  */
  WiFi.begin("Wokwi-GUEST", "", 6);      // open network, channel 6
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println(" Connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(100);   // TODO: Build something!
}