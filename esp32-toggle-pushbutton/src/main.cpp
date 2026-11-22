#include <Arduino.h>

const int BUTTON = 18;
const int LED = 23;

bool ledState = false;
bool lastButton = HIGH;

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
}

void loop() {
  bool button = digitalRead(BUTTON);

  if (lastButton == HIGH && button == LOW) {
    ledState = !ledState;
    digitalWrite(LED, ledState);
  }

  lastButton = button;
  delay(50);
}

/*
NOTE:
Detect the transition from HIGH to LOW, rather than simply checking whether the button is pressed. 
This ensures that holding the button does not repeatedly toggle the LED.
*/