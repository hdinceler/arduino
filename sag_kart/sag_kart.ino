//sağdaki kart 9 numaralı usb portunda
String gelen_mesaj;
String giden_mesaj;
void setup() {
 Serial.begin(9600);
}

void loop() {
  Serial.println("ben sagdaki kartim");
  delay("400");
}
