#ifndef _MICROBLU_H
#define _MICROBLU_H

// #include <StdFirmata.h>
#include <PubSubClient.h>
#include <MessageHandler.h>
#include "Client.h"

class Microblu : public MessageHandler {
  // Firmata firmata;
  PubSubClient meshblu;

  char *uuid, *token, *meshbluHost;
  int meshbluPort;

public:
  Microblu(char *uuid, char *token, char *meshbluHost, int meshbluPort);
  void initialize(Client &networkClient);
  void loop();
  // void (*virtualOnMessage)(char *topic, byte *payload, unsigned int length);
  void onMessage(char *topic, byte *payload, unsigned int length);
};

#endif // _MICROBLU_H
