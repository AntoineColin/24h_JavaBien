void setup() {
  // put your setup code here, to run once:
Arene4();
}

void loop() {
  // put your main code here, to run repeatedly:

}

Arene4(){
  //CCW5CW3 composant2
  int n=0,j=1; //nb tours
  for(int i=0; i<sizeof(areneCourante.composant2);i++){
    if((areneCourante.composant2[i] == "C")&&(areneCourante.composant2[i+1] == "C"))
    {
      n = areneCourante.composant2[i+3];
      
      while(LineLVal != 0 && LineRVal != 0 && j !=n*2)
      {// in steps of 1 degree
            motor_LEFT.write(60);
            motor_RIGHT.write(60); 
            if(LineLVal == 0 && LineRVal == 0)
               j++;
      }
      i+=3;
      j=1;
    }else 
    {
      n = areneCourante.composant2[i+2];
      while(LineLVal != 0 && LineRVal != 0 && j !=n*2)
      {// in steps of 1 degree
            motor_LEFT.write(120);
            motor_RIGHT.write(120); 
            if(LineLVal == 0 && LineRVal == 0)
               j++;
      }
      i+=2;
      j=1;
    }
  }
  stopMotors();
}

