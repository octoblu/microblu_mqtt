#ifndef _B64_H
#define _B64_H

#ifdef SPARK
#include "application.h"
#include "pgmspace.h"
#else
#include "Arduino.h"
#include "avr/pgmspace.h"
#include "Client.h"
#endif


//#define B64_DEBUG
#ifdef B64_DEBUG
#define DBGCN( ... ) Serial.println( __VA_ARGS__ )
#define DBGC( ... ) Serial.print( __VA_ARGS__ )
#define DBGCSN( ... ) Serial.println( F(__VA_ARGS__) )
#define DBGCS( ... ) Serial.print( F(__VA_ARGS__) )
#else
#define DBGCN( ... )
#define DBGC( ... )
#define DBGCSN( ... )
#define DBGCS( ... )
#endif

class b64 {
	public:
    // static void decode(char *src, Stream &stream);
    static uint8_t decode(char *src, size_t size, Stream &stream);
    static uint8_t decode(Stream &from, Stream &to);
    static uint8_t decode(Stream &from, Stream &to, size_t max);

    static uint8_t encode(Stream &from, Stream &to, size_t max);
		static uint8_t encode(const uint8_t *buf, size_t size, Stream &out);
    static uint8_t encode(Stream &from, Stream &to);
    static uint8_t encode(Stream &stream, char *buf, size_t max);


    static uint8_t encodeLength(size_t max);

		static char lookup(const char c);
		static char reverselookup(const char c);
};
#endif // _B64_H