#include <Arduino.h>

void setup()
{
  pinMode(2, OUTPUT);          // on-board LED
  pinMode(18, INPUT_PULLUP);   // button to GND
}

void loop()
{
  if (digitalRead(18) == LOW)  // pressed
    digitalWrite(2, HIGH);
  else
    digitalWrite(2, LOW);
}