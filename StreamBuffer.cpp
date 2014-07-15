
#include <StreamBuffer.h>
  
StreamBuffer::StreamBuffer(ringbuffer &writebuf, ringbuffer &readbuf) : _writebuf(&writebuf), _readbuf(&readbuf) {}

//place write data into a buffer to be sent on next flush or monitor
size_t StreamBuffer::write(uint8_t c)
{

  _writebuf->push(c);

  return 1;
}

//place write data into a buffer to be sent on next flush or monitor
size_t StreamBuffer::write(char *payload, size_t length)
{
  int i = 0;
  for(i; i<length; i++)
    _writebuf->push(payload[i]);

  return i;
}

void StreamBuffer::flush()
{
}

int StreamBuffer::available() {
  return _readbuf->available();
}

int StreamBuffer::read() {
  // if the head isn't ahead of the tail, we don't have any characters
  if (_readbuf->available()) 
  {
    return _readbuf->pop();
  } else {
    return -1;
  }
}

// //TODO 
// int StreamBuffer::read(uint8_t *readbuf, size_t size) {
// }

int StreamBuffer::peek() 
{
  if (_readbuf->available()) 
  {
    return _readbuf->peek();
  } else {
    return -1;
  }
}
