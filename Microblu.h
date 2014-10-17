#ifndef _MICROBLU_H
#define _MICROBLU_H

#include <StdFirmata.h>
#include <PubSubClient.h>
#include <MessageHandler.h>
#include <FirmataMessageHandler.h>
#include "Client.h"

class Microblu : public MessageHandler, public FirmataMessageHandler {
  // StdFirmata firmata;
  PubSubClient meshblu;

  char *uuid, *token, *meshbluHost;
  int meshbluPort;

public:
  Microblu(char *uuid, char *token, char *meshbluHost, int meshbluPort);
  void initialize(Client &networkClient);
  void loop();
  void onMessage(char *topic, byte *payload, unsigned int length);
  void onFirmataMessage(char *message);
};

#endif // _MICROBLU_H
