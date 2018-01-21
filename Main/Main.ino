#include <Servo.h>
#include <SPI.h>
#include <WiFiST.h>
#include <PubSubClient.h>
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

#define BULK_MAX_PACKET_SIZE            0x00000040
#define PICC_TYPEA_ACConfigA            0x27
#define PICC_TYPEB_ARConfigD            0x0E 
#define PICC_TYPEB_ACConfigA            0x17
#define PICC_TYPEF_ACConfigA            0x17

#define ALREADY_READ -15
#define LineR D0
#define LineL D1

#define LED_GREEN A2
#define LED_RED A3
#define LED_YELLOW A4

struct Arene {
  int id_entier;
  String id_char;
  String composant1; //NOT NULL
  String composant2;
  String composant3;
};


///////////////// PROTOTYPES ////////////////
void stopMotors();
void asservir();

bool NFCDetected();
int readNFCTag();
void parserTag(sURI_Info url);

void doAction();

void callback(char* topic, byte* payload, unsigned int length);
void setup_wifi();
void connectServeur();
void COMServeur();

void Arene0();
void Arene1();
void Arene2();
void Arene3();
void Arene4();
void Arene5();
void Arene6();
void Arene7();
void Arene8();
void Arene9();
void Arene10();

///////////////// DECLARATION DES VARIABLES ////////////////
/****************DEBUT**WIFI**CONNECTION*********************************/
SPIClass SPI_3(PC12, PC11, PC10);
WiFiClass WiFi(&SPI_3, PE0, PE1, PE8, PB13);
char server[]= "24hducode.spc5studio.com";
int status = WL_IDLE_STATUS;     // the Wifi radio's status
WiFiClient espClient;
PubSubClient client(server,1883,callback,espClient);
/****************FIN**WIFI**CONNECTION*********************************/

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

struct Arene areneCourante;

int LineRVal; //0 blanc       1 noir
int LineLVal;

bool actionDone;

Servo motor_LEFT;
Servo motor_RIGHT;


/*char ssid[] = "OnePlus3T";     //  your network SSID (name)
char pass[] = "JavaBien;24h";  // your network password*/
char ssid[] = "24HDUCODE";     //  your network SSID (name)
char pass[] = "2018#24hcode!";  // your network password
String messageToSend;

int lastIDArene;
int truc;

///////////////// INITIALISATION ////////////////

void setup() {
  Serial.begin(9600);

  ConfigManager_HWInit();
  
  pinMode(LineR, INPUT);
  pinMode(LineL, INPUT);
  
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);

  motor_LEFT.attach(D6, 900, 2100);
  motor_RIGHT.attach(D5, 900, 2100);

  areneCourante.id_entier = -1;
  setup_wifi();
  lastIDArene = -1;
  truc = 0;
  connectServeur();
}

///////////////// PROGRAMME PRINCIPAL ////////////////
void loop() {
  delay(10);
  if(NFCDetected()) {
    truc = readNFCTag();
    Serial.println("NFC detected");
    if(truc != 0) { //Si ça s'est pas terminé normalement, on reprend l'asserv
      asservir();
      Serial.println("Abandon NFC (deja fait)");
    } else {
      Serial.println("NFC go to Action");
      stopMotors();
      doAction();
      lastIDArene = areneCourante.id_entier;
      COMServeur();
      //client.loop();
    }
  }else {
    asservir();
  }
}


///////////////// DEFINITION DES FONCTIONS ////////////////

void stopMotors() {
  motor_LEFT.write(1480);
  motor_RIGHT.write(1480);
  return;
}

void asservir() {
  LineLVal = digitalRead(LineL);
  LineRVal = digitalRead(LineR);

  if(LineLVal == 0 && LineRVal == 0) {//Avancer tout droit
      motor_LEFT.write(1550);
      motor_RIGHT.write(1410);
  } else if(LineLVal == 0 && LineRVal == 1) { //Tourner à droite
      motor_LEFT.write(1550);
      motor_RIGHT.write(1550);
  } else if(LineLVal == 1 && LineRVal == 0) { //Tourner à gauche
      motor_LEFT.write(1410);
      motor_RIGHT.write(1410);
  } else if(LineLVal == 1 && LineRVal == 1) { //Attendre
      stopMotors();
      //Peut être rajouter quelque chose pour débloquer la situation
  }
}

bool NFCDetected() { //Renvoie true si le NFC est détecté
  TagType = ConfigManager_TagHunting(TRACK_NFCTYPE2);
  if(TagType == TRACK_NFCTYPE2) {
    digitalWrite(LED_RED , HIGH);
    return true;
  } else {
    return false;
  }
}

int readNFCTag() { //Lit le tag NFC, l'enregistre dans l'arène courante
  memset(url.Information,'\0',400); /*Clear url buffer before reading*/
  if (TagType == TRACK_NFCTYPE2) {
    if (PCDNFCT2_ReadNDEF() == RESULTOK) {
      digitalWrite(LED_RED , LOW);
      digitalWrite(LED_YELLOW , HIGH);
      memset(NDEF_Buffer,'\0',20); /* Avoid printing useless characters */
      if(NDEF_IdentifyNDEF( &RecordStruct, NDEF_Buffer) == RESULTOK && RecordStruct.TypeLength != 0) {
        if (NDEF_ReadURI(&RecordStruct, &url)== RESULTOK) {
          digitalWrite(LED_YELLOW , LOW);
          digitalWrite(LED_GREEN , HIGH);
          parserTag(url);
          digitalWrite(LED_GREEN, LOW);
          if(areneCourante.id_entier == lastIDArene)
            return ALREADY_READ;
          else
            return 0;
        } else {
          return -1;
        }
      } else {
        return -1;
      }
    } else {
      return -1;
    }
  } else {
    return -1;
  }
}


void parserTag(sURI_Info url) {
  String message(url.URI_Message);
  int index[3];

  areneCourante.id_char = "";
  areneCourante.id_entier = -1;
  areneCourante.composant1 = "";
  areneCourante.composant3 = "";
  areneCourante.composant2 = "";
  
  index[0] = message.indexOf(':');
  areneCourante.id_char = message.substring(1, index[0]);
  
  //Si id = 5a, 7a, 9a alors retirer extension
  if(areneCourante.id_char.indexOf("5") > 0 || areneCourante.id_char.indexOf("7") > 0 || areneCourante.id_char.indexOf("9") > 0) { //Retirer les caractères derrière
    areneCourante.id_entier = areneCourante.id_char.substring(1, 2).toInt();
  } else {
    areneCourante.id_entier = areneCourante.id_char.toInt();
  }
  
  switch(areneCourante.id_entier) {
    case 1: case 2: case 3: case 4: case 6: case 8: case 5:
      index[1] = message.lastIndexOf(':');
      areneCourante.composant1 = message.substring(index[0]+1, index[1]);
      areneCourante.composant2 = message.substring(index[1]+1);
      break;
    case 10: case 9:
      areneCourante.composant1 = message.substring(index[0]+1);
      break;
    case 7:
      areneCourante.composant1 = message.substring(index[0]+1, index[1]);
      areneCourante.composant2 = message.substring(index[1]+1, index[2]);
      areneCourante.composant3 = message.substring(index[2]+1);
      break;
    default: break;
  }
  return;
}

void doAction() {
  messageToSend = "A" + areneCourante.id_char + ":";
  switch(areneCourante.id_entier) {
    case 0: Arene0(); break;
    case 1: Arene1(); break;
    case 2: Arene2(); break;
    case 3: Arene3(); break;
    case 4: Arene4(); break;
    case 5: Arene5(); break;
    case 6: Arene6(); break;
    case 7: Arene7(); break;
    case 8: Arene8(); break;
    case 9: Arene9(); break;
    case 10: Arene10(); break;
    default: break;
  }
  return;
}

void setup_wifi(){  
  // Initialize the WiFi device :
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi module not present");
    // don't continue:
    while (true);
  }
  // Print firmware version
  String fv = WiFi.firmwareVersion();
  Serial.print("Firwmare version : ");
  Serial.println(fv);
  if (fv != "C3.5.2.3.BETA9")
  {
    Serial.println("Please upgrade the firmware");
  }
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  // you're connected now, so print out the data:
  Serial.println("You're connected to the network");
}

void callback(char* topic, byte* payload, unsigned int length) {
  /*Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");*/
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
void connectServeur() {
  if (client.connect("teamA","Bulbizarre", "G3526T49")) {
    if(client.subscribe("24hcode/teamA/742a3/broker2device")) {
      Serial.println("subscribe");
    } else {
      Serial.println("non subscribe");
    }
  } else{
    Serial.println("client non connecte");
  }
  return;
}

void COMServeur() {
  unsigned long timer = millis();
  while(!client.publish("24hcode/teamA/742a3/device2broker", messageToSend.c_str()));
  Serial.println("publish : '" + messageToSend + "'");
  return;
}



void Arene0() {
  return;
}
void Arene1() {
  messageToSend += "Hello 24h du code!";
  return;
}
void Arene2() {
  messageToSend += areneCourante.composant2;
  return;
}
void Arene3() {
  messageToSend += areneCourante.composant2;
  //JouerSon(partition = areneCourante.composant2)
  return;
}
void Arene4() { //360° -- CCWn
  return;
}
void Arene5() { //César PhraseDécodée
  return;
}
void Arene6() { //Repos/Caresse - nbCaresses
  return;
}
void Arene7() { //SpyDJ -- MusiqueCodée
  return;
}
void Arene8() {
  return;
}
void Arene9() {
  return;
}
void Arene10() {
  return;
}

