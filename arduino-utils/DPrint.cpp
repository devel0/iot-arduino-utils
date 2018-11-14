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

#if SERIAL_SPEED != 57600
#error "please set to 57600 baud for atmega8"
#endif

// 115k
#define UBRRH_VALUE 0
#define UBRRL_VALUE 8

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
	DPrintChar(10);
}

void DPrintln() { DPrintChar(10); }

//--

void DPrintChar(char c)
{
	_DPrintInit();
	_DPutc(c);
}

void DPrintCharln(char c)
{
	DPrintChar(c);
	DNewline();
}

//--

void DPrintCharX(char c, uint16_t cnt)
{
	_DPrintInit();
	while (cnt--)
		_DPutc(c);
}

void DPrintCharXln(char c, uint16_t cnt)
{
	DPrintCharX(c, cnt);
	DNewline();
}

//--

void DPrintByte(byte b)
{
	DPrintInt16((int)b);
}

void DPrintByteln(byte b)
{
	DPrintByte(b);
	DNewline();
}

//--

void DPrintBool(bool b) { DPrintChar(b ? '1' : '0'); }

void DPrintBoolln(bool b)
{
	DPrintBool(b);
	DNewline();
}

//--

void DPrintUInt16(uint16_t x)
{
	char buf[6];
	utoa(x, buf, 10);
	DPrintStr(buf);
}

void DPrintUInt16ln(uint16_t x)
{
	DPrintUInt16(x);
	DNewline();
}

//--

void DPrintInt16(int16_t v)
{
	char buf[7];
	itoa(v, buf, 10);
	DPrintStr(buf);
}

void DPrintInt16ln(int16_t v)
{
	DPrintInt16(v);
	DNewline();
}

//--

void DPrintUInt32(uint32_t x)
{
	char buf[11];
	ultoa(x, buf, 10);
	DPrintStr(buf);
}

void DPrintUInt32ln(uint32_t x)
{
	DPrintUInt32(x);
	DNewline();
}

//--

void DPrintInt32(int32_t v)
{
	char buf[12];
	ltoa(v, buf, 10);
	DPrintStr(buf);
}

void DPrintInt32ln(int32_t v)
{
	DPrintInt32(v);
	DNewline();
}

//--

void DPrintFloat(float v, int prec)
{
	char buf[20];

	FloatToString(buf, v, prec);

	DPrintStr(buf);
}

//--

void DPrintFloatln(float v, int prec)
{
	DPrintFloat(v);
	DNewline();
}

//--

void DPrintF(const __FlashStringHelper *str)
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

void DPrintFln(const __FlashStringHelper *str)
{
	DPrintF(str);
	DNewline();
}

//--

void DPrintStr(const char *str)
{
	_DPrintInit();

	while (*str)
	{
		_DPutc(*str);
		++str;
	}
}

void DPrintStrln(const char *str)
{
	DPrintStr(str);
	DNewline();
}

//--

void DPrintStrn(const char *str, int size)
{
	_DPrintInit();

	while (size)
	{
		_DPutc(*str);
		++str;
		--size;
	}
}

void DPrintStrnln(const char *str, int size)
{
	DPrintStrn(str, size);
	DNewline();
}

//--

void DPrintFn(const __FlashStringHelper *str, int size)
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

void DPrintFnln(const __FlashStringHelper *str, int size)
{
	DPrintFn(str, size);
	DNewline();
}

//--

void DPrintBytes(const byte *buf, uint16_t len, char sep)
{
	char str[3];

	while (len > 0)
	{
		DPrintByte(*buf);
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
		DPrintChar('0');
	DPrintStr(str);
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
		DPrintF(F("0x"));
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
		DPrintF(F("0x"));
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
			DPrintChar(sep);
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
			DPrintF(F(": "));
		}

		if (prettyPrint)
		{
			DPrintChar(' ');
			if (i % 8 == 0)
				DPrintChar(' ');
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