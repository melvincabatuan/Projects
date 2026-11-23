#include <Arduino.h>
#include <WiFi.h>

#define LED_PIN 23                     // external LED, active HIGH

const char* ssid = "YOUR_SSID";      // change to your router for real hardware: REPLACE with your router SSID
const char* pass = "YOUR_PASSWORD";                 // empty = open network : REPLACE with your router password for real hardware


WiFiServer server(23);                // TCP port 23 (use this port in Hercules)
 
// Runs automatically when WiFi drops or fails, and prints the reason number.
// Common reasons:
//   15, 202, 204 = wrong password or router security mode (try WPA2-PSK AES)
//   201          = network name not found (spelling, or 5 GHz only)
//   8, 203       = router refused the board (MAC filter or device limit)
void onWiFiEvent(arduino_event_id_t event, arduino_event_info_t info) {
  if (event == ARDUINO_EVENT_WIFI_STA_DISCONNECTED) {
    Serial.print("WiFi failed, reason ");
    Serial.println(info.wifi_sta_disconnected.reason);
  }
}
 
void setup() {
  Serial.begin(115200);
  delay(2000);                        // time to open the Serial Monitor
  Serial.println();
  Serial.println("=== TCP LED server ===");   // if you don't see this, this sketch is not running
 
  pinMode(LED_PIN, OUTPUT);
 
  // Connect to WiFi
  WiFi.mode(WIFI_STA);
  WiFi.onEvent(onWiFiEvent);
  WiFi.begin(ssid, pass);
 
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  int seconds = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
    seconds++;
    if (seconds == 30) {              // no luck after 30 s: start over
      Serial.println();
      Serial.println("Could not connect. Restarting...");
      ESP.restart();
    }
  }
 
  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("Server IP: ");
  Serial.println(WiFi.localIP());     // type this IP into Hercules
 
  server.begin();                     // start listening for clients
  Serial.println("Server started on port 23");
}
 
void loop() {
  WiFiClient client = server.accept();    // check for a new client
  if (!client) return;                    // nobody connected yet
 
  Serial.println("Client connected");
 
  while (client.connected()) {
    if (client.available()) {
      String cmd = client.readStringUntil('\n');   // read one line
      cmd.trim();                                  // remove spaces and \r
 
      Serial.print("Received: ");
      Serial.println(cmd);
 
      if (cmd == "LED+ON") {
        digitalWrite(LED_PIN, HIGH);
        client.println("OK");
      } else if (cmd == "LED+OFF") {
        digitalWrite(LED_PIN, LOW);
        client.println("OK");
      } else if (cmd == "LED") {
        if (digitalRead(LED_PIN) == HIGH) client.println("LED is on");
        else                              client.println("LED is off");
      } else {
        client.println("Unknown command");
      }
    }
    delay(1);
  }
 
  client.stop();
  Serial.println("Client disconnected");
}
