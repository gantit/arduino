#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <string.h>
#include "utility/debug.h"
#include <PubSubClient.h>
#include "DHT.h" //cargamos la librería DHT

#define DHTPIN 11 //Seleccionamos el pin en el que se //conectará el sensor
#define DHTTYPE DHT22 //Se selecciona el DHT11 (hay //otros DHT)

// These are the interrupt and control pins
#define ADAFRUIT_CC3000_IRQ   7  // MUST be an interrupt pin!
// These can be any two pins
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10
// Use hardware SPI for the remaining pins
// On an UNO, SCK = 13, MISO = 12, and MOSI = 11
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                         SPI_CLOCK_DIVIDER); // you can change this clock speed but DI
//temperatura
DHT dht(DHTPIN, DHTTYPE);

String W = " ";
String P = " ";
String ouput_str;
char ouput[50];

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("");
  for (int i = 0; i < length; i++) {
    W = W + (char)payload[i];
  }
  readWifiData();

}

//static byte server_ip[4] = { 192, 168, 1, 112 };
uint32_t server_ip = cc3000.IP2U32(192, 168, 1, 112);

Adafruit_CC3000_Client mqttclient = Adafruit_CC3000_Client();
PubSubClient mqttClient(server_ip, 1883, callback, mqttclient);

#define WLAN_SSID       "Livebox-AB67"        // cannot be longer than 32 characters!
#define WLAN_PASS       "6*3*9*5*6*1*0*9*7"
// Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2
#define WLAN_SECURITY   WLAN_SEC_WPA2



/**************************************************************************/
/*!
    @brief  Sets up the HW and the CC3000 module (called automatically
            on startup)
*/
/**************************************************************************/
void setup(void)
{
  Serial.begin(115200);
  dht.begin(); //Se inicia el sensor
  Serial.println(F("Hello, CC3000!\n"));
  Serial.print("Free RAM: "); Serial.println(getFreeRam(), DEC);

  /* Initialise the module */
  Serial.println(F("\nInitialising the CC3000 ..."));
  if (!cc3000.begin()) {
    Serial.println(F("Unable to initialise the CC3000! Check your wiring?"));
    while (1);
  }

  /* Delete any old connection data on the module */
  Serial.println(F("\nDeleting old connection profiles"));
  if (!cc3000.deleteProfiles()) {
    Serial.println(F("Failed!"));
    while (1);
  }

  /* Attempt to connect to an access point */
  char *ssid = WLAN_SSID; 
  Serial.print(F("\nAttempting to connect to ")); Serial.println(ssid);

  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    Serial.println(F("Failed!"));
    while (1);
  }
  Serial.println(F("Connected!"));

  /* Wait for DHCP to complete */
  Serial.println(F("Request DHCP"));
  while (!cc3000.checkDHCP()) {
    delay(100); // ToDo: Insert a DHCP timeout!
  }
  /* Display the IP address DNS, Gateway, etc. */
  while (! displayConnectionDetails()) {
    delay(1000);
  }
}

