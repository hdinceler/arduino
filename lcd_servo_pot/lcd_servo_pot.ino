#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#define pot A0
int okunan= 0;
void setup() {
 lcd.init();                                  
  lcd.backlight(); 
  lcd.clear();                       
  lcd.setCursor(0, 1);            
  Serial.begin(9600);
 pinMode(pot, INPUT);
}

void loop() {
  okunan=analogRead(pot);
  int motor_acisi= map(okunan,0,1023, 0,180);
  Serial.println( motor_acisi  );
   lcd.setCursor(0,0);
    lcd.print(motor_acisi);
    delay(200);
    lcd.clear();
}
