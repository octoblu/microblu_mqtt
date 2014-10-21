#ifndef _StreamBuffer_H
#define _StreamBuffer_H

#ifdef SPARK
#include "application.h"
#else
#include "Arduino.h"
#endif

#include "QueueArray.h"

class StreamBuffer : public Stream {
  public:
    StreamBuffer();
    
    // int read(uint8_t *buf, size_t size);
    void flush();
    int available();
    int read();
    size_t write(uint8_t c);
    size_t write(char *payload, size_t length);

    int peek();

  private:
    QueueArray<char> *_buf;
};

#endif // _StreamBuffer_H
