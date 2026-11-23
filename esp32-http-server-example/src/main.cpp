#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "YOUR_SSID";          // your router's WiFi name
const char* pass = "YOUR_PASSWORD";      // your router's WiFi password

WiFiServer server(80);                   // HTTP uses port 80

String httpResponseHeader =
  "HTTP/1.1 200 OK\r\n"
  "Content-Type: text/html\r\n"
  "Connection: close\r\n"
  "\r\n";                                // the empty line

String webPage =
  "<!DOCTYPE HTML>\r\n"
  "<html><head><title>ESP32 HTTP Server</title></head>\r\n"
  "<body><p>A web page from ESP32</p></body></html>\r\n";

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
  Serial.print("Open in your browser: http://");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.accept();   // wait for a browser
  if (client) {
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);                 // log the request
        if (c == '\n' && currentLineIsBlank) {   // request ended
          client.print(httpResponseHeader);
          client.print(webPage);
          break;
        }
        if (c == '\n') currentLineIsBlank = true;
        else if (c != '\r') currentLineIsBlank = false;
      }
    }
    delay(1);                            // let the browser receive
    client.stop();
  }
}