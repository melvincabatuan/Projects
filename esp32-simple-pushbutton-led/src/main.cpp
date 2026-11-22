#include <Arduino.h>

const int BTN_PIN = 18;   // button to GND (INPUT_PULLUP)
const int LED_PIN = 23;   // external LED, active HIGH

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
  digitalWrite(LED_PIN, LOW);      // start with the LED off
}

void loop() {
  int b = digitalRead(BTN_PIN);    // 1 = released, 0 = pressed
  Serial.println(b);

  if (b == LOW) digitalWrite(LED_PIN, HIGH);   // pressed: LED on
  else          digitalWrite(LED_PIN, LOW);    // released: LED off

  delay(50); // simple debounce delay
}