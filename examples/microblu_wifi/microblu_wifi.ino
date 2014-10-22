#include <SPI.h>
#include <WiFi.h>
#include <Servo.h>
#include <Wire.h>
#include <Firmata.h>
#include <Microblu.h>
#include <StdFirmata.h>
#include <PubSubClient.h>

#define MESHBLU_HOST "192.168.200.43"
#define MESHBLU_PORT 1883
#define UUID  "68ce70e1-5636-11e4-a414-671a5d380d7e"
#define TOKEN "661sg1wxr61ug14ifgtnggr1xwfry66r"

#define WIFI_SSID       "OB-HQ"
#define WIFI_PASSWORD   "0ct0b1u2014"

Microblu *microblu  = new Microblu(UUID, TOKEN, MESHBLU_HOST, MESHBLU_PORT);
StdFirmata *firmata = new StdFirmata();
WiFiClient networkClient;

int status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(9600);
  Serial.println("SYSTEM REBOOT");

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while(true);
  }

  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(WIFI_SSID);
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    delay(10000);
  }

  microblu->setup(networkClient, firmata);
}

void loop() {
  microblu->loop();
}
