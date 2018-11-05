#include "DebugMacros.h"

#include "DPrint.h"
#include "Util.h"

#ifdef DPRINT_SERIAL

namespace SearchAThing
{

namespace Arduino
{

bool _DPrintInitialized = false;

// if DPRINT_SERIAL is defined then all DPrint
// functions prints on the serial the the SERIAL_SPEED 8-n-1
#ifdef DPRINT_SERIAL
void _DPrintInit()
{
	// # refers to
	// [Atmel-8271J-AVR- ATmega-Datasheet_11/2015]

	if (_DPrintInitialized)
		return;

#if defined(__AVR_ATmega8__)
	// Table 62
	#define UBRRH_VALUE 0
	#define UBRRL_VALUE 3

	// Sets baud rate to SERIAL_SPEED
	// using values computed by inclusion of <util/setbaud.h>
	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;

	// #24.5
	UCSRB = (1 << RXEN) | (1 << TXEN);
	// Sets 8bit data mode - no parity - 1 bit stop
	UCSRC = (1 << URSEL) | (1 << USBS) | (3 << UCSZ0);
#else
	// #20.11.5
	// Sets baud rate to SERIAL_SPEED
	// using values computed by inclusion of <util/setbaud.h>
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;

	// #20.11.2
	// Sets 2X mode if used
#if USE_2X
	UCSR0A |= (1 << U2X0);
#else
	UCSR0A &= ~((1 << U2X0));
#endif

	// #20.11.4
	// Sets 8bit data mode - no parity - 1 bit stop
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

	// #20.11.3
	// Enable receiver/transmitter
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
#endif

	_DPrintInitialized = true;
}

#if defined(__AVR_ATmega8__)
#define _DPutc(c)                           \
	{                                       \
		loop_until_bit_is_set(UCSRA, UDRE); \
		UDR = c;                            \
	}
#else
#define _DPutc(c)                             \
	{                                         \
		loop_until_bit_is_set(UCSR0A, UDRE0); \
		UDR0 = c;                             \
	}
#endif

#else // DPRINT_SERIAL undef

// If DPRINT_SERIAL is not enabled all DPrint functions
// do dummy null output.
// Note:
// To disable calls to library DPrint simply don't define DEBUG

void _DPrintInit()
{
}

#define _DPutc(c) \
	{             \
	}

#endif

void DNewline()
{
	DPrint((char)10);
}

void DPrintln() { DPrint((char)10); }

//--

void DPrint(char c)
{
	_DPrintInit();
	_DPutc(c);
}

void DPrintln(char c)
{
	DPrint(c);
	DNewline();
}

//--

void DPrintX(char c, uint16_t cnt)
{
	_DPrintInit();
	while (cnt--)
		_DPutc(c);
}

void DPrintXln(char c, uint16_t cnt)
{
	DPrintX(c, cnt);
	DNewline();
}

//--

void DPrint(byte b)
{
	char buf[4];
	itoa(b, buf, 10);
	DPrint(buf);
}

void DPrintln(byte b)
{
	DPrint(b);
	DNewline();
}

//--

void DPrint(bool b) { DPrint(b ? '1' : '0'); }

void DPrintln(bool b)
{
	DPrint(b);
	DNewline();
}

//--

void DPrint(uint16_t x)
{
	char buf[6];
	utoa(x, buf, 10);
	DPrint(buf);
}

void DPrintln(uint16_t x)
{
	DPrint(x);
	DNewline();
}

//--

void DPrint(int16_t v)
{
	char buf[7];
	itoa(v, buf, 10);
	DPrint(buf);
}

void DPrintln(int16_t v)
{
	DPrint(v);
	DNewline();
}

//--

void DPrint(unsigned long v)
{
	char buf[10];
	ultoa(v, buf, 10);
	DPrint(buf);
}

//--

void DPrintln(unsigned long v)
{
	DPrint(v);
	DNewline();
}

//--

void DPrint(signed long v)
{
	char buf[11];
	ltoa(v, buf, 10);
	DPrint(buf);
}

//--

void DPrintln(signed long v)
{
	DPrint(v);
	DNewline();
}

//--

void DPrint(float v, int prec)
{
	char buf[20];

	FloatToString(buf, v, prec);

	DPrint(buf);
}

//--

void DPrintln(float v, int prec)
{
	DPrint(v);
	DNewline();
}

//--

void DPrint(const __FlashStringHelper *str)
{
	_DPrintInit();

	auto p = (const char PROGMEM *)str;
	auto i = 0;
	char c;
	while (c = pgm_read_byte(p + i))
	{
		_DPutc(c);
		++i;
	}
}

void DPrintln(const __FlashStringHelper *str)
{
	DPrint(str);
	DNewline();
}

//--

void DPrint(const char *str)
{
	_DPrintInit();

	while (*str)
	{
		_DPutc(*str);
		++str;
	}
}

void DPrintln(const char *str)
{
	DPrint(str);
	DNewline();
}

//--

void DPrint(const char *str, int size)
{
	_DPrintInit();

	while (size)
	{
		_DPutc(*str);
		++str;
		--size;
	}
}

void DPrintln(const char *str, int size)
{
	DPrint(str, size);
	DNewline();
}

//--

void DPrint(const __FlashStringHelper *str, int size)
{
	_DPrintInit();

	auto p = (const char PROGMEM *)str;
	auto i = 0;
	while (size)
	{
		_DPutc(pgm_read_byte(p + i));
		++i;
		--size;
	}
}

void DPrintln(const __FlashStringHelper *str, int size)
{
	DPrint(str, size);
	DNewline();
}

//--

void DPrintBool(int v)
{
	DPrint(v ? true : false);
}

void DPrintBoolln(int v)
{
	DPrintBool(v);
	DNewline();
}

//--

void DPrintBytes(const byte *buf, uint16_t len, char sep)
{
	char str[3];

	while (len > 0)
	{
		DPrint(*buf);
		if (len != 1)
			_DPutc(sep);

		++buf;
		--len;
	}
}

void DPrintBytesln(const byte *buf, uint16_t len, char sep)
{
	DPrintBytes(buf, len, sep);
	DNewline();
}

//--

void DPrintHex(byte b)
{
	char str[3];
	itoa(b, str, HEX);
	if (str[1] == 0)
		DPrint('0');
	DPrint(str);
}

void DPrintHexln(byte b)
{
	DPrintHex(b);
	DNewline();
}

//--

void DPrintHex(uint16_t v, bool prefix)
{
	if (prefix)
		DPrint(F("0x"));
	DPrintHex(highByte(v));
	DPrintHex(lowByte(v));
}

void DPrintHexln(uint16_t v, bool prefix)
{
	DPrintHex(v, prefix);
	DNewline();
}

//--

void DPrintHex(unsigned long v, bool prefix)
{
	if (prefix)
		DPrint(F("0x"));
	DPrintHex((byte)((v >> 24) & 0xff));
	DPrintHex((byte)((v >> 16) & 0xff));
	DPrintHex((byte)((v >> 8) & 0xff));
	DPrintHex((byte)(v & 0xff));
}

void DPrintHexln(unsigned long v, bool prefix)
{
	DPrintHex(v, prefix);
	DNewline();
}

//--

void DPrintHexBytes(const byte *buf, uint16_t len, char sep)
{
	while (len)
	{
		DPrintHex(*buf);
		++buf;
		--len;

		if (len > 0)
			DPrint(sep);
	}
}

void DPrintHexBytesln(const byte *buf, uint16_t len, char sep)
{
	DPrintHexBytes(buf, len, sep);
	DNewline();
}

//--

void DPrintHex(const byte *buf, uint16_t len, bool prettyPrint)
{
	uint16_t i = 0;
	while (len > 0)
	{
		if (prettyPrint && i % 16 == 0)
		{
			if (i > 0)
				DNewline();
			DPrintHex(i);
			DPrint(F(": "));
		}

		if (prettyPrint)
		{
			DPrint(' ');
			if (i % 8 == 0)
				DPrint(' ');
		}

		DPrintHex(*buf);

		++i;
		++buf;
		--len;
	}
}

void DPrintHexln(const byte *buf, uint16_t len, bool prettyPrint)
{
	DPrintHex(buf, len, prettyPrint);
	DNewline();
}

} // namespace Arduino

} // namespace SearchAThing

#endif // DPRINT_SERIAL