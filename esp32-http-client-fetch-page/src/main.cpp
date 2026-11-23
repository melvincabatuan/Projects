#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "YOUR_SSID";          // your router's WiFi name
const char* pass = "YOUR_PASSWORD";      // your router's WiFi password


const char host[] = "www.google.com";
const int MAX_BODY_LINES = 15;           // how many lines of the page to show

String httpRequest = "GET / HTTP/1.0\r\n"            // 1.0: no chunked replies
                     "Host: " + String(host) + "\r\n"
                     "Connection: close\r\n\r\n";

void setup() {
  Serial.begin(115200);
  delay(1500);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");
  Serial.printf("ESP32 IP: %s\n", WiFi.localIP().toString().c_str());
}

void loop() {
  Serial.println("\n==============================");

  // 1. WiFi status
  if (WiFi.status() == WL_CONNECTED)
    Serial.printf("WiFi: CONNECTED (IP %s, signal %d dBm)\n",
                  WiFi.localIP().toString().c_str(), WiFi.RSSI());
  else {
    Serial.println("WiFi: NOT CONNECTED, reconnecting...");
    WiFi.reconnect();
    delay(5000);
    return;
  }

  // 2. Server connection status
  Serial.printf("Connecting to %s:80 ... ", host);
  WiFiClient client;
  if (!client.connect(host, 80)) {
    Serial.println("FAILED");
    delay(5000);
    return;
  }
  Serial.println("CONNECTED");

  // 3. Send the request and wait for the reply
  client.print(httpRequest);
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println("Timeout: no reply");
      client.stop();
      return;
    }
  }

  // 4. Status line and headers (stop at the blank line)
  Serial.println("--- Response headers ---");
  while (client.connected() || client.available()) {
    String line = client.readStringUntil('\n');
    line.trim();
    if (line.length() == 0) break;
    Serial.println(line);
  }

  // 5. First lines of the page body
  Serial.println("--- Page (first lines) ---");
  int count = 0;
  while ((client.connected() || client.available()) && count < MAX_BODY_LINES) {
    String line = client.readStringUntil('\n');
    line.trim();
    if (line.length() == 0) continue;
    if (line.length() > 100) line = line.substring(0, 100) + " ...";
    Serial.println(line);
    count++;
  }

  client.stop();
  Serial.println("--- Done ---");
  delay(5000);
}