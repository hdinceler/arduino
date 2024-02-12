#include <Arduino.h>
#include <SPI.h>

#include "RF24.h"
#define CE_PIN 9
#define CSN_PIN 10
RF24 radio(CE_PIN, CSN_PIN);

void setup() {
  radio.begin();
  Serial.begin(9600);
  radio.openReadingPipe(1, 0xF0F0F0F0E12E); // Verici ile aynı adresi kullanmalısınız
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening(); // Dinleme modunda çalış
}

void loop() {
  if (radio.available()) {
    char text[32] = ""; // Mesajı depolamak için bir dizi
    radio.read(&text, sizeof(text)); // Mesajı oku
    Serial.println("Alınan Mesaj: " + String(text));
  }
}
