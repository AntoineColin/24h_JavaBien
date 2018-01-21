void setup() {
  // put your setup code here, to run once:
Arene4();
}

void loop() {
  // put your main code here, to run repeatedly:

}

Arene4(){
  //CCW5CW3 composant2
  int n=0,delai; //nb tours
  for(int i=0; i<sizeof(areneCourante.composant2);i++){
    if((areneCourante.composant2[i] == "C")&&(areneCourante.composant2[i+1] == "C"))
    {
      n = areneCourante.composant2[i+3];
      for(int j=0;j<n*2;j++){
        for(int pos = 1480; pos < 2100; pos -= 1)  // goes from 0 degrees to 180 degrees
        {                                  // in steps of 1 degree
            motor_LEFT.write(pos);
            motor_RIGHT.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
        } 
      }
      i+=3;
    }else 
    {
      n = areneCourante.composant2[i+2];
      for(int j=0;j<n*2;j++){
        for(int pos = 1480; pos < 2100; pos -= 1)  // goes from 0 degrees to 180 degrees
        {                                  // in steps of 1 degree
            motor_LEFT.write(pos);
            motor_RIGHT.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
        } 
      }
      i+=2;
    }
  }
  stopMotors();
}

