#include "Arduino.h"

#include "PID.h"
#include <stdio.h>


// Test the PID controller code and will be used to tune gains 

// Sample time 0.1, Max 255, Min 0, Kp 0.1, Ki 0.01, Kd 5
PID pid = PID(0.1, 255, 0, 0.1, 0.01, 5);
const int ledPin = 16;

const int freq = 32; // 32 hz
const int PWM_Ch = 5;
const int Input_Ch1 = 0;
const int Input_Ch2 = 0;
const int resolution = 8; // 0-255 duty cycle range
unsigned int DutyCycle = 127;

// This can be the initial/input stretch sensor signal for testing
double sensor_test = 50;

void setup() {
}

void loop() {
  // Reference Input from FABRIK Href
  double Href = ledcRead(Input_Ch1);
  //Measured output from stretch sensor
  double output = ledcRead(Input_Ch2);

  //PID loop
  double DutyCycle = pid.calculate(Href, output);

  // Output PWM signal 
  // Using ledc to generate arbitrary PWM signal
  ledcWrite(PWM_Ch,DutyCycle)
    
}

