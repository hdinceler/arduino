#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7,8); // CE, CSN pins

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(0xF0F0F0F0E1LL); // Alıcı adresi, alıcı ile aynı olmalı
}

void loop() {
  // "Merhaba" mesajını gönder
  char message[] = "Merhaba";
  radio.write(&message, sizeof(message));

  Serial.println("Merhaba gönderildi");

  delay(1000); // 1 saniye bekle
}
