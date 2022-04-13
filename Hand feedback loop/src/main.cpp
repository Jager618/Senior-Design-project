#include "Arduino.h"

#include "PID.h"
#include <stdio.h>


// Test the PID controller code and will be used to tune gains 

// Sample time 0.1, Max 255, Min 0, Kp 0.1, Ki 0.01, Kd 5
PID pid = PID(0.1, 255, 0, 0.1, 0.01, 5);
const int ledPin = 16;

const int freq = 32; // 32 hz PWM
const int PWM_Ch = 7;
const int Input_Ch1 = 1;
const int Input_Ch2 = 2;
const int Input_Ch3 = 3;
const int Input_Ch4 = 4;
const int Input_Ch5 = 5;
const int Input_Ch6 = 6;


const int resolution = 8; // This resolution gives a 0-255 duty cycle range
unsigned int DutyCycle = 127; //Initial 50% duty cycle. 100% = fully grasped hand, 50% = halfway grasped

// This can be the initial flex sensor signal for testing corresponding to 0 degree flex-
// Actual range is 3.3 - 1.5V from flex sensor, 3.3v being unflexed fingers, 1.5V fully flexed fingers
double sensor_test = 2;

void setup() {
}

void loop() {
  // Reference Input from FABRIK Href (may need SPI for this)
  double Href = ledcRead(Input_Ch1);
  //Measured output from stretch sensors for each finger (5 total)
  double feedback1 = ledcRead(Input_Ch2);
  double feedback2 = ledcRead(Input_Ch3);
  double feedback3 = ledcRead(Input_Ch4);
  double feedback4 = ledcRead(Input_Ch5);
  double feedback5 = ledcRead(Input_Ch6);

  //PID loop
  double DutyCycle = pid.calculate(Href, output);

  // Output PWM signal 
  // Using ledc to generate arbitrary PWM signal
  ledcWrite(PWM_Ch,DutyCycle)
    
}

