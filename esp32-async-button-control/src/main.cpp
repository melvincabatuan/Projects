// ESP32 LED control with ESPAsyncWebServer (access point mode)
// Needs these libraries in platformio.ini:
//   lib_deps =
//       ESP32Async/ESPAsyncWebServer
//       ESP32Async/AsyncTCP

#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "ESP32-AP";
const char* password = "access1234";       // at least 8 characters
const int LED_PIN = 23;                  // external LED, active HIGH

AsyncWebServer server(80);

const char webpage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP32 LED Control</title>
  <style>
    body { font-family: Arial; text-align: center; margin-top: 50px; }
    .button {
      padding: 16px 36px; margin: 20px; font-size: 20px;
      border: none; border-radius: 10px; cursor: pointer;
    }
    .on { background-color: #4CAF50; color: white; }
    .off { background-color: #f44336; color: white; }
  </style>
</head>
<body>
  <h1>ESP32 LED Control</h1>
  <p><strong>Status:</strong> %STATE%</p>
  <button class="button on" onclick="location.href='/on'">Turn ON</button>
  <button class="button off" onclick="location.href='/off'">Turn OFF</button>
</body>
</html>
)rawliteral";

String processor(const String& var) {
  if (var == "STATE") return digitalRead(LED_PIN) ? "ON" : "OFF";
  return String();
}

void setup() {
  Serial.begin(115200);
  delay(1500);
  pinMode(LED_PIN, OUTPUT);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  Serial.print("Join WiFi \"ESP32_Hotspot\", then open http://");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("Request: /");
    AsyncWebServerResponse *response =
        request->beginResponse(200, "text/html", webpage, processor);
    response->addHeader("Cache-Control", "no-store");   // never reuse an old page
    request->send(response);
  });

  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("Request: /on  -> LED ON");
    digitalWrite(LED_PIN, HIGH);
    request->redirect("/");
  });

  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("Request: /off -> LED OFF");
    digitalWrite(LED_PIN, LOW);
    request->redirect("/");
  });

  server.onNotFound([](AsyncWebServerRequest *request) {
    Serial.println("Unknown URL: " + request->url());
    request->send(404, "text/plain", "Not found: " + request->url());
  });

  server.begin();
}

void loop() {
}