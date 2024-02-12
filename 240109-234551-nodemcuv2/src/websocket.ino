#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
 
const char* ssid = "cxvnj4w35uR4354ERWR";  
const char* password = "cxvnj4w35uR4354ERWR.+/#!RoS6Qk8C:|"; 
const char* webSocketHost = "192.168.1.2";
const uint16_t webSocketPort = 1980;
 
WiFiClient wifiClient;
WebSocketClient webSocket;

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  webSocket.begin(wifiClient, webSocketHost, webSocketPort, "/");
}

void loop() {
  if (millis() % 1000 == 0) { // Her saniye bir kontrol et
    if (webSocket.available()) {
      Serial.println("Sending WebSocket message");
      webSocket.printf("Merhaba");
    }
    webSocket.monitor();
  }
}