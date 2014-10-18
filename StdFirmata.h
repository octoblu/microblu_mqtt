#ifndef _STD_FIRMATA_H
#define _STD_FIRMATA_H

#define B64_DEBUG true
#include <SPI.h>
#include <StreamBuffer.h>
#include <ringbuffer.h>
#include <b64.h>
#include <Servo.h>
#include <Wire.h>
#include <Firmata.h>
#include <FirmataMessageHandler.h>


class StdFirmata {
  FirmataMessageHandler *messageHandler;
public:
  StdFirmata();
  void initialize();
  void initialize(FirmataMessageHandler *messageHandler);
  void receiveMessage(byte* payload, unsigned int length);
  void loop();
};

#endif // _STD_FIRMATA_H
