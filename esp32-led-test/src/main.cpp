#include <Arduino.h>

#define LED_PIN 23

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);  // Configure GPIO23 as output
    digitalWrite(LED_PIN, HIGH);  // Turn ON LED
    Serial.println("GPIO23 LED is ON!");
}

void loop() {
    // LED remains ON
}
