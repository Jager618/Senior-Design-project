// Testing stretch sensors for hand
#include <Arduino.h>

int flex_value = 0;
int input_pin1 = 36; //GPIO pin 36
int input_pin2 = 39; //GPIO pin 39
int input_pin3 = 34; //GPIO pin 34
int input_pin4 = 35; //GPIO pin 35
int input_pin5 = 32; //GPIO pin 32

const int PWM_Pin = 3; 

void setup() {
  pinMode(PWM_Pin, OUTPUT);
   Serial.begin(155200);
}

void loop() {
  // Map input voltage (between 0 and 3.3V) from voltage divider into integer value between 0 - 1023
  flex_value = analogRead(input_pin1); //get adc value for 1 flex sensor
  delay(1000);

  Serial.println(flex_value);
  delay(1000);
}