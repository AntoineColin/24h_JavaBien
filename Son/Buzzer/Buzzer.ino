#include "pitches.h"

#define SerialPort Serial
#define BUZZER A5

void jouerSon(char partition[]) {
  pinMode(BUZZER, OUTPUT);
  char note[2];
  int notelue;
  SerialPort.begin(9600);
  for(int i = 0; i < sizeof(partition); i++) {
    int noteDuration = 1000 / 8;
    if(note[1]){
      switch(note[0]){
        case 'C' : {
          notelue = NOTE_CS4;
          break;
        }
        case 'D' : {
          notelue = NOTE_DS4;
          break;
        }
        case 'E' : {
          notelue = NOTE_F4;
          break;
        }
        case 'F' : {
          notelue = NOTE_FS4;
          break;
        }
        case 'G' : {
          notelue = NOTE_GS4;
          break;
        }
        case 'A' : {
          notelue = NOTE_AS4;
          break;
        }
        case 'B' : {
          notelue = NOTE_C4;
          break;
        }
      }
    }else{
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
