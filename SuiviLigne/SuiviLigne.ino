#include <Servo.h> 

/**
 * 0 : blanc
 * 1 : noir
 */
#define LineR D0
#define LineL D1


Servo motor_LEFT;
Servo motor_RIGHT;

int LineRVal;
int LineLVal;

void setup() {

  Serial.begin(9600);
  
  pinMode(LineR, INPUT);
  pinMode(LineL, INPUT);

  motor_LEFT.attach(D6, 900, 2100);
  motor_RIGHT.attach(D5, 900, 2100);

}

void loop() {
  delay(10);
  LineLVal = digitalRead(LineL);
  LineRVal = digitalRead(LineR);
  
  //Serial.print(LineLVal); Serial.print(" "); Serial.print(LineRVal);

  if(LineLVal == 0 && LineRVal == 0) {//Avancer tout droit
      motor_LEFT.write(1600);
      motor_RIGHT.write(1400);
      //Serial.println(" : Tout droit !!!");
  } else if(LineLVal == 0 && LineRVal == 1) { //Tourner à droite
      motor_LEFT.write(1600);
      motor_RIGHT.write(1600);
      //Serial.println(" : Droite");
  } else if(LineLVal == 1 && LineRVal == 0) { //Tourner à gauche
      motor_LEFT.write(1400);
      motor_RIGHT.write(1400);
      //Serial.println(" : Gauche");
  } else if(LineLVal == 1 && LineRVal == 1) { //Attendre
      motor_LEFT.write(1480);
      motor_RIGHT.write(1480);
      //Serial.println(" : Attente");
  }
}
