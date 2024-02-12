#include <Arduino.h>
// Pin tanımlamaları
const int SW_pin = 2; // Anahtar pinini tanımla
const int x_pin = A1; // X eksenini okumak için analog pin
const int y_pin = A0; // Y eksenini okumak için analog pin

// Motor pin tanımlamaları
int sag_motor_pin1 = 3;
int sag_motor_pin2 = 5;
int sol_motor_pin1 = 6;
int sol_motor_pin2 = 9;

// Değişkenler
unsigned int x_degeri = 0;
unsigned int y_degeri = 0;

void setup() {
  // Pin modları tanımla
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  pinMode(sag_motor_pin1, OUTPUT);
  pinMode(sag_motor_pin2, OUTPUT);
  pinMode(sol_motor_pin1, OUTPUT);
  pinMode(sol_motor_pin2, OUTPUT);
  
  // Serial haberleşmeyi başlat
  Serial.begin(9600);
}

void ileri_git(uint8_t hiz) {
  analogWrite(sag_motor_pin1, hiz);
  analogWrite(sag_motor_pin2, 0);
  analogWrite(sol_motor_pin1, hiz);
  analogWrite(sol_motor_pin2, 0);
}

void geri_git(uint8_t hiz) {
  analogWrite(sag_motor_pin2, hiz);
  analogWrite(sag_motor_pin1, 0);
  analogWrite(sol_motor_pin2, hiz);
  analogWrite(sol_motor_pin1, 0);
}

void saga_don(uint8_t hiz) {
  analogWrite(sag_motor_pin2, hiz);
  analogWrite(sag_motor_pin1, 0);
  analogWrite(sol_motor_pin1, hiz);
  analogWrite(sol_motor_pin2, 0);
}

void sola_don(uint8_t hiz) {
  analogWrite(sag_motor_pin1, hiz);
  analogWrite(sag_motor_pin2, 0);
  analogWrite(sol_motor_pin2, hiz);
  analogWrite(sol_motor_pin1, 0);
}

void loop() {
  // Joystick değerlerini oku
  x_degeri = analogRead(x_pin);
  y_degeri = analogRead(y_pin);
  Serial.print(x_degeri);
  Serial.print(",");
  Serial.print(y_degeri);
  Serial.print("\n");
 
  if (y_degeri > 512 && y_degeri < 1024) ileri_git(map(y_degeri, 512, 1023, 0, 255));
  if (y_degeri >= 0 && y_degeri < 511) geri_git(map(y_degeri, 511, 0, 0, 255));
  if (x_degeri > 504 && x_degeri < 1024) saga_don(map(x_degeri, 504, 1023, 0, 255));
  if (x_degeri >= 0 && x_degeri < 502) sola_don(map(x_degeri, 502, 0, 0, 255));
 
  delay(20);
}
