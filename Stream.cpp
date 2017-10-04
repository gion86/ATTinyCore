#include "Arduino.h"
#include "Stream.h"

#define PARSE_TIMEOUT 1000  // default number of milli-seconds to wait

// Private method to read stream with timeout
int Stream::timedRead()
{
  int c;
  _startMillis = millis();
  do {
    c = read();
    if (c >= 0) return c;
  } while(millis() - _startMillis < _timeout);
  return -1;     // -1 indicates timeout
}


// Rad characters from stream into buffer,
// terminates if length characters have been read, or timeout (see setTimeout).
// Rturns the number of characters placed in the buffer,
// the buffer is NOT null terminated.
size_t Stream::readBytes(char *buffer, size_t length)
{
  size_t count = 0;
  while (count < length) {
    int c = timedRead();
    if (c < 0) break;
    *buffer++ = (char)c;
    count++;
  }
  return count;
}
