
#include "CrossStreamBuffer.h"
  
CrossStreamBuffer::CrossStreamBuffer(){
  inBuffer = new QueueArray<unsigned char>;
  outBuffer = new QueueArray<unsigned char>;
}

//place write data into a buffer to be sent on next flush or monitor
size_t CrossStreamBuffer::write(uint8_t c)
{
  outBuffer->push(c);

  return 1;
}

//place write data into a buffer to be sent on next flush or monitor
size_t CrossStreamBuffer::write(char *payload, size_t length)
{
  int i = 0;
  for(i; i<length; i++)
    outBuffer->push(payload[i]);

  return i;
}

void CrossStreamBuffer::flush()
{
}

int CrossStreamBuffer::available() {
  return inBuffer->count();
}

int CrossStreamBuffer::read() {
  // if the head isn't ahead of the tail, we don't have any characters
  if (available()) 
  {
    return inBuffer->pop();
  } else {
    return -1;
  }
}

// //TODO 
// int CrossStreamBuffer::read(uint8_t *readbuf, size_t size) {
// }

int CrossStreamBuffer::peek() 
{
  if (available()) 
  {
    return inBuffer->peek();
  } else {
    return -1;
  }
}
