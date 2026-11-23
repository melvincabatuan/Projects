#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32-AP";
const char* password = "access1234";       // at least 8 characters

const int LED_PIN = 23;                  // external LED, active HIGH
WebServer server(80);

void showPage() {
  String page = "<html><head><meta name='viewport' content='width=device-width,initial-scale=1'>";
  page += "<style>a{display:inline-block;padding:16px 36px;margin:10px;font-size:24px;";
  page += "background:#4CAF50;color:white;text-decoration:none;border-radius:10px}";
  page += "a.off{background:#f44336}</style></head>";
  page += "<body style='text-align:center;font-family:Arial'>";
  page += "<h1>ESP32 LED Control</h1>";
  page += "<p>LED is ";
  page += digitalRead(LED_PIN) ? "ON" : "OFF";
  page += "</p>";
  page += "<a href='/on'>Turn ON</a>";
  page += "<a class='off' href='/off'>Turn OFF</a>";
  page += "</body></html>";
  server.send(200, "text/html", page);
}

void ledOn() {
  Serial.println("Request: LED ON");
  digitalWrite(LED_PIN, HIGH);
  showPage();                            // show the updated page directly
}

void ledOff() {
  Serial.println("Request: LED OFF");
  digitalWrite(LED_PIN, LOW);
  showPage();
}

void notFound() {
  Serial.println("Unknown URL: " + server.uri());
  server.send(404, "text/plain", "Not found: " + server.uri());
}

void setup() {
  Serial.begin(115200);
  delay(1500);
  pinMode(LED_PIN, OUTPUT);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  Serial.print("Join WiFi \"ESP32_Hotspot\", then open http://");
  Serial.println(WiFi.softAPIP());

  server.on("/", showPage);
  server.on("/on", ledOn);
  server.on("/off", ledOff);
  server.on("/led/on", ledOn);           // also accept the original URLs
  server.on("/led/off", ledOff);
  server.onNotFound(notFound);
  server.begin();
}

void loop() {
  server.handleClient();
}