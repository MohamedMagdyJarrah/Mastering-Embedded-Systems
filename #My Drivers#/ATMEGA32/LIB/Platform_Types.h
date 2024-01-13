#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_

typedef _Bool 							boolean;

typedef volatile unsigned char 			vuint8;
typedef volatile unsigned short int 	vuint16;
typedef volatile unsigned int 			vuint32;
typedef volatile unsigned long int 		vuint64;

typedef volatile signed char 			vsint8;
typedef volatile signed short int 		vsint16;
typedef volatile signed int 			vsint32;
typedef volatile signed long int 		vsint64;


typedef unsigned char 			        uint8;
typedef unsigned short int 		        uint16;
typedef unsigned int 			        uint32;
typedef unsigned long int 		        uint64;

typedef signed char 			        sint8;
typedef signed short int 		        sint16;
typedef signed int 			     	    sint32;
typedef signed long int 		        sint64;

typedef float							float32;
typedef double							float64;

#ifndef TRUE
#define TRUE							((boolean)1)
#endif

#ifndef FALSE
#define FALSE							((boolean)0)
#endif

#ifndef NULL
#define NULL 							((void*)0)
#endif

/* Error Status */
#define NO_ERROR						0
#define ERROR_DETECTED					1
#define NULL_POINTER					2
#define BUSY_FUNC						3

/* CPU Frequency */
#define F_CPU			8000000UL

/* For Asynchronous functions state */
#define IDLE					0
#define BUSY					1

#endif
