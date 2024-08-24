#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Arduino.h>
const char* ssid = "xavier";
const char* password = "xyvielyonsmbugua";

const  
 char* serverName = "http://192.168.0.102:3001/api/arduino/getmessage";

void setup() {
    // ... other setup code
    Serial.begin(9600);
    WiFi.begin(ssid, password);
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
}

void loop()  
 {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        http.begin(serverName);  

        // Set any necessary headers if required
        // http.addHeader("Content-Type", "application/json");

        int httpCode = http.GET();

        if (httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            Serial.println("HTTP GET request successful!");

            // Parse the JSON response
            DynamicJsonDocument doc(1024);  // Adjust the buffer size as needed
            deserializeJson(doc, payload);

            // Extract and store data
            String variable1 = doc["key1"].as<String>();
            int variable2 = doc["key2"].as<int>();
            float variable3 = doc["key3"].as<float>();

            // Do something with the extracted data
            Serial.println("Extracted data:");
            Serial.println("Variable 1: " + variable1);
            Serial.println("Variable 2: " + String(variable2));
            Serial.println("Variable 3: " + String(variable3));
        } else {
            Serial.print("HTTP GET request failed, error code: ");
            Serial.println(httpCode);
        }

        http.end();
    } else {
        Serial.println("WiFi Disconnected");
    }
}