#include <Arduino.h>

int buttonPin = 4;
int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int buttonSignal = digitalRead(buttonPin);
  digitalWrite(ledPin, buttonSignal);
  Serial.println(buttonSignal);
  delay(1000);
}
