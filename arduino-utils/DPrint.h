#ifndef _SEARCHATHING_ARDUINO_UTILS_DPRINT_H
#define _SEARCHATHING_ARDUINO_UTILS_DPRINT_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "DebugMacros.h"

#ifdef DPRINT_SERIAL
#define BAUD SERIAL_SPEED
#include <util/setbaud.h>
#endif

#define DPrintInt(x) DPrint((int16_t)x);
#define DPrintIntln(x) DPrintln((int16_t)x);

namespace SearchAThing
{

	namespace Arduino
	{

		extern bool _DPrintInitialized;
		// Initializes the debug output line.
		// If DSERIAL_PRINT is defined then the serial with the SERIAL_SPEED
		// will be used as output line. Its an internal function that is
		// called automatically when DPrint functions are used.
		void _DPrintInit();

		// Prints a newline.
		void DNewline();

		// Prints a newline.
		void DPrintln();

		// Prints a single char.
		void DPrint(char c);

		// Prints a single char.
		// followed by a newline.
		void DPrintln(char c);

		// Prints given char for `cnt' times.
		void DPrintX(char c, uint16_t cnt);

		// Prints given char for `cnt' times.
		// Follows a newline.
		void DPrintXln(char c, uint16_t cnt);

		// Prints numeric value of the given byte.
		void DPrint(byte b);

		// Prints numeric value of the given byte.
		// Follows a newline.
		void DPrintln(byte b);

		// Prints numeric value (0,1) of the given boolean.
		void DPrint(bool b);

		// Prints numeric value (0,1) of the given boolean.
		// Follows a newline.
		void DPrintln(bool b);

		// Prints numeric value of the given unsigned 16bit integer.
		void DPrint(uint16_t x);

		// Prints numeric value of the given unsigned 16bit integer.
		// Follows a newline.
		void DPrintln(uint16_t x);

		// Prints numeric value of the given signed 16bit integer.
		void DPrint(int16_t v);

		// Prints numeric value of the given signed 16bit integer.
		// Follows a newline.
		void DPrintln(int16_t v);		

		// Prints numeric value of the given unsigned 32bit integer.		
		void DPrint(unsigned long v);

		// Prints numeric value of the given unsigned 32bit integer.		
		// Follows a newline.
		void DPrintln(unsigned long v);

		// Prints numeric value of the given signed 32bit integer.		
		void DPrint(signed long v);

		// Prints numeric value of the given signed 32bit integer.		
		// Follows a newline.
		void DPrintln(signed long v);

		// Prints numeric value of the given float with specified precision.
		void DPrint(float v, int prec = 2);

		// Prints numeric value of the given float with specified precision.
		// Follows a newline.
		void DPrintln(float v, int prec = 2);

		// Prints given flash string. Note: Use F("str") to pass argument.
		void DPrint(const __FlashStringHelper *str);

		// Prints given flash string. Follows a newline.
		// Note: Use F("str") to pass argument.		
		void DPrintln(const __FlashStringHelper *str);

		// Prints given string of chars until leading null char excluded.
		void DPrint(const char *str);

		// Prints given string of chars until leading null char excluded.
		// Follows a newline.
		void DPrintln(const char *str);

		// Prints given array of char for the given size.
		// Useful when a leading null char isn't available.
		void DPrint(const char *str, int size);

		// Prints given array of char for the given size.		
		// Useful when a leading null char isn't available.
		// Follows a newline.
		void DPrintln(const char *str, int size);

		// Prints `size' chars from the given flash string.
		// Note: Use F("str") to pass the argument.
		void DPrint(const __FlashStringHelper *str, int size);

		// Prints `size' chars from the given flash string.		
		// Note: Use F("str") to pass the argument.
		// Follows a newline.
		void DPrintln(const __FlashStringHelper *str, int size);

		// Prints '0' if the given numeric value is 0 and `1' otherwise.
		void DPrintBool(int v);

		// Prints '0' if the given numeric value is 0 and `1' otherwise.
		// Follows a newline.
		void DPrintBoolln(int v);

		// Prints numerical value of first `len' bytes of the given buffer
		// `buf' separating each number with the given separator `sep' char.
		void DPrintBytes(const byte *buf, uint16_t len, char sep = '.');

		// Prints numerical value of first `len' bytes of the given buffer
		// `buf' separating each number with the given separator `sep' char.
		// Follows a newline.
		void DPrintBytesln(const byte *buf, uint16_t len, char sep = '.');		

		// Prints lowercase hexadecimal value of the given byte.
		void DPrintHex(byte b);

		// Prints lowercase hexadecimal value of the given byte.
		// Follows a newline.
		void DPrintHexln(byte b);

		// Prints lowercase hexadecimal value of the given unsigned 16bit
		// integer prefixed with "0x" string when `prefix' option is set
		// to true.
		void DPrintHex(uint16_t v, bool prefix = false);

		// Prints lowercase hexadecimal value of the given unsigned 16bit
		// integer prefixed with "0x" string when `prefix' option is set
		// to true.
		// Follows a newline.
		void DPrintHexln(uint16_t v, bool prefix = false);

		// Prints lowercase hexadecimal value of the given unsigned 32bit
		// integer prefixed with "0x" string when `prefix' option is set
		// to true.
		void DPrintHex(unsigned long v, bool prefix = false);

		// Prints lowercase hexadecimal value of the given unsigned 32bit
		// integer prefixed with "0x" string when `prefix' option is set
		// to true.
		// Follows a newline.
		void DPrintHexln(unsigned long v, bool prefix = false);

		// Prints lowercase hexadecimal value of the given `len' bytes buffer
		// separating each with `sep' char.
		void DPrintHexBytes(const byte *buf, uint16_t len, char sep = '-');

		// Prints lowercase hexadecimal value of the given `len' bytes buffer
		// separating each with `sep' char.
		// Follows a newline.
		void DPrintHexBytesln(const byte *buf, uint16_t len, char sep = '-');		

		// Prints lowercase hexdecimal value of `len' bytes of the given
		// buffer in sequence (if `prettyPrint'==false) or in two column 8+8
		// space separated and addressed (when `prettyPrint'==true).
		void DPrintHex(const byte *buf, uint16_t len, bool prettyPrint = false);

		// Prints lowercase hexdecimal value of `len' bytes of the given
		// buffer in sequence (if `prettyPrint'==false) or in two column 8+8
		// space separated and addressed (when `prettyPrint'==true).
		// Follows a newline.
		void DPrintHexln(const byte *buf, uint16_t len, bool prettyPrint = false);		

	}

}

#endif
