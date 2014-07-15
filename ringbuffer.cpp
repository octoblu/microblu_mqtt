#include "ringbuffer.h"

ringbuffer::ringbuffer(size_t _size)
        : size(_size)
        , head(0)
        , tail(0)
{
    buffer = new unsigned char[_size];
}

ringbuffer::~ringbuffer()
{
    delete[] buffer;
}

void ringbuffer::push(unsigned char c)
{
  int i = (head + 1) % size;

  if (i != tail) 
  {
    buffer[head] = c;
    head = i;
  }
}

unsigned char ringbuffer::pop()
{
  unsigned char c = buffer[tail];
  tail = (tail + 1) % size;
  return c;
}

unsigned char ringbuffer::peek()
{
  return buffer[tail];
}

int ringbuffer::available()
{
  return (((head + size) - tail) % size);
}