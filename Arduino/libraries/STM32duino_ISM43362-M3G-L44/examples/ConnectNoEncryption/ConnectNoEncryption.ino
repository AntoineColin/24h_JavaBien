/*

 This example connects to an unencrypted Wifi network.
 Then it prints the  MAC address of the Wifi module,
 the IP address obtained, and other network details.
 It also set the MAC address of the device.
 */
#include <SPI.h>
#include <WiFiST.h>

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

char ssid[] = "ST_test";                      // the name of your network
int status = WL_IDLE_STATUS;                  // the Wifi radio's status
uint8_t macAddrDevice[6] = {0,1,2,3,4,5};     // the mac address you want set in the WiFi device

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Initialize the device :
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi device not detected");
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

  // Set Mac Address of the device on the board optional)
  // WiFi.setMac(macAddrDevice);
  // Be careful, if setting the MAC adress, you could lose
  // previously assigned MAC address. If only for test,
  // you can save your current MAC address, change it,
  // then set it back to original one.

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to open SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the data:
  Serial.print("You're connected to the network");
  printCurrentNet();
  printWifiData();
}

void loop() {
  // check the network connection once every 10 seconds:
  delay(10000);
  printCurrentNet();
}

void printWifiData() {
  // print your WiFi device's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);

  // print your subnet mask:
  IPAddress subnet = WiFi.subnetMask();
  Serial.print("NetMask: ");
  Serial.println(subnet);

  // print your gateway address:
  IPAddress gateway = WiFi.gatewayIP();
  Serial.print("Gateway: ");
  Serial.println(gateway);
}

void printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the MAC address of the router you're attached to:
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  Serial.print(bssid[5], HEX);
  Serial.print(":");
  Serial.print(bssid[4], HEX);
  Serial.print(":");
  Serial.print(bssid[3], HEX);
  Serial.print(":");
  Serial.print(bssid[2], HEX);
  Serial.print(":");
  Serial.print(bssid[1], HEX);
  Serial.print(":");
  Serial.println(bssid[0], HEX);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
}
