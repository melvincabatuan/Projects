#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(1500);
  Serial.println("DHT11 hardware test");

  // Wiring check: pull the pin DOWN and see whether something pulls it UP
  pinMode(DHTPIN, INPUT_PULLDOWN);
  delay(100);
  if (digitalRead(DHTPIN) == HIGH)
    Serial.println("Data line: HIGH -> sensor/pull-up detected (wiring looks OK)");
  else
    Serial.println("Data line: LOW  -> nothing pulling it up: DATA wire loose, VCC missing, or bare sensor without resistor");

  dht.begin();                           // this sets the pin mode again
  delay(2000);
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Read failed (NaN): no valid reply from the sensor");
    delay(2000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  delay(2000);
}