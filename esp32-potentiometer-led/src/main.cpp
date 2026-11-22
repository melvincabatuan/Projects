#include <Arduino.h>

const int POT_PIN = 32;    // potentiometer wiper (ADC1)
const int LED_PIN = 23;    // external LED, active HIGH

bool ledIsOn = false;
unsigned long lastToggle = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int raw = analogRead(POT_PIN);                 // 0 to 4095
  int interval = map(raw, 0, 4095, 500, 50);     // ms per half-cycle (500 = slow, 50 = fast)

  if (millis() - lastToggle >= interval) {
    lastToggle = millis();
    ledIsOn = !ledIsOn;                          // flip the LED
    digitalWrite(LED_PIN, ledIsOn);
  }
}