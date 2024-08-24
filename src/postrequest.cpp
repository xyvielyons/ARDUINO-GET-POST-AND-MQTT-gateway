#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h> // Include ArduinoJson library

const char* ssid = "xavier";
const char* password = "xyvielyonsmbugua";

// Your Domain name with URL path or IP address with path
const char* serverName = "http://192.168.0.102:3001/api/arduino/postmessage";

// Timer set to 5 seconds (5000)
unsigned long timerDelay = 5000;
unsigned long lastTime = 0;

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");  

  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Timer set to 5 seconds,publishing data every 5 seconds.");
}

void loop() {
  // Send an HTTP POST request every 5 seconds
  if ((millis() - lastTime) > timerDelay) {
    // Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      // Create a StaticJsonDocument object for JSON data
      JsonDocument doc; // Adjust size as needed
      // Add data to the JSON document
      doc["api_key"] = "tPmAT5Ab3j7F9";
      doc["sensor"] = "BME280";
      doc["value1"] = 24.25;  // Replace with your actual sensor readings
      doc["value2"] = 49.54;
      doc["value3"] = 1005.14;

      // Serialize the JSON document into a char array
      char jsonBuffer[200]; // Adjust size as needed
      serializeJson(doc, jsonBuffer);

      // Start HTTP POST request
      http.begin(client, serverName);
      http.addHeader("Content-Type", "application/json");

      // Send the JSON data in the POST request body
      int httpResponseCode = http.POST(jsonBuffer);

      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);

      // Free resources
      http.end();
    } else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();  

  }
}
