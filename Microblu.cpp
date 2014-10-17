#include "Microblu.h";

Microblu::Microblu(char *uuid, char *token, char *meshbluHost, int meshbluPort) {
  this->uuid = uuid;
  this->token = token;
  this->meshbluHost = meshbluHost;
  this->meshbluPort = meshbluPort;
}

void Microblu::initialize(Client &networkClient) {

  meshblu = PubSubClient(meshbluHost, meshbluPort, this, networkClient);

  char clientId[40] = "mb_";
  strcat(clientId, uuid);

  if(!meshblu.connect(clientId, uuid, token)){
    return;
  }

  meshblu.subscribe(uuid);
  // firmata.initialize();
}

void Microblu::loop() {
  meshblu.loop();
  // firmata.loop();
}

void Microblu::onMessage(char* topic, byte* payload, unsigned int length) {
  Serial.println(topic);
}

void Microblu::onFirmataMessage(char *message) {
  Serial.println(message);
}

