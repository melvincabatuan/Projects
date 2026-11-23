#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "YOUR_SSID";          // your router's WiFi name
const char* pass = "YOUR_PASSWORD";      // your router's WiFi password

const char ip[] = "192.168.1.101";       // the PC running the TCP server: Test-NetConnection 192.168.1.101 -Port 23
const uint16_t port = 23;

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
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client;
  if (!client.connect(ip, port)) {       // also: connect(ip, port, timeout)
    Serial.println("Connection failed, wait 5 sec ...");
    delay(5000);
    return;
  }

  client.printf("Message from TCP client\n");
  String response = client.readStringUntil('\n');   // waits up to 1 s
  Serial.println("Echoed message: " + response);

  client.stop();                         // close the connection
  delay(5000);
}