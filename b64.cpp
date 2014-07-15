#include "b64.h"

const char base64[ 64 ] PROGMEM  = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
  


uint8_t b64::encode(const uint8_t *buf, size_t size, Stream &out)
{
	int i = 0;
	while(i<size)
	{
	
	}
	DBGCN();
	return 0;
}

char b64::lookup(const char c)
{
	return pgm_read_byte( &base64[ c ]);
}

uint8_t b64::encode(Stream &from, Stream &to)
{
	int i = 0, j = 0;
	while(from.available())
	{
		//default to 
		char c[] = {0, 0, 0};
		char d0, d1, d2, d3;

		//grab 3 chars if available
		do
		{	
			DBGCS("c");
			DBGC((int)i%3);
			DBGCS(": ");
			DBGCN((int)(from.peek()));
			c[i%3]=from.read();
      i++;
		}while(from.available() && (i%3!=0));

		if (i%3==1)
		{
			d0 = (c[0] >> 2) & 63;
			d1 = ((c[0] << 4) & 48) | ((c[1] >> 4) & 15);

			DBGCS("d0: ");
			DBGC((int)d0);
			DBGCS(" : ");
			DBGC(lookup(d0));
			to.print( lookup(d0) );
			j++;
			DBGCN();

			DBGCS("d1: ");
			DBGC((int)d1);
			DBGCS(" : ");
			DBGC(lookup(d1));
			to.print( lookup(d1) );
			j++;
			DBGCN();

			DBGC('=');
	    to.print( '=' );
	    j++;
			DBGC('=');
	    to.print( '=' );
	    j++;
		}
		else if (i%3==2)
		{
			d0 = (c[0] >> 2) & 63;
			d1 = ((c[0] << 4) & 48) | ((c[1] >> 4) & 15);
			d2 = ((c[1] << 2) & 60) | ((c[2] >> 6) & 3);

			DBGCS("d0: ");
			DBGC((int)d0);
			DBGCS(" : ");
			DBGC(lookup(d0));
			to.print(lookup(d0));
			j++;
			DBGCN();

			DBGCS("d1: ");
			DBGC((int)d1);
			DBGCS(" : ");
			DBGC(lookup(d1));
			to.print(lookup(d1));
			j++;
			DBGCN();

			DBGCS("d2: ");
			DBGC((int)d2);
			DBGCS(" : ");
			DBGC(lookup(d2));
			to.print(lookup(d2));
			j++;
			DBGCN();

			DBGC('=');
		  to.print( '=' );
			j++;
			DBGCN();
		}
		else
		{
			d0 = (c[0] >> 2) & 63;
			d1 = ((c[0] << 4) & 48) | ((c[1] >> 4) & 15);
			d2 = ((c[1] << 2) & 60) | ((c[2] >> 6) & 3);
			d3 = c[2] & 63;

			DBGCS("d0: ");
			DBGC((int)d0);
			DBGCS(" : ");
			DBGC(lookup(d0));
			to.print(lookup(d0));
			j++;
			DBGCN();

			DBGCS("d1: ");
			DBGC((int)d1);
			DBGCS(" : ");
			DBGC(lookup(d1));
			to.print(lookup(d1));
			j++;
			DBGCN();

			DBGCS("d2: ");
			DBGC((int)d2);
			DBGC(" : ");
			DBGC(lookup(d2));
			to.print(lookup(d2));
			j++;
			DBGCN();

			DBGCS("d3: ");
			DBGC((int)d3);
			DBGC(" : ");
			DBGC(lookup(d3));
			to.print(lookup(d3));
			j++;
			DBGCN();
		}
	}
	return j;
}

uint8_t b64::encode(Stream &from, Stream &to, size_t max)
{
	int i = 0, j = 0;
	while(from.available() && (j<=max-4))
	{
		//default to 
		char c[] = {0, 0, 0};
		char d0, d1, d2, d3;

		//grab 3 chars if available
		do
		{	
			DBGCS("c");
			DBGC((int)i%3);
			DBGCS(": ");
			DBGCN((int)(from.peek()));
			c[i%3]=from.read();
      i++;
		}while(from.available() && (i%3!=0) && (j<=max-4));

		if (i%3==1)
		{
			d0 = (c[0] >> 2) & 63;
			d1 = ((c[0] << 4) & 48) | ((c[1] >> 4) & 15);

			DBGCS("d0: ");
			DBGC((int)d0);
			DBGCS(" : ");
			DBGC(lookup(d0));
			to.print( lookup(d0) );
			j++;
			DBGCN();

			DBGCS("d1: ");
			DBGC((int)d1);
			DBGCS(" : ");
			DBGC(lookup(d1));
			to.print( lookup(d1) );
			j++;
			DBGCN();

			DBGC('=');
	    to.print( '=' );
	    j++;
			DBGCN();

			DBGC('=');
	    to.print( '=' );
	    j++;
			DBGCN();

		}
		else if (i%3==2)
		{
			d0 = (c[0] >> 2) & 63;
			d1 = ((c[0] << 4) & 48) | ((c[1] >> 4) & 15);
			d2 = ((c[1] << 2) & 60) | ((c[2] >> 6) & 3);

			DBGCS("d0: ");
			DBGC((int)d0);
			DBGCS(" : ");
			DBGC(lookup(d0));
			to.print(lookup(d0));
			j++;
			DBGCN();

			DBGCS("d1: ");
			DBGC((int)d1);
			DBGCS(" : ");
			DBGC(lookup(d1));
			to.print(lookup(d1));
			j++;
			DBGCN();

			DBGCS("d2: ");
			DBGC((int)d2);
			DBGCS(" : ");
			DBGC(lookup(d2));
			to.print(lookup(d2));
			j++;
			DBGCN();

			DBGC('=');
		  to.print( '=' );
			j++;
			DBGCN();

		}
		else
		{
			d0 = (c[0] >> 2) & 63;
			d1 = ((c[0] << 4) & 48) | ((c[1] >> 4) & 15);
			d2 = ((c[1] << 2) & 60) | ((c[2] >> 6) & 3);
			d3 = c[2] & 63;

			DBGCS("d0: ");
			DBGC((int)d0);
			DBGCS(" : ");
			DBGC(lookup(d0));
			to.print(lookup(d0));
			j++;
			DBGCN();

			DBGCS("d1: ");
			DBGC((int)d1);
			DBGCS(" : ");
			DBGC(lookup(d1));
			to.print(lookup(d1));
			j++;
			DBGCN();

			DBGCS("d2: ");
			DBGC((int)d2);
			DBGC(" : ");
			DBGC(lookup(d2));
			to.print(lookup(d2));
			j++;
			DBGCN();

			DBGCS("d3: ");
			DBGC((int)d3);
			DBGC(" : ");
			DBGC(lookup(d3));
			to.print(lookup(d3));
			j++;
			DBGCN();

		}
	}
	return j;
}

uint8_t b64::encode(Stream &stream, char *buf, size_t max)
{
	int i = 0, j = 0;

	while(stream.available() && j < max-2)
	{

		//default to 
		char c[] = {0, 0, 0};
		char d0, d1, d2, d3;

		//grab 3 chars if available
		do
		{	
			DBGCS("c");
			DBGC((int)i%3);
			DBGCS(": ");
			DBGCN((int)(stream.peek()));
			c[i%3]=stream.read();
      i++;
		}while(stream.available() && (i%3!=0) && j < max-2);

		if (i%3==1)
		{
			d0 = (c[0] >> 2) & 63;
			d1 = ((c[0] << 4) & 48) | ((c[1] >> 4) & 15);

			DBGCS("d0: ");
			DBGC((int)d0);
			DBGCS(" : ");
			DBGC(lookup(d0));
			buf[j++] = ( lookup(d0) );
			DBGCS("d1: ");
			DBGC((int)d1);
			DBGCS(" : ");
			DBGC(lookup(d1));
			buf[j++] = ( lookup(d1) );
			DBGC('=');
		  buf[j++] = ( '=' );
			DBGC('=');
		  buf[j++] = ( '=' );
		}
		else if (i%3==2)
		{
			d0 = (c[0] >> 2) & 63;
			d1 = ((c[0] << 4) & 48) | ((c[1] >> 4) & 15);
			d2 = ((c[1] << 2) & 60) | ((c[2] >> 6) & 3);

			DBGCS("d0: ");
			DBGC((int)d0);
			DBGCS(" : ");
			DBGC(lookup(d0));
			buf[j++] = (lookup(d0));
			DBGCN();

			DBGCS("d1: ");
			DBGC((int)d1);
			DBGCS(" : ");
			DBGC(lookup(d1));
			buf[j++] = (lookup(d1));
			DBGCN();

			DBGCS("d2: ");
			DBGC((int)d2);
			DBGCS(" : ");
			DBGC(lookup(d2));
			buf[j++] = (lookup(d2));
			DBGCN();

			DBGC('=');
		  buf[j++] = ( '=' );
		  DBGCN();

		}
		else
		{
			d0 = (c[0] >> 2) & 63;
			d1 = ((c[0] << 4) & 48) | ((c[1] >> 4) & 15);
			d2 = ((c[1] << 2) & 60) | ((c[2] >> 6) & 3);
			d3 = c[2] & 63;

			DBGCS("d0: ");
			DBGC((int)d0);
			DBGCS(" : ");
			DBGC(lookup(d0));
			buf[j++] = (lookup(d0));
			DBGCN();

			DBGCS("d1: ");
			DBGC((int)d1);
			DBGCS(" : ");
			DBGC(lookup(d1));
			buf[j++] = (lookup(d1));
			DBGCN();

			DBGCS("d2: ");
			DBGC((int)d2);
			DBGC(" : ");
			DBGC(lookup(d2));
			buf[j++] = (lookup(d2));
			DBGCN();

			DBGCS("d3: ");
			DBGC((int)d3);
			DBGC(" : ");
			DBGC(lookup(d3));
			buf[j++] = (lookup(d3));
			DBGCN();

		}
	}
	return j;
}

uint8_t b64::decode(char *src, size_t size, Stream &stream)
{
	int i = 0, j = 0;
	while(i<size)
	{
		//default to 
		char c[] = {-1, -1, -1, -1};
		char d0, d1, d2;

		//grab 4 chars if available
		do
		{
			DBGCS("c");
			DBGC(i%4);
			DBGCS(": ");
			DBGC(src[i]);
			DBGCS(": ");
			DBGCN((int)reverselookup(src[i]));
			c[i%4]=reverselookup(src[i++]);
		}while( i<size && i%4 != 0 );

		d0 = ((c[0] << 2) & 252) | (c[1] >>4 & 3);
		DBGCS("d0: ");
		DBGCN(d0, HEX);
    stream.write(d0);
    j++;
    DBGCN();

    //if c3 is equal sign (negative one in our lookup), we ignore the second to last character
		if(c[2] != -1)
		{
			d1 = ((c[1] << 4) & 240) | (c[2] >>2 & 15);
			DBGCS("d1: ");
			DBGCN(d1, HEX);
    	stream.write(d1);
    	j++;
    	DBGCN();

		}

		//if c2 is equal sign (negative one in our lookup), we ignore the second to last character
		if(c[3] != -1)
		{
			d2 = ((c[2] << 6) & 192) | (c[3] & 63);
			DBGCS("d2: ");
			DBGCN(d2, HEX);
	    stream.write(d2);
	    j++;
	    DBGCN();

	  }
	}
	DBGCN();
	return j;
}

//max is max to put out to stream
uint8_t b64::decode(Stream &from, Stream &to, size_t max)
{
	int i,j = 0;
	while(from.available() && j<max-2)
	{
		//default to 
		char c[] = {-1, -1, -1, -1};
		char d0, d1, d2;

		//grab 4 chars if available
		do
		{
			DBGCS("c");
			DBGC(i%4);
			DBGCS(": ");
			DBGC(from.peek());
			DBGCS(": ");
			DBGCN((int)reverselookup(from.peek()));
			c[i%4]=reverselookup(from.read());
		}while( from.available() && i%4 != 0  && j<max-2);

		d0 = ((c[0] << 2) & 252) | (c[1] >>4 & 3);
		DBGCS("d0: ");
		DBGCN(d0, HEX);
    to.write(d0);
    j++;
    DBGCN();
    	
    	//if c3 is equal sign (negative one in our lookup), we ignore the second to last character
		if(c[2] != -1)
		{
			d1 = ((c[1] << 4) & 240) | (c[2] >>2 & 15);
			DBGCS("d1: ");
			DBGCN(d1, HEX);
    	to.write(d1);
			j++;
			DBGCN();
		}

		//if c2 is equal sign (negative one in our lookup), we ignore the second to last character
		if(c[3] != -1)
		{
			d2 = ((c[2] << 6) & 192) | (c[3] & 63);
			DBGCS("d2: ");
			DBGCN(d2, HEX);
	    to.write(d2);
			j++;
			DBGCN();

	  }
	}
	DBGCN();

	return j;
}

uint8_t b64::encodeLength(size_t len)
{

	int n = len;
	//borrowed from https://github.com/adamvr/arduino-base64
	return (n + 2 - ((n + 2) % 3)) / 3 * 4;

}

char b64::reverselookup(const char c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return c-65;
	}
	else if (c >= 'a' && c <= 'z')
	{
		return c-71;
	}
	else if (c >= '0' && c <= '9')
	{
		return c+4;
	}
	else if (c == 43)
	{
		return 62;
	}
	else if (c == 47)
	{
		return 63;
	}
	else
	{
		return -1;
	}
}
