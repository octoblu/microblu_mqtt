#ifndef _MICROBLU_H
#define _MICROBLU_H

// #include <Firmata.h>
// #include <Meshblu.h>

class Microblu {
  // Firmata firmata;
  // Meshblu meshblu;

public:
  Microblu(char*, char*);
  Microblu(char*, char*, char*, int);
  void initialize(void *networkClient);
  void loop();
};

#endif // _MICROBLU_H
