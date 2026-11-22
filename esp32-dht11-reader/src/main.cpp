#include <Arduino.h>
#include <DHT.h>
#define DHTPIN 22
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Sensor read failed");
  } else {
    Serial.printf("Temperature: %.2fC Humidity: %.2f%%\n", temp, hum);
  }
  delay(2000);                    // DHT22 limit: 0.5 Hz
}