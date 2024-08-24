#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
void callback(char *topic, byte *payload, unsigned int length);
const char* ssid = "xavier";
const char* password = "xyvielyonsmbugua";

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char *topic = "esp32/test";
const char *topic2 = "esp32/test1";
const char *mqtt_username = "xyvielyons";
const char *mqtt_password = "XyvieLyons7@gmail.com";

#define led3  32
#define led2  35
#define led1  34

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  // Set software serial baud to 115200;
 Serial.begin(9600);
 pinMode(2,OUTPUT);
 pinMode(led2,OUTPUT);
 pinMode(led3,OUTPUT);
 // connecting to a WiFi network
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.println("Connecting to WiFi..");
 }
 Serial.println("Connected to the WiFi network");


 client.setServer(mqtt_server,mqtt_port);
 client.setCallback(callback);

 while(!client.connected()){
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
    if(client.connect(client_id.c_str(),mqtt_username,mqtt_password)){
          Serial.println("Public emqx mqtt broker connected");
    }else{
          Serial.print("failed with state ");
          Serial.print(client.state());
          delay(2000);
    }
 }
  client.subscribe(topic);
  client.publish(topic2, "Hi EMQX I'm ESP32");


;}

void loop() {
  client.loop();// put your main code here, to run repeatedly:
}

void callback(char *topic, byte *payload, unsigned int length){
  Serial.print("message arrived in topic: ");
  Serial.println(topic);
  Serial.print("message:");
  String messageTemp;

  for(int i=0;i<length;i++){
    Serial.print((char) payload[i]);
    messageTemp += (char) payload[i];
  }
  Serial.println();
  Serial.println("-----------------------");
  Serial.println(messageTemp);

  if(messageTemp == "hello1on"){
    digitalWrite(2,HIGH);
  }
  if(messageTemp == "hello1off"){
    digitalWrite(2,LOW);
  }
  if(messageTemp == "hello2"){
    digitalWrite(led2,HIGH);
  }
  if(messageTemp == "hello3"){
    digitalWrite(led3,HIGH);
  }

}


