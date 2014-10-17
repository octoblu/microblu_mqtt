#ifndef _FIRMATA_MESSAGE_HANDLER_H
#define _FIRMATA_MESSAGE_HANDLER_H

class FirmataMessageHandler
{
public:
  virtual void onFirmataMessage(char* message);
};

#endif _FIRMATA_MESSAGE_HANDLER_H
