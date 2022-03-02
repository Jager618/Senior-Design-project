// Testing stretch sensors on ESP32
#include <Arduino.h>

int stretch_value = 0;
int output_pin = 36; //GPIO pin 36 or we can use 3.3v output pin
int feedback_input = 39; //GPIO pin 39

void setup() {
   Serial.begin(155200);
}

void loop() {
  stretch_value = analogRead(feedback_input); //get adc value for pin
  delay(1000);
   
  Serial.println(stretch_value);
  delay(1000);
}
