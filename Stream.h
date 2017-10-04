/*
  Stream.h - base class for character-based streams.
  Copyright (c) 2010 David A. Mellis.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef Stream_h
#define Stream_h

#include <inttypes.h>
#include "Print.h"

class Stream : public Print
{
  protected:
    unsigned long _timeout;     // number of milliseconds to wait for the next char before aborting timed read
    unsigned long _startMillis;	// used for timeout measurement
    int timedRead();    		// private method to read stream with timeout

  public:
    virtual int available() = 0;
    virtual int read() = 0;
    virtual int peek() = 0;
    virtual void flush() = 0;

	// Terminates if length characters have been read or timeout (see setTimeout).
    // Returns the number of characters placed in the buffer (0 means no valid data found)
    size_t readBytes( char *buffer, size_t length); // read chars from stream into buffer
    size_t readBytes( uint8_t *buffer, size_t length) { return readBytes((char *)buffer, length); }
    
};

#endif
