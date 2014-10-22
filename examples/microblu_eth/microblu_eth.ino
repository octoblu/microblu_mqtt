#include <SPI.h>
#include <Ethernet.h>
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

Microblu *microblu = new Microblu(UUID, TOKEN, MESHBLU_HOST, MESHBLU_PORT);
StdFirmata *firmata = new StdFirmata();
EthernetClient networkClient;

IPAddress ip(192, 168, 200, 172);
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xE1 };

void setup() {
  Serial.begin(9600);

  if (Ethernet.begin(mac) == 0) {
    Ethernet.begin(mac, ip);
  }

  microblu->initialize(networkClient, firmata);
}

void loop() {
  microblu->loop();
}
