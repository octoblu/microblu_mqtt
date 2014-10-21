#include "Microblu.h";

Microblu::Microblu(char *uuid, char *token, char *meshbluHost, int meshbluPort) {
  this->uuid = uuid;
  this->token = token;
  this->meshbluHost = meshbluHost;
  this->meshbluPort = meshbluPort;
  this->firmataStream = StreamBuffer();
  this->meshbluStream = StreamBuffer();
}

void Microblu::initialize(Client &networkClient) {
  meshblu = PubSubClient(meshbluHost, meshbluPort, NULL, networkClient, meshbluStream);

  char clientId[40] = "mb_";
  strcat(clientId, uuid);

  if(!meshblu.connect(clientId, uuid, token)){
    return;
  }

  if (meshblu.subscribe(uuid)) {
    Serial.println("Sub");
    firmata.initialize(firmataStream);
  }
}

void Microblu::loop() {
  meshblu.loop();
  if (meshbluStream.available()) {
    base64_decode_stream(meshbluStream, firmataStream);
  }
  if (firmataStream.available()) {
    Serial.println(firmataStream.available());
  }
  firmata.loop();
  if (firmataStream.available()) {
    base64_encode_stream(firmataStream, base64Buf);
    Serial.println(base64Buf);
    // meshblu.publish("tb", base64Buf);
  }
}
