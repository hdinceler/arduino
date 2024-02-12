#include <Servo.h>
#define motor_pin 9
Servo servoMotor;
String kelime;
int aci;
void setup() {
  pinMode(motor_pin, OUTPUT);
  servoMotor.attach(motor_pin);






  
  Serial.begin(9600);
}
void loop() {
  if( Serial.available() ){
    kelime=  Serial.readString();
    aci= atoi(kelime.c_str() );
      servoMotor.write(aci); 
  }
}
