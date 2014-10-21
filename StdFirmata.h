#ifndef _STD_FIRMATA_H
#define _STD_FIRMATA_H

#include <SPI.h>
#include <Servo.h>
#include <Firmata.h>

class StdFirmata {
public:
  void initialize(Stream &stream);
  void loop();
};

#endif // _STD_FIRMATA_H
