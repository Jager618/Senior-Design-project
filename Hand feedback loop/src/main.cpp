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

// Wifi credentials
const char* ssid = "Big Gaming Gamers 2.4g";
const char* password = "1234123412341";


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
  
    http.begin(" "); //Specify the URL
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
  double feedback1 = ledcRead(Input_Ch2);
  double feedback2 = ledcRead(Input_Ch3);
  double feedback3 = ledcRead(Input_Ch4);
  double feedback4 = ledcRead(Input_Ch5);
  double feedback5 = ledcRead(Input_Ch6);
  
  // Compare flex sensor feedback to estimate position (1.5V = fully flexed/grasped hand)
  
  //PID loop
  double DutyCycle = pid.calculate(Href, output);

  // Output PWM signal 
  // Using ledc to generate arbitrary PWM signal
  ledcWrite(PWM_Ch,DutyCycle)
    
}

