int led=13;

void setup() {
  pinMode( led, OUTPUT ) ; 
}

void loop() {
  digitalWrite( led, HIGH );delay(3000);
  digitalWrite(led, LOW);delay(30
  00);

  // digitalWrite( led, HIGH );delay(300);
  // digitalWrite(led, LOW);delay(300);

  // digitalWrite( led, HIGH );delay(250);
  // digitalWrite(led, LOW);delay(250);

  // digitalWrite( led, HIGH );delay(100);
  // digitalWrite(led, LOW);delay(100);
}
