#include <Microblu.h>
#include <SPI.h>
#include <WiFi.h>

#define MESHBLU_HOST "mqtt.octoblu.com"
#define MESHBLU_PORT 1883
#define UUID  "XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX"
#define TOKEN "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"

#define WIFI_SSID       "<ssid>"
#define WIFI_PASSWORD   "<password>"

Microblu microblu(UUID, TOKEN, MESHBLU_HOST, MESHBLU_PORT);
WiFiClient networkClient;

void setup() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  microblu.initialize(&networkClient);
}

void loop() {
  microblu.loop();
}
