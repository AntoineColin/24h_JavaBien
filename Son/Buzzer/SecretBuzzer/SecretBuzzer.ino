#include "pitches.h"

#define SerialPort Serial
#define BUZZER A5

void jouerSon(char partition[]) {
  
  char note[2];
  int notelue;
  int i = 0;
  
  while(partition[i]!='\0') {
    note[0] = partition[i];
    note[1] = partition[i+1];

    switch(note[0]){
      case 'C' : {
        notelue = NOTE_C3;
        break;
      }
      case 'D' : {
        notelue = NOTE_D3;
        break;
      }
      case 'E' : {
        notelue = NOTE_E3;
        break;
      }
      case 'F' : {
        notelue = NOTE_F3;
        break;
      }
      case 'G' : {
        notelue = NOTE_G3;
        break;
      }
      case 'A' : {
        notelue = NOTE_A3;
        break;
      }
      case 'B' : {
        notelue = NOTE_B2;
        break;
      }
    }
    i++;
    tone(A5,notelue, 200);
    delay(167);
    noTone(A5);
    delay (180);
  }
}

void decripter(char code[]){
  char partition[50];
  int j = 0;
  int i = 0;
  while(code[i]!='\0'){
    SerialPort.println(code[i]);
    switch(code[i]){
      case 'v' : partition[j++] = 'C';
      case 'd' : partition[j++] = 'C';
      case 'c' : partition[j++] = 'C';
      case 'p' : partition[j++] = 'C';
        
      break;
      
      case 'j' : partition[j++] = 'D';
      case 's' : partition[j++] = 'D';
      case 'm' : partition[j++] = 'D';
        
      break;
      
      case 'x' : partition[j++] = 'E';
      case 'f' : partition[j++] = 'E';
      case 'r' : partition[j++] = 'E';
      case 'o' : partition[j++] = 'E';
        
      break;

      case 'q' : partition[j++] = 'F';
      case 'a' : partition[j++] = 'F';
      case 'n' : partition[j++] = 'F';
        
      break;
      
      case 'y' : partition[j++] = 'G';
      case 'g' : partition[j++] = 'G';
      case 'l' : partition[j++] = 'G';
      case 'k' : partition[j++] = 'G';
        
      break;
      
      case 'u' : partition[j++] = 'A';
      case 'b' : partition[j++] = 'A';
      case 'i' : partition[j++] = 'A';
        
      break;
      
      case 'z' : partition[j++] = 'B';
      case 'h' : partition[j++] = 'B';
      case 't' : partition[j++] = 'B';
      case 'e' : partition[j++] = 'B';
        
      break;
      
    }
    i++;
  }
  jouerSon(partition);
}



void setup(){
   SerialPort.begin(9600);
   pinMode(BUZZER, OUTPUT);
  
  decripter("pkpcaomzzkeilepxfpkpcaomzzkeilep\0");
}

void loop() {

}
