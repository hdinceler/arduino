int led_kirmizi=9;
int led_sari=10;
int led_yesil=11;

void setup()
{
  pinMode(led_kirmizi , OUTPUT);
  pinMode(led_sari, OUTPUT);
  pinMode(led_yesil, OUTPUT);
  
}

void loop()
{
  digitalWrite(led_kirmizi, HIGH);
  delay(500);


  digitalWrite(led_kirmizi, LOW);
  digitalWrite(led_sari, HIGH);
  delay(500);


  digitalWrite(led_sari, LOW);
  digitalWrite(led_yesil, HIGH);
  delay(500);



  digitalWrite(led_yesil, LOW);
  digitalWrite(led_sari, HIGH);
  delay(500);


  digitalWrite(led_sari, LOW);
  delay(500);
}
 
