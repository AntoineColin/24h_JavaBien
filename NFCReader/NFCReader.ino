/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "stdbool.h"
#include "string.h"
#include "lib_NDEF_URI.h"
#include "lib_NDEF_SMS.h"
#include "lib_NDEF_Text.h"
#include "lib_NDEF_Email.h"
#include "lib_NDEF_Geo.h"
#include "lib_95HFConfigManager.h"
#include "miscellaneous.h"
#include "lib_95HFConfigManager.h"
#include "lib_wrapper.h"
#include "lib_NDEF_URI.h"
#include "drv_spi.h"

#define SerialPort Serial

#define LED_GREEN A2
#define LED_RED A3
#define LED_YELLOW A4

struct Arene {
  char* id;
  char* composant1;
  char* composant2;
  char* composant3;
};

struct Arene areneCourante;

/* Exported define -----------------------------------------------------------*/
#define BULK_MAX_PACKET_SIZE            0x00000040

/* Regarding board antenna (and matching) appropriate 
value may be modified to optimized RF performances */
/* Analogue configuration register
 ARConfigB	bits  7:4	MOD_INDEX	Modulation index to modulator
                      3:0	RX_AMP_GAIN	Defines receiver amplifier gain
For type A you can also adjust the Timer Window
*/

/******************  PICC  ******************/
/* ISO14443A */
#define PICC_TYPEA_ACConfigA            0x27  /* backscaterring */

/* ISO14443B */
#define PICC_TYPEB_ARConfigD            0x0E  /* card demodulation gain */
#define PICC_TYPEB_ACConfigA            0x17  /* backscaterring */

/* Felica */
#define PICC_TYPEF_ACConfigA            0x17  /* backscaterring */

/* Private variables ---------------------------------------------------------*/

uint8_t TT1Tag[NFCT1_MAX_TAGMEMORY];
uint8_t TT2Tag[NFCT2_MAX_TAGMEMORY];
uint8_t TT3Tag[NFCT3_MAX_TAGMEMORY];
uint8_t *TT3AttribInfo = TT3Tag, *TT3NDEFfile = &TT3Tag[NFCT3_ATTRIB_INFO_SIZE];
uint8_t CardNDEFfileT4A [NFCT4_MAX_NDEFMEMORY];
uint8_t CardNDEFfileT4B [NFCT4_MAX_NDEFMEMORY];
uint8_t TT5Tag[NFCT5_MAX_TAGMEMORY];

sURI_Info url; 
extern uint8_t NDEF_Buffer []; 
sRecordInfo_uri RecordStruct;

int8_t TagType = TRACK_NOTHING;
bool terminal_msg_flag = false ;
static char dataOut[256];

void setup() {
  // 95HF HW Init
  ConfigManager_HWInit();

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);

  
  areneCourante.id = (char*) malloc(8);
  areneCourante.composant1 = (char*) malloc(256);
  areneCourante.composant2 = (char*) malloc(256);
  areneCourante.composant3 = (char*) malloc(256);
  
  terminal_msg_flag = true;
  
  SerialPort.begin(9600);
}

void loop()
{
  TagType = ConfigManager_TagHunting(TRACK_ALL);
  if(TagType == TRACK_NFCTYPE2) {
    digitalWrite(LED_RED , HIGH);
    if(terminal_msg_flag == true ) {
      terminal_msg_flag = false ;
      SerialPort.print( "\r\n\r\nTRACK_NFCTYPE2 NFC tag detected nearby");
    }
    delay(1000);
    memset(url.Information,'\0',400); /*Clear url buffer before reading*/
    if (TagType == TRACK_NFCTYPE2) {
      if ( PCDNFCT2_ReadNDEF() == RESULTOK ) {
        digitalWrite(LED_RED , LOW);
        digitalWrite(LED_YELLOW , HIGH);
        delay(1000);
        memset(NDEF_Buffer,'\0',20); /* Avoid printing useless characters */
        if(NDEF_IdentifyNDEF( &RecordStruct, NDEF_Buffer) == RESULTOK && RecordStruct.TypeLength != 0) {
          if (NDEF_ReadURI(&RecordStruct, &url)==RESULTOK) {
            snprintf( dataOut, 256, "\r\n\r\n--------------------\r\n*****URI Reader*****\r\n--------------------\r\nURI Information read successfully from the tag: \r\n     URI Information: [%s], \r\n     URI Protocol: [%s] ,  \r\n     URI Message: [%s]", (char *)url.Information, (char *)url.protocol, (char *)url.URI_Message );
            SerialPort.print( dataOut );
            digitalWrite(LED_YELLOW , LOW);
            digitalWrite(LED_GREEN , HIGH);
            areneCourante = parserTag(url);
            delay(5000);
            digitalWrite(LED_GREEN, LOW);
          }
        }
      }
    }
  }
  delay(300);
}

/**
 * A<id-arène>:<thème>:<énoncé>
 * (char *)url.URI_Message
 */
Arene parserTag(sURI_Info url) {
  String message(url.URI_Message);
  String id;
  String composant[3];

  int index[3];
  index[0] = message.indexOf(':');
  id = message.substring(1, index[0]);
  
  //Si id = 5a, 7a, 9a alors retirer extension
  if(id.indexOf("5") > 0 || id.indexOf("7") > 0 || id.indexOf("9") > 0) { //Retirer les caractères derrière
    id = id.substring(1, 2);
  }

  Serial.println("");Serial.println("");
  Serial.print(id); Serial.print(" ");
  switch(id.toInt()) {
    case 1: case 2: case 3: case 4: case 6: case 8: case 5:
      index[1] = message.lastIndexOf(':');
      composant[0] = message.substring(index[0]+1, index[1]);
      composant[1] = message.substring(index[1]+1);
      Serial.print(composant[0]); Serial.print(" ");
      Serial.print(composant[1]); Serial.print(" ");
      break;
    case 10: case 9:
      composant[0] = message.substring(index[0]+1);
      Serial.print(composant[0]); Serial.print(" ");
      break;
    case 7:
      composant[0] = message.substring(index[0]+1, index[1]);
      composant[1] = message.substring(index[1]+1, index[2]);
      composant[2] = message.substring(index[2]+1);
      Serial.print(composant[0]); Serial.print(" ");
      Serial.print(composant[1]); Serial.print(" ");
      Serial.print(composant[2]); Serial.print(" ");
      break;
    default: break;
  }  
}


