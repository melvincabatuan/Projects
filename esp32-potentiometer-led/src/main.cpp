#include <Arduino.h>

const int POT_PIN = 32;    // potentiometer wiper (ADC1)
const int LED_PIN = 23;    // external LED, active HIGH
const int freq = 1000;     // 1 kHz PWM
const int res  = 10;       // 10 bits: 0 to 1023

void setup() {
  ledcAttach(LED_PIN, freq, res);
}

void loop() {
  int raw = analogRead(POT_PIN);             // 0 to 4095 (12-bit ADC)
  int duty = map(raw, 0, 4095, 0, 1023);     // scale to the 10-bit PWM range
  ledcWrite(LED_PIN, duty);
  delay(10);
}