/*
 This example connects to an WPA2-encrypted Wifi network.
 Then it prints the  MAC address of the Wifi module,
 the IP address obtained, and other network details.
 */
#include <SPI.h>
#include <WiFiST.h>
#include <PubSubClient.h>
/*
  The following configuration is dedicated to the DISCO L475VG IoT board.
  You should adapt it to your board.

Configure SPI3:
 * MOSI: PC12
 * MISO: PC11
 * SCLK: PC10

Configure WiFi:
 * SPI         : SPI3
 * Cs          : PE0
 * Data_Ready  : PE1
 * reset       : PE8
 * wakeup      : PB13
 */

SPIClass SPI_3(PC12, PC11, PC10);
WiFiClass WiFi(&SPI_3, PE0, PE1, PE8, PB13);

char ssid[] = "OnePlus3T";         //  your network SSID (name)
char pass[] = "JavaBien;24h";  // your network password
//char ssid[] = "24HDUCODE";         //  your network SSID (name)
//char pass[] = "2018#24hcode";  // your network password
char server[]= "24hducode.spc5studio.com";
int status = WL_IDLE_STATUS;     // the Wifi radio's status

void callback(char* topic, byte* payload, unsigned int length);
void setup_wifi();
void concatenerReponse();

WiFiClient espClient;
PubSubClient client(server,1883,espClient);
char message[40] = "Hello from Bulbizarre";

void setup() {
  setup_wifi();
  if (client.connect("teamA","Bulbizarre", "G3526T49")) {
    Serial.println("client connecte");
  }else{
    Serial.println("client non connecte");
  }

  client.setCallback(callback);

  if(client.publish("24hcode/teamA/742a3/device2broker",message))
  {
    Serial.println("publish");
  }else{
    Serial.println("non publish");
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

void loop() {
  // check the network connection once every 10 seconds:
  delay(10000);
}

void setup_wifi(){
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
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void concatenerReponse()
{
  
}


