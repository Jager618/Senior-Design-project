// Using Arduino library with esp32
#include "Arduino.h"

#include "PID.h"
#include <stdio.h>
#include "WiFi.h"
#include "HTTPClient.h"

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
  
    http.begin("http://api.thingspeak.com/update?api_key=9UFD8N6EX92CGEIF"); //Specify the URL for testing
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
}