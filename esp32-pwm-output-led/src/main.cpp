#include <Arduino.h>

#define LED_PIN 23

const int freq = 1000;  // 1 kHz
const int res = 10;     // 10-bit resolution

void setup() {
  Serial.begin(115200);

  if (ledcAttach(LED_PIN, freq, res)) {
    Serial.println("PWM successfully attached!");
  } else {
    Serial.println("PWM attachment failed!");
  }

  ledcWrite(LED_PIN, 0);
}

void loop() {

  // Gradually increase brightness
  for (int i = 0; i <= 1023; i += 20) {
    ledcWrite(LED_PIN, i);
    delay(100);
  }

  // Gradually decrease brightness
  for (int i = 1023; i >= 0; i -= 20) {
    ledcWrite(LED_PIN, i);
    delay(100);
  }
}
