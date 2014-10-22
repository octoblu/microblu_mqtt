#ifndef _CROSS_STREAM_BUFFER_H_
#define _CROSS_STREAM_BUFFER_H_

#ifdef SPARK
#include "application.h"
#else
#include "Arduino.h"
#endif

#include "QueueArray.h"

class CrossStreamBuffer : public Stream {
  public:
    CrossStreamBuffer();

    QueueArray<unsigned char> *inBuffer;
    QueueArray<unsigned char> *outBuffer;
    
    // int read(uint8_t *buf, size_t size);
    void flush();
    int available();
    int read();
    size_t write(uint8_t c);
    size_t write(char *payload, size_t length);

    int peek();
};

#endif // _CROSS_STREAM_BUFFER_H_
