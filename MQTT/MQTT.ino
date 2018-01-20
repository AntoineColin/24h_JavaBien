#include <SPI.h>
#include <WiFiST.h>
#include <PubSubClient.h>

void callback(char* topic, byte* payload, unsigned int length);
void setup_wifi();
//void A1(char message[]);
//void A2(char message2[]);
void envoiMQTT(char ssid[],char pass[]);

SPIClass SPI_3(PC12, PC11, PC10);
WiFiClass WiFi(&SPI_3, PE0, PE1, PE8, PB13);

/*char ssid[] = "OnePlus3T";         //  your network SSID (name)
char pass[] = "JavaBien;24h";  // your network password
//char ssid[] = "24HDUCODE";         //  your network SSID (name)
//char pass[] = "2018#24hcode";  // your network password
*/

/****************DEBUT**WIFI**CONNECTION*********************************/
char server[]= "24hducode.spc5studio.com";
int status = WL_IDLE_STATUS;     // the Wifi radio's status
WiFiClient espClient;
PubSubClient client(server,1883,callback,espClient);
/****************FIN**WIFI**CONNECTION*********************************/

int enigme = 0;
//char message[40];
void setup() {
  /*switch(enigme){
  case 0:*/
    envoiMQTT("OnePlus3T","JavaBien;24h","Hello from Bulbizarre"); 
 /*   break;
  case 1:
    A1("A1:G3526T49:742a3");
    break;
  case 2:
    A2("A2:Circuit:1234");
    break;
  default:
    Serial.println("Mauvaise valeur");
    break;
  }*/
  
}

void loop() {
  // check the network connection once every 10 seconds:
  client.loop(); //permet d'attendre l'affichage de la reponse du serveur
}

/********************************************************/
/*******************DEBUT***ENIGMES**********************/
/*void A1(char message[])
{
  if (message == "A1:G3526T49:742a3"){
      envoiMQTT("OnePlus3T","JavaBien;24h","A1:Hello 24h du code!"); 
  }else{
    Serial.println("Le message ne correspond pas");
  }
}
void A2(char message2[])
{
  if (message == "A2:Circuit:1234"){
      envoiMQTT("OnePlus3T","JavaBien;24h","A2:1234"); 
  }else{
    Serial.println("Le message ne correspond pas");
  }
}*/

/*********************FIN***ENIGMES**********************/
/********************************************************/



/********************************************************/
/**************DEBUT***ENVOI***MQQT**********************/
void setup_wifi(char ssid[],char pass[]){
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
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
  Serial.print("You're connected to the network");
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

void envoiMQTT(char ssid[],char pass[],char message[40]){
  setup_wifi(ssid,pass);
  if (client.connect("teamA","Bulbizarre", "G3526T49")) {
    Serial.println("client connecte");
  }else{
    Serial.println("client non connecte");
  }
  if(client.subscribe("24hcode/teamA/742a3/broker2device"))
  {
     Serial.println("subscribe");
  }else{
     Serial.println("non subscribe");
  }
  if(client.publish("24hcode/teamA/742a3/device2broker",message))
  {
    Serial.println("publish");
  }else{
    Serial.println("non publish");
  }
}
/****************FIN***ENVOI***MQQT**********************/
/********************************************************/
