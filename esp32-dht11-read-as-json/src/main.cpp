// DHT11 readings in a browser (JSON + AJAX), ESP32 as access point
// platformio.ini needs:
//   lib_deps =
//       adafruit/DHT sensor library
//       adafruit/Adafruit Unified Sensor
//       ESP32Async/ESPAsyncWebServer
//       ESP32Async/AsyncTCP

#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DHT.h>

const char* ssid = "ESP32-AP";
const char* password = "access1234";       // at least 8 characters

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

AsyncWebServer server(80);

// Latest valid readings (shared by loop() and the web handler)
float temperature = 0;
float humidity = 0;

// The web page
const char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP32 DHT11</title>
</head>
<body style="font-family:Arial; text-align:center; margin-top:50px">
  <h1>ESP32 DHT11</h1>
  <p>Temperature: <b><span id="temp_value">N/A</span>&deg;C</b></p>
  <p>Humidity: <b><span id="hum_value">N/A</span>%</b></p>
<script>
setInterval(function() { getDHT11Value(); }, 1000);
function getDHT11Value() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      var response = JSON.parse(this.responseText);
      document.getElementById("temp_value").innerHTML = Math.round(response.temp);
      document.getElementById("hum_value").innerHTML = Math.round(response.hum);
    }
  };
  xhttp.open("POST", "dht11_ajax", true);
  xhttp.send();
}
</script>
</body>
</html>
)=====";

void setup() {
  Serial.begin(115200);
  delay(1500);                           // give the Serial Monitor time to open
  dht.begin();

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  Serial.print("Join WiFi \"ESP32_DHT11\", then open http://");
  Serial.println(WiFi.softAPIP());       // 192.168.4.1

  // Main page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", webpage);
  });

  // JSON data requested by the page every second
  server.on("/dht11_ajax", HTTP_ANY, [](AsyncWebServerRequest *request) {
    String json = "{\"temp\":" + String(temperature, 1) +
                  ",\"hum\":"  + String(humidity, 1) + "}";
    request->send(200, "application/json", json);
  });

  server.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("DHT11 reading failed! Check wiring.");
  } else {
    humidity = h;                        // keep only valid readings
    temperature = t;
    Serial.printf("Temperature: %.1f C  Humidity: %.1f %%\n", t, h);
  }

  delay(2000);                           // the web server runs in the background
}