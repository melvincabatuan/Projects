#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "ESP32-AP";
const char* pass = "esp32accesspoint";   // at least 8 characters

void setup() {
  Serial.begin(115200);
  delay(1000);                           // give the monitor time to attach

  WiFi.softAP(ssid, pass);               // start the access point
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());       // default: prints 192.168.4.1
}

void loop() {
  Serial.print("Stations connected: ");
  Serial.println(WiFi.softAPgetStationNum());
  delay(2000);                           // print every 2 seconds
}