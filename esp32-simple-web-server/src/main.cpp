// ESP32 simple web server 
// Needs these libraries in platformio.ini:
//   lib_deps =
//       ESP32Async/ESPAsyncWebServer
//       ESP32Async/AsyncTCP

#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

// 1. Your WiFi details (change these)
const char* ssid = "YOUR_WIFI_SSID";
const char* pass = "YOUR_WIFI_PASSWORD";

// 2. Create the web server on port 80 (the standard web port)
AsyncWebServer server(80);

// 3. The web page the ESP32 will send to the browser
const char webpage[] PROGMEM = R"=====(
<html>
  <head><title>ESP32 Web Page</title></head>
  <body><p>Hello, World!</p></body>
</html>
)=====";

void setup() {
  Serial.begin(115200);
  delay(1500);                          // give the Serial Monitor time to open

  // 4. Connect to your WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");

  // 5. Print the address to type into your browser
  Serial.print("Open in your browser: http://");
  Serial.println(WiFi.localIP());

  // 6. When a browser asks for the main page "/", send our web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", webpage);
  });

  // 7. Start the server
  server.begin();
}

void loop() {
  // Nothing to do here: the async server works in the background
}