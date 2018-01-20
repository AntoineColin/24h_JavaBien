#include <Servo.h> 

Servo motor_LEFT;
Servo motor_RIGHT;

void setup() {
    
  motor_LEFT.attach(D6, 900, 2100);
  motor_RIGHT.attach(D5, 900, 2100);

}

void loop() {
  asservir();
}


void asservir() {
  motor_LEFT.write(1500);
  motor_RIGHT.write(1500);
}

