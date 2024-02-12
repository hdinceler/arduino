#include <Arduino.h>
#include <SPI.h>

#include <RF24.h>
// pin tanımlamaları
#define CE_PIN 8
#define CSN_PIN 7
#define sag_pin_ileri 3
#define sag_pin_geri 5
#define sol_pin_ileri 6
#define sol_pin_geri 9
#define trigPin_on 2  // Ön taraf HC-SR04 trig pini
#define echoPin_on 4 // Ön taraf HC-SR04 echo pini
#define projektor_pin A5
#define buzzer_pin A4  // araç ön taraftan en fazla belirtilen cm kadar yaklaşabilir
#define trigPin_arka A3  //Arka taraf  HC-SR04 trig pini
#define echoPin_arka A2 //Arka Taraf HC-SR04 echo pini
#define far_pin A1 //
//////// 
//  hcsr-04 mesafe hassasiyet
#define mesafe_limit_on 5   // araç ön taraftan en fazla belirtilen cm kadar yaklaşabilir
#define mesafe_limit_arka 3   // araç arka taraftan en fazla belirtilen cm kadar yaklaşabilir
#define sag_pwm_ileri 0
#define sag_pwm_geri 0
#define sol_pwm_ileri  0
#define sol_pwm_geri 0
 
uint8_t btn_up =0;
uint8_t btn_down =0;
uint8_t btn_right =0;
uint8_t btn_left =0;
uint8_t btn_joy=0;
unsigned int  x_degeri=0;
unsigned int y_degeri=0;
char buff[10];
char gelen_komut[64] = "";
unsigned long bip_previousMillis = 0;  // Önceki zamanı saklamak için değişken
const long bip_aralik= 500;  // Uyarı sesi aralığı (milisaniye cinsinden)

RF24 radio(CE_PIN, CSN_PIN);
 
void ileri_git(uint8_t hiz){
  Serial.print("ileri_hiz:");
  Serial.print(hiz);
  Serial.print("-");
  analogWrite( sag_pin_ileri, hiz );analogWrite( sol_pin_ileri, hiz );analogWrite( sag_pin_geri, 0 );analogWrite(sol_pin_geri, 0 );
}
void geri_git(uint8_t hiz){
  Serial.print("geri_hiz:");
  Serial.print(hiz);
  Serial.print("-");
  analogWrite( sag_pin_ileri, 0 );analogWrite( sol_pin_ileri, 0 );analogWrite( sag_pin_geri, hiz );analogWrite(sol_pin_geri, hiz );
}

void saga_don(uint8_t hiz){
  Serial.print("saga hiz:");
  Serial.print(hiz);
  Serial.print("-");
  analogWrite( sag_pin_ileri, 0 );analogWrite( sol_pin_ileri, hiz );analogWrite( sag_pin_geri, hiz  );analogWrite(sol_pin_geri, 0 );

}

void sola_don(uint8_t hiz){
  Serial.print("sola hiz:");
  Serial.print(hiz);
  Serial.print("-");
  analogWrite( sag_pin_ileri, hiz );analogWrite( sol_pin_ileri, 0 );analogWrite( sag_pin_geri, 0 );analogWrite(sol_pin_geri, hiz  );

}
void dur(){
  analogWrite( sag_pin_ileri, 0 );analogWrite( sol_pin_ileri, 0 );analogWrite( sag_pin_geri, 0 );analogWrite(sol_pin_geri, 0  );
  // Serial.println("dur");
}

void far_ac(){Serial.println("far");}
void projektor_ac(){Serial.println("projektor");}
void bip_ac(){Serial.println("bip");}
void siren_ac(){Serial.println("siren");}

void far_kapat(){ }
void projektor_kapat(){ }
void bip_kapat(){ }
void siren_kapat(){ }

void setup() {
  radio.begin();
  Serial.begin(9600);
  radio.openReadingPipe(0, 0xF0F0F0F0E12E);
  // radio.setPALevel(RF24_PA_MIN); // en düşük seviye enerji tüketimi , düşük sinyal menzili
  radio.startListening();//verici  modunda çalış. 
  Serial.begin(9600);
   //Pin modları tanımla
  pinMode(sag_pin_ileri, OUTPUT);
  pinMode(sag_pin_geri, OUTPUT);
  pinMode(sol_pin_ileri, OUTPUT);
  pinMode(sol_pin_geri, OUTPUT);
  pinMode(projektor_pin, OUTPUT);digitalWrite(projektor_pin,0);
  pinMode(far_pin, OUTPUT);digitalWrite(far_pin,0);
  pinMode(buzzer_pin, OUTPUT);digitalWrite(buzzer_pin,0);
}

void  axis_yaz(char gelen_komut[64] ){ Serial.print(gelen_komut);Serial.print(" | X:");  Serial.print(x_degeri);    Serial.print("-Y:");    Serial.print(y_degeri);    Serial.print("\n"); }

void loop() {
  if (radio.available()) {
   radio.read(&gelen_komut, sizeof(gelen_komut)); 

    strcpy( buff , strtok( gelen_komut,  "," ) );    x_degeri= atoi(buff);
    strcpy( buff , strtok(NULL,  "," ) );    y_degeri= atoi(buff);
    strcpy( buff , strtok(NULL,  "," ) );    btn_joy= atoi(buff);
    strcpy( buff , strtok(NULL,  "," ) );    btn_up= atoi(buff);
    strcpy( buff , strtok(NULL,  "," ) );    btn_down= atoi(buff);
    strcpy( buff , strtok(NULL,  "," ) );    btn_right= atoi(buff);
    strcpy( buff , strtok(NULL,  "," ) );    btn_left= atoi(buff);

    //Serial.print(gelen_komut);  

    if(btn_joy==1 ) dur();

  //if ( (x_degeri ==  505  || x_degeri==504 ) &&  (y_degeri ==524 || y_degeri == 525) ) dur();
  if (y_degeri >=526 && y_degeri < 1024){   ileri_git( map(y_degeri, 526,1023, 0,255) ); axis_yaz(gelen_komut);  } 
  else if (y_degeri >= 0 && y_degeri < 520) {geri_git(map(y_degeri, 520, 0, 0, 255)); axis_yaz(gelen_komut);}
  else if (x_degeri >= 0 && x_degeri < 504) {sola_don(map(x_degeri, 504, 0, 0, 255)); axis_yaz(gelen_komut);}
  else if (x_degeri > 510 && x_degeri < 1024) {saga_don(map(x_degeri, 510, 1023, 0, 255));axis_yaz(gelen_komut);}
  else dur();
  
  // if(btn_joy==1) korna_ac(); else korna_kapt();
  if(btn_up==1) digitalWrite(projektor_pin, HIGH); else digitalWrite(projektor_pin, LOW);
  if(btn_down==1) digitalWrite(far_pin, HIGH); else digitalWrite(far_pin, LOW);
  if(btn_right==1) digitalWrite(buzzer_pin, HIGH); else digitalWrite(buzzer_pin, LOW);
  
  // if(btn_up==1)  far_yak();
  // if(btn_down==1)  far_yak();

  //  Serial.print("\n");
    // Serial.println(btn_left);

  } else{
    //Serial.print("sinyal yok");
      //  all_stop();
  }
}
