/******************************************************************************
*	types.h
*	 by Alex Chadwick
*
*	A light weight implementation of the USB protocol stack fit for a simple
*	driver.
*
*	types.h contains definitions of standardised types used ubiquitously.
******************************************************************************/
#ifndef _TYPES_H
#define _TYPES_H

#include <stdint.h>

/** Unsigned 8 bit type */
typedef uint8_t		u8;
/** Unsigned 16 bit type */
typedef uint16_t	u16;
/** Unsigned 32 bit type */
typedef uint32_t	u32;
/** Unsigned 64 bit type */
typedef uint64_t	u64;
/** Signed 8 bit type */
typedef int8_t		s8;
/** Signed 16 bit type */
typedef int16_t		s16;
/** Signed 32 bit type */
typedef int32_t		s32;
/** Signed 64 bit type */
typedef int64_t		s64;

/** One bit truth value */
typedef enum {
	false = 0,
	true = 1,
} bool;

/**
	\brief Result of a method call.

	Negative results are errors.
	OK is for a general success.
	ErrorGeneral is an undisclosed failure.
	ErrorArgument is a bad input.
	ErrorRetry is a temporary issue that may disappear, the method should be rerun
		without modification (the caller is expected to limit number of retries as
		required).
	ErrorDevice is a more permenant hardware error (a reset procedure should be
		enacted before retrying).
	ErrorIncompatible is a device driver that will not support the detected
		device.
	ErrorCompiler is a problem with the configuration of the compiler generating
		unusable code.
	ErrorMemory is used when the memory is exhausted.
	ErrorTimeout is used when a maximum delay is reached when waiting and an 
		operation is unfinished. This does not necessarily mean the operationg 
		will not finish, just that it is unreasonably slow.
	ErrorDisconnected is used when a device is disconnected in transfer.
*/
typedef enum {
	OK = 0,
	ErrorGeneral = -1,
	ErrorArgument = -2,
	ErrorRetry = -3,
	ErrorDevice = -4,
	ErrorIncompatible = -5,
	ErrorCompiler = -6,
	ErrorMemory = -7,
	ErrorTimeout = -8,
	ErrorDisconnected = -9,
} Result;

/**
	\brief Direction of USB communication.

	Many and various parts of the USB standard use this 1 bit field to indicate
	in which direction information flows.
*/
typedef enum {
	HostToDevice = 0,
	Out = 0,
	DeviceToHost = 1,
	In = 1,
} UsbDirection;

/**
	\brief Speed of USB communication.

	Many and various parts of the USB standard use this 2 bit field to indicate
	in which direction information flows.
*/
typedef enum {
	High = 0,
	Full = 1,
	Low = 2,
} UsbSpeed;

static inline char* SpeedToChar(UsbSpeed speed) {
	if (speed == High) return "480 Mb/s";
	else if (speed == Low) return "1.5 Mb/s";
	else if (speed == Full) return "12 Mb/s";
	else return "Unknown Mb/s";
}

/**
	\brief Transfer type in USB communication.

	Many and various parts of the USB standard use this 2 bit field to indicate
	in what type of transaction to use.
*/
typedef enum {
	Control = 0,
	Isochronous = 1,
	Bulk = 2,
	Interrupt = 3,
} UsbTransfer;

/**
	\brief Transfer size in USB communication.

	Many and various parts of the USB standard use this 2 bit field to indicate
	in what size of transaction to use.
*/
typedef enum {
	Bits8,
	Bits16,
	Bits32,
	Bits64,
} UsbPacketSize;

static inline UsbPacketSize SizeFromNumber(u32 size) {
	if (size <= 8) return Bits8;
	else if (size <= 16) return Bits16;
	else if (size <= 32) return Bits32;
	else return Bits64;
}
static inline u32 SizeToNumber(UsbPacketSize size) {
	if (size == Bits8) return 8;
	else if (size == Bits16) return 16;
	else if (size == Bits32) return 32;
	else return 64;
}

/**
	\brief Returns the minimum of two inputs.

	Returns the minimum of two inputs, ensuring only one evaluation of each. To
	do so, the type must be supplied.
*/
#define Min(x, y, type) ({ type __x = (x); type __y = (y); __x < __y ? __x : __y; })
/**
	\brief Returns the maximum of two inputs.

	Returns the maximum of two inputs, ensuring only one evaluation of each. To
	do so, the type must be supplied.
*/
#define Max(x, y, type) ({ type __x = (x); type __y = (y); __x < __y ? __y : __x; })

#endif // _TYPES_H