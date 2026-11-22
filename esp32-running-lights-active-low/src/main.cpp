#include <Arduino.h>

// Beginner-safe GPIOs on ESP32 DevKit V1 (ESP32-WROOM-32) - ACTIVE LOW
const int PINS[] = {4, 13, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27, 32, 33};
const int N = sizeof(PINS) / sizeof(PINS[0]);
const int STEP_MS = 500;

void allOff() {
  for (int i = 0; i < N; i++) digitalWrite(PINS[i], HIGH);   // HIGH = off
}

void showOnly(int i) {
  allOff();
  digitalWrite(PINS[i], LOW);                                // LOW = on
  delay(STEP_MS);
}

void setup() {
  allOff();                                                  // set off level first...
  for (int i = 0; i < N; i++) pinMode(PINS[i], OUTPUT);      // ...then enable outputs

  // Lamp test: all LEDs on
  for (int i = 0; i < N; i++) digitalWrite(PINS[i], LOW);
  delay(2000);
}

void loop() {
  for (int i = 0; i < N; i++)      showOnly(i);   // forward
  for (int i = N - 2; i > 0; i--)  showOnly(i);   // backward
}