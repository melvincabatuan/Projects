#include <Arduino.h>

const int LED_PIN = 18;   // GPIO18: LED through a 220 ohm resistor to GND
 
void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("ESP32 Blink started");
}
 
void loop() {
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED ON");
  delay(500);
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED OFF");
  delay(500);
}