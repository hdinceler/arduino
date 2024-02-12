//SDA A4 e , SCL de A5 e bağlanacak.  VCC 5 volta ,  GND GND ye bağlanacak
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
String gelen_mesaj;
void setup() {
  lcd.init();                                  
  lcd.backlight();                        
  lcd.print("Merhaba");            
  lcd.setCursor(0, 1);            
  Serial.begin(9600);      
}

void loop() {
  if(Serial.available()){
    gelen_mesaj=Serial.readString();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(gelen_mesaj);
  }
  lcd.clear();
  Serial.write("ben yusuf");
  delay(500);
  
}
