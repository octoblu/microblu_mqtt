
#include "StreamBuffer.h"
  
StreamBuffer::StreamBuffer(){
  _buf = new QueueArray<char>;
}

//place write data into a buffer to be sent on next flush or monitor
size_t StreamBuffer::write(uint8_t c)
{
  _buf->push(c);

  return 1;
}

//place write data into a buffer to be sent on next flush or monitor
size_t StreamBuffer::write(char *payload, size_t length)
{
  int i = 0;
  for(i; i<length; i++)
    _buf->push(payload[i]);

  return i;
}

void StreamBuffer::flush()
{
}

int StreamBuffer::available() {
  return _buf->count();
}

int StreamBuffer::read() {
  // if the head isn't ahead of the tail, we don't have any characters
  if (available()) 
  {
    return _buf->pop();
  } else {
    return -1;
  }
}

// //TODO 
// int StreamBuffer::read(uint8_t *readbuf, size_t size) {
// }

int StreamBuffer::peek() 
{
  if (available()) 
  {
    return _buf->peek();
  } else {
    return -1;
  }
}
