#ifndef _SEARCHATHING_ARDUINO_UTILS_DEBUG_MACROS_H
#define _SEARCHATHING_ARDUINO_UTILS_DEBUG_MACROS_H

//--------------------------------------------------

// define here serial speed
#define SERIAL_SPEED	115200

// comment follow to disable serial debug
//#define SEARCHATHING_DISABLE

//--------------------------------------------------

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

//===========================================================================
// USER OVERRIDABLE MACROS
//---------------------------------------------------------------------------
// Change macro by:
// - comment out functionalities not needed, or
// - by compiler flags ( -DSEARCHATHING_DISABLE [defines to enable] )
//   eg. -DSEARCHATHING_DISABLE -DDEBUG -DDEBUG_ASSERT
//===========================================================================

#ifndef SEARCHATHING_DISABLE	// !(disable everything)

//===========================================================================
// GENERAL
//---------------------------------------------------------------------------

#define DEBUG			// general debugging
#define DEBUG_ASSERT	// assert failed
#define DPRINT_SERIAL	// dprint output to serial
 
#endif // SEARCHATHING_DISABLE

#include "DPrint.h"

#endif