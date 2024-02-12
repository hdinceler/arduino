#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7,8); // CE, CSN pins

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, 0xF0F0F0F0E1LL); // Gönderici adresi, gönderici ile aynı olmalı
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    char message[32] = "";
    radio.read(&message, sizeof(message));
    Serial.println("Alınan Mesaj: " + String(message));
  }
}
