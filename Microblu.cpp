#include "Microblu.h";

Microblu::Microblu(char *uuid, char *token, char *meshbluHost, int meshbluPort) {
  this->uuid = uuid;
  this->token = token;
  this->meshbluHost = meshbluHost;
  this->meshbluPort = meshbluPort;
  this->firmataStream = StreamBuffer();
  this->meshbluStream = StreamBuffer();
}

void Microblu::initialize(Client &networkClient, StdFirmata *newFirmata) {
  meshblu = PubSubClient(meshbluHost, meshbluPort, NULL, networkClient, meshbluStream);
  firmata = newFirmata;

  char clientId[40] = "mb_";
  strcat(clientId, uuid);

  Serial.println("Con");
  if(!meshblu.connect(clientId, uuid, token)){
    return;
  }

  Serial.println("GO");
  if (meshblu.subscribe(uuid)) {
    Serial.println("S");
    firmata->initialize(firmataStream);
    Serial.println("FIRM");
  } else {
    Serial.println("FAIL");
  }
}

void Microblu::loop() {
  meshblu.loop();
  if (meshbluStream.available()) {
    Serial.println("MB Av");
    base64_decode_stream(meshbluStream, firmataStream);
  }
  firmata->loop();
  if (firmataStream.available()) {
    Serial.println(firmataStream.available());
    base64_encode_stream(firmataStream, base64Buf);
    Serial.println(base64Buf);
    // meshblu.publish("tb", base64Buf);
  }
}
