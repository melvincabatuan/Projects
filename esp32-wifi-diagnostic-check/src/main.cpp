#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "YOUR_SSID"; // Replace with your router SSID
const char* pass = "YOUR_PASSWORD"; //Replace with your router password

void setup() {
  Serial.begin(115200);
  delay(1500);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Scanning...");
  int n = WiFi.scanNetworks();
  for (int i = 0; i < n; i++)
    Serial.printf("%d: %s  ch %d  %d dBm\n", i, WiFi.SSID(i).c_str(),
                  WiFi.channel(i), WiFi.RSSI(i));

  Serial.printf("Connecting to %s\n", ssid);
  WiFi.begin(ssid, pass);
}

void loop() {
  Serial.printf("Status: %d\n", WiFi.status());
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(WiFi.localIP());
    while (true) delay(1000);
  }
  delay(1000);
}