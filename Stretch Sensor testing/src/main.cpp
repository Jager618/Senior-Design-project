// Testing stretch sensors
#include <Arduino.h>

int stretch_value = 0;
int input_pin = 36; //GPIO pin 36

void setup() {
   Serial.begin(155200);
}

void loop() {
  stretch_value = analogRead(input_pin); //get adc value for pin
  delay(1000);

  Serial.println(stretch_value);
  delay(1000);
}