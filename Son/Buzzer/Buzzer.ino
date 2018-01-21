#include "pitches.h"

#define SerialPort Serial
#define BUZZER A5

void jouerSon(String partition) {
  
  char note[2];
  int notelue;
  int i = 0;

  
  
  while(partition[i]!='\0') {
    note[0] = partition[i];
    note[1] = partition[i+1];
    
    int noteDuration = 1000 / 4;
    
    if(note[1]=='#'){
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
        default :
        notelue = NOTE_C2;
        break;
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
        default : 
        notelue = NOTE_C4;
        break;
      }
    }
    tone(A5,notelue, 250);
    SerialPort.println(notelue);
    delay(250);
    noTone(A5);

    i++;
  }
}

void setup(){
  SerialPort.begin(9600);
  pinMode(BUZZER, OUTPUT);
  
  char partoche[] = "BA#AG#GFEDC\0";
  
  jouerSon(partoche);
}

void loop() {

}
