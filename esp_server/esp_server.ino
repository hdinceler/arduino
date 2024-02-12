// #include <ESP8266WiFi.h>
// #include <ESP8266WebServer.h>

// const char *ssid = "cxvnj4w35uR4354ERWR";  // Wi-Fi ağ adı
// const char *password = "cxvnj4w35uR4354ERWR.+/#!RoS6Qk8C:|";        // Şifresiz ağ, bu alani boş bırakın

// ESP8266WebServer server(80);

// void handleRoot() {
//   String html = "<html><body><h1>Hello from NodeMCU!</h1></body></html>";
//   server.send(200, "text/html", html);
// }

// void setup() {
//   Serial.begin(115200);

//   // Wi-Fi bağlantısı başlat
//   WiFi.begin(ssid, password);
//   while (WiFi.waitForConnectResult() != WL_CONNECTED) {
//     Serial.println("Connection Failed! Rebooting...");
//     delay(5000);
//     ESP.restart();
//   }

//   // HTTP GET isteği için kök işleyici
//   server.on("/", HTTP_GET, handleRoot);

//   // Sunucuyu başlat
//   server.begin();
//   Serial.println("HTTP server started");

//   // NodeMCU'nun IP adresini seri monitörde görüntüle
//   Serial.println("NodeMCU IP Address: " + WiFi.localIP().toString());
// }
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "NodeMCU_Hotspot";   // NodeMCU'nun hotspot adı
const char *password = "12345678";       // Hotspot şifresi

ESP8266WebServer server(80);

void handleRoot() {
  String html = "<html><body><h1>Hello from NodeMCU!</h1></body></html>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);

  // Hotspot'u başlat
  WiFi.softAP(ssid, password);
  
  // Hotspot'un IP adresini seri monitörde görüntüle
  Serial.print("NodeMCU Hotspot IP Address: ");
  Serial.println(WiFi.softAPIP());

  // HTTP GET isteği için kök işleyici
  server.on("/", HTTP_GET, handleRoot);

  // Sunucuyu başlat
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Sunucu taleplerini işle
  server.handleClient();

  // Diğer kodunuz buraya gelecek
}



// void loop() {
//   // Sunucu taleplerini işle
//   server.handleClient();

//   // Diğer kodunuz buraya gelecek
// }
