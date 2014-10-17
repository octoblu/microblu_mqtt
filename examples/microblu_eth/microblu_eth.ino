#include <PubSubClient.h>
#include <Microblu.h>
#include <SPI.h>
#include <Ethernet.h>

#define MESHBLU_HOST "mqtt.octoblu.com"
#define MESHBLU_PORT 1883
#define UUID  "68ce70e1-5636-11e4-a414-671a5d380d7e"
#define TOKEN "661sg1wxr61ug14ifgtnggr1xwfry66r"

Microblu microblu(UUID, TOKEN, MESHBLU_HOST, MESHBLU_PORT);
EthernetClient networkClient;

IPAddress ip(192, 168, 200, 177);
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

void setup() {
  Serial.begin(9600);

  Serial.println("Connecting to Ethernet...");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }
  Serial.println("Connected");

  microblu.initialize(networkClient);
}

void loop() {
  microblu.loop();
}
