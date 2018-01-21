
#define SerialPort Serial


String cesar(char code[]){

  char reponse[60];
  int i = 0;
  while(code[i]!='\0'){
    
    reponse[i] = (char) (((int)code[i]+8-65)%26+65);
    i++;
  }
  return reponse;
}

void setup() {
  SerialPort.begin(9600);
  String blo = cesar("MFKLEPPPAAWLVWKBWMPSNAFVMFME");
  SerialPort.println(blo);  
}


void loop() {
  
}
