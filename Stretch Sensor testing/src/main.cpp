// Testing module for stretch sensors for hand
#include <Arduino.h>

int flex_value1 = 0;
int flex_value2 = 0;
int flex_value3 = 0;
int flex_value4 = 0;
int flex_value5 = 0;
int avg_signal = 0;

int input_pin1 = 36; //GPIO pin 36
int input_pin2 = 39; //GPIO pin 39
int input_pin3 = 34; //GPIO pin 34
int input_pin4 = 35; //GPIO pin 35
int input_pin5 = 32; //GPIO pin 32

const int PWM_Pin = 3; 
int PWM_duty = 0;

void setup() {
  pinMode(PWM_Pin, OUTPUT);
   Serial.begin(155200);
}

void loop() {
  // Map input voltage (between 0 and 3.3V) from voltage divider into integer value between 0 - 1023
  flex_value1 = analogRead(input_pin1); //get adc value for 1 flex sensor

  PWM_duty = map(PWM_duty, 400, 900, 0, 255); // Map count to duty cycle
  ledcWrite(PWM_Pin,PWM_duty); // Write to PWM pin output
  delay(1000);

  Serial.println(flex_value1);
  delay(1000);
}