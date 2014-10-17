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
    Serial.println("Error connecting to Meshblu");
    return;
  }
  firmata.initialize();
}

void Microblu::loop() {
  meshblu.loop();
  // while(message = meshblu->getMessage()) {
  //   firmata->
  // }

  // while(Firmata.available())
  //   Firmata.processInput();
}

void Microblu::onMessage(char* topic, byte* payload, unsigned int length) {
  Serial.println("onMessage");
  Serial.println(topic);
}

