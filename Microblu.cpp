#include "Microblu.h";

Microblu::Microblu(char *uuid, char *token, char *meshbluHost, int meshbluPort) {
  this->uuid = uuid;
  this->token = token;
  this->meshbluHost = meshbluHost;
  this->meshbluPort = meshbluPort;
  this->firmataStream = CrossStreamBuffer();
  this->inFirmataStream = StreamBuffer(firmataStream.inBuffer);
  this->outFirmataStream = StreamBuffer(firmataStream.outBuffer);
  this->meshbluStream = StreamBuffer();
}

void Microblu::setup(Client &networkClient, StdFirmata *newFirmata) {
  meshblu = PubSubClient(meshbluHost, meshbluPort, NULL, networkClient, meshbluStream);
  firmata = newFirmata;

  char clientId[40] = "mb_";
  strcat(clientId, uuid);

  if(!meshblu.connect(clientId, uuid, token)){
    Serial.println(F("Failed to connect..."));
    return;
  }

  if (meshblu.subscribe(uuid)) {
    firmata->setup(firmataStream);
  }
}

void Microblu::loop() {
  meshblu.loop();
  if (meshbluStream.available()) {
    base64_decode_stream(meshbluStream, inFirmataStream);
  }
  firmata->loop();
  if (outFirmataStream.available()) {
    base64_encode_stream(outFirmataStream, base64Buf);
    meshblu.publish("tb", base64Buf);
  }
}
