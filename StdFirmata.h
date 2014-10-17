#ifndef _STD_FIRMATA_H
#define _STD_FIRMATA_H

#include <SPI.h>
#include <StreamBuffer.h>
#include <ringbuffer.h>
#include <b64.h>
#include <Servo.h>
#include <Wire.h>
#include <Firmata.h>

class StdFirmata {
public:
  StdFirmata();
  void initialize();
};

#endif // _STD_FIRMATA_H
