#include <PubSubClient.h>
#include <Microblu.h>
#include <SPI.h>
#include <WiFi.h>

#define MESHBLU_HOST "mqtt.octoblu.com"
#define MESHBLU_PORT 1883
#define UUID  "68ce70e1-5636-11e4-a414-671a5d380d7e"
#define TOKEN "661sg1wxr61ug14ifgtnggr1xwfry66r"

#define WIFI_SSID       "OB-HQ"
#define WIFI_PASSWORD   "0ct0b1u2014"

Microblu microblu(UUID, TOKEN, MESHBLU_HOST, MESHBLU_PORT);
WiFiClient networkClient;

int status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(9600);

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while(true);
  }

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(WIFI_SSID);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    // wait 10 seconds for connection:
    delay(10000);
  }

  microblu.initialize(networkClient);
}

void loop() {
  microblu.loop();
}
