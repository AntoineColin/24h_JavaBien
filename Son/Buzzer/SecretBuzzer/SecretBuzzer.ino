#include "pitches.h"

#define SerialPort Serial
#define BUZZER A5

void decripter(char code[]){
  char partition[50];
  int j = 0;
  for(int i = 0; i< sizeof(code); i++){
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
  }
}

void jouerSon(char partition[]) {
  pinMode(BUZZER, OUTPUT);
  char note[2];
  int notelue;
  SerialPort.begin(9600);
  for(int i = 0; i < sizeof(partition); i++) {
    int noteDuration = 1000 / 8;
    switch(note[0]){
      case 'C' : {
        notelue = NOTE_C4;
        break;
      }
      case 'D' : {
        notelue = NOTE_D4;
        break;
      }
      case 'E' : {
        notelue = NOTE_E4;
        break;
      }
      case 'F' : {
        notelue = NOTE_F4;
        break;
      }
      case 'G' : {
        notelue = NOTE_G4;
        break;
      }
      case 'A' : {
        notelue = NOTE_A4;
        break;
      }
      case 'B' : {
        notelue = NOTE_B4;
        break;
      }
    }
    tone(BUZZER,notelue, 200);
    SerialPort.println("Note");
    
  }
}

void setup(){
  
  jouerSon("DADADABDBAD");
}

void loop() {

}
