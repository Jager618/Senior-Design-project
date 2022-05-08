// Hand feedback control system SDP
// Kyle Atlas

// Using Arduino library with esp32
#include "Arduino.h"

#include "PID.h"
#include <stdio.h>
#include "WiFi.h"
#include "HTTPClient.h"


// Test the PID controller code and will be used to tune gains 

// Sample time 0.1, Max 255, Min 0, Kp 0.1, Ki 0.01, Kd 5
PID pid = PID(0.1, 255, 0, 0.1, 0.01, 5);
const int ledPin = 16;

const int freq = 32; // 32 hz PWM
// PWM output pins to solenoid valves
const int PWM_Ch1 = 14;
const int PWM_Ch2 = 25;
const int PWM_Ch3 = 26;
const int PWM_Ch4 = 27;
const int PWM_Ch5 = 33;

//Flex sensor feedback- ADC pins
const int Input_Ch1 = 32;
const int Input_Ch2 = 34;
const int Input_Ch3 = 35;
const int Input_Ch4 = 36;
const int Input_Ch5 = 39;


const int resolution = 8; // This resolution gives a 0-255 duty cycle range
unsigned int DutyCycle = 127; //Initial 50% duty cycle. 100% = fully grasped hand

// This can be the initial flex sensor signal for testing corresponding to 0 degree flex-
// Actual range is 3.3 - 1.5V from flex sensor, 3.3v being unflexed fingers, 1.5V fully flexed fingers
double sensor_test = 500;

// credentials for my home internet
const char* ssid = "Mirror March";
const char* password = "5andared";


void setup() {
  Serial.begin(115200);
  delay(4000);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  
  Serial.println("Connected to the WiFi network");
}

void loop() {
  
  double Href;
  
  // Reference Input from Jetson Nano using HTTP
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
  
    HTTPClient http;
  
    http.begin(""); //Specify the URL for testing/IP address
    int httpCode = http.GET(); //Make the request
  
    if (httpCode > 0) { //Check for the returning code
  
        String payload = http.getString();
        Href = payload;
        Serial.println(httpCode);
        Serial.println(payload);
      }
  
    else {
      Serial.println("Error on HTTP request");
    }
  
    http.end(); //Free the resources
  }
  
  delay(10000);
 
  //Measured output from stretch sensors for each finger (5 total)
  double feedback1 = ledcRead(Input_Ch1);
  double feedback2 = ledcRead(Input_Ch2);
  double feedback3 = ledcRead(Input_Ch3);
  double feedback4 = ledcRead(Input_Ch4);
  double feedback5 = ledcRead(Input_Ch5);
  
  // Average feedback
  double average_feedback = (feedback1 + feedback2 + feedback3 + feedback4 + feedback5)/5;
  //PID loop
  double DutyCycle = pid.Update(Href, average_feedback);

  // Output PWM signal 
  // Using ledc to generate arbitrary PWM signal
  ledcWrite(PWM_Ch1,DutyCycle);
  ledcWrite(PWM_Ch2,DutyCycle);
  ledcWrite(PWM_Ch3,DutyCycle);
  ledcWrite(PWM_Ch4,DutyCycle);
  ledcWrite(PWM_Ch5,DutyCycle);
    
}