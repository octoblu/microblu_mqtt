#ifndef _MICROBLU_H
#define _MICROBLU_H

#define FIRMATA_BUFFER_SIZE 150

#include <StdFirmata.h>
#include <PubSubClient.h>
#include "StreamBuffer.h"
#include "Client.h"
#include "Base64.h"

class Microblu {
  StreamBuffer firmataStream;
  StreamBuffer meshbluStream;

  StdFirmata firmata;
  PubSubClient meshblu;

  char *uuid, *token, *meshbluHost;
  int meshbluPort;
  char base64Buf[20];

public:
  Microblu(char *uuid, char *token, char *meshbluHost, int meshbluPort);
  void initialize(Client &networkClient);
  void loop();
};

#endif // _MICROBLU_H
