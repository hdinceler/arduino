  #include <ESP8266WiFi.h>
  #include <WiFiClient.h>
  #include <ESP8266WebServer.h>
  #include <ElegantOTA.h>

const char* ssid = "cxvnj4w35uR4354ERWR";
const char* password = "cxvnj4w35uR4354ERWR.+/#!RoS6Qk8C:|";
ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
    Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  ElegantOTA.begin(&server);  
  pinMode(LED_BUILTIN, OUTPUT);

}

// the loop function runs over and over again forever
void loop() {
  ElegantOTA.loop();
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(500);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(500);                      // wait for a second
}
