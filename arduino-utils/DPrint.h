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

#if !defined(__AVR_ATmega8__)
#include <util/setbaud.h>
#endif

#endif

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
void DPrintChar(char c);

// Prints a single char.
// followed by a newline.
void DPrintCharln(char c);

// Prints given char for `cnt' times.
void DPrintCharX(char c, uint16_t cnt);

// Prints given char for `cnt' times.
// Follows a newline.
void DPrintCharXln(char c, uint16_t cnt);

// Prints numeric value of the given byte.
void DPrintByte(byte b);

// Prints numeric value of the given byte.
// Follows a newline.
void DPrintByteln(byte b);

// Prints numeric value (0,1) of the given boolean.
void DPrintBool(bool b);

// Prints numeric value (0,1) of the given boolean.
// Follows a newline.
void DPrintBoolln(bool b);

// Prints numeric value of the given unsigned 16bit integer.
void DPrintUInt16(uint16_t x);

// Prints numeric value of the given unsigned 16bit integer.
// Follows a newline.
void DPrintUInt16ln(uint16_t x);

// Prints numeric value of the given signed 16bit integer.
void DPrintInt16(int16_t v);

// Prints numeric value of the given signed 16bit integer.
// Follows a newline.
void DPrintInt16ln(int16_t v);

// Prints numeric value of the given unsigned 32bit integer.
void DPrintUInt32(uint32_t x);

// Prints numeric value of the given unsigned 32bit integer.
// Follows a newline.
void DPrintUInt32ln(uint32_t x);

// Prints numeric value of the given signed 32bit integer.
void DPrintInt32(int32_t v);

// Prints numeric value of the given signed 32bit integer.
// Follows a newline.
void DPrintInt32ln(int32_t v);

#define DPrintULong DPrintUInt32
#define DPrintULongln DPrintUInt32ln
#define DPrintLong DPrintInt32
#define DPrintLongln DPrintInt32ln

// Prints numeric value of the given float with specified precision.
void DPrintFloat(float v, int prec = 2);

// Prints numeric value of the given float with specified precision.
// Follows a newline.
void DPrintFloatln(float v, int prec = 2);

// Prints given flash string. Note: Use F("str") to pass argument.
void DPrintF(const __FlashStringHelper *str);

// Prints given flash string. Follows a newline.
// Note: Use F("str") to pass argument.
void DPrintFln(const __FlashStringHelper *str);

// Prints given string of chars until leading null char excluded.
void DPrintStr(const char *str);

// Prints given string of chars until leading null char excluded.
// Follows a newline.
void DPrintStrln(const char *str);

// Prints given array of char for the given size.
// Useful when a leading null char isn't available.
void DPrintStrn(const char *str, int size);

// Prints given array of char for the given size.
// Useful when a leading null char isn't available.
// Follows a newline.
void DPrintStrnln(const char *str, int size);

// Prints `size' chars from the given flash string.
// Note: Use F("str") to pass the argument.
void DPrintFn(const __FlashStringHelper *str, int size);

// Prints `size' chars from the given flash string.
// Note: Use F("str") to pass the argument.
// Follows a newline.
void DPrintFnln(const __FlashStringHelper *str, int size);

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

class DPrintCls : public Print
{
  public:
    virtual size_t write(uint8_t c)
    {
#ifdef DPRINT_SERIAL
        DPrintChar(c);
#endif
    }
};

} // namespace Arduino

} // namespace SearchAThing

#ifndef DPRINT_SERIAL

#define DNewline() ;
#define DPrintln() ;
#define DPrintChar(x, ...) ;
#define DPrintCharln(x, ...) ;
#define DPrintCharX(x, ...) ;
#define DPrintCharXln(x, ...) ;
#define DPrintByte(x, ...) ;
#define DPrintByteln(x, ...) ;
#define DPrintBool(x, ...) ;
#define DPrintBoolln(x, ...) ;
#define DPrintUInt16(x, ...) ;
#define DPrintUInt16ln(x, ...) ;
#define DPrintInt16(x, ...) ;
#define DPrintInt16ln(x, ...) ;
#define DPrintUInt32(x, ...) ;
#define DPrintUInt32ln(x, ...) ;
#define DPrintInt32(x, ...) ;
#define DPrintInt32ln(x, ...) ;
#define DPrintULong(x, ...) ;
#define DPrintULongln(x, ...) ;
#define DPrintLong(x, ...) ;
#define DPrintLongln(x, ...) ;
#define DPrintFloat(x, ...) ;
#define DPrintFloatln(x, ...) ;
#define DPrintF(x, ...) ;
#define DPrintFln(x, ...) ;
#define DPrintStr(x, ...) ;
#define DPrintStrln(x, ...) ;
#define DPrintStrn(x, ...) ;
#define DPrintStrnln(x, ...) ;
#define DPrintFn(x, ...) ;
#define DPrintFnln(x, ...) ;
#define DPrintBool(x, ...) ;
#define DPrintBoolln(x, ...) ;
#define DPrintBytes(x, ...) ;
#define DPrintBytesln(x, ...) ;
#define DPrintHex(x, ...) ;
#define DPrintHexln(x, ...) ;
#define DPrintHex(x, ...) ;
#define DPrintHexln(x, ...) ;
#define DPrintHex(x, ...) ;
#define DPrintHexln(x, ...) ;
#define DPrintHexBytes(x, ...) ;
#define DPrintHexBytesln(x, ...) ;
#define DPrintHex(x, ...) ;
#define DPrintHexln(x, ...) ;

#endif

#endif
