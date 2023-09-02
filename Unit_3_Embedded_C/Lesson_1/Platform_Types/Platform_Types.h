#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_

typedef _Bool 							boolean;

typedef volatile unsigned char 			vuint8_t;
typedef volatile unsigned short int 	vuint16_t;
typedef volatile unsigned int 			vuint32_t;
typedef volatile unsigned long int 		vuint64_t;

typedef volatile signed char 			vsint8_t;
typedef volatile signed short int 		vsint16_t;
typedef volatile signed int 			vsint32_t;
typedef volatile signed long int 		vsint64_t;


typedef unsigned char 			        uint8_t;
typedef unsigned short int 		        uint16_t;
typedef unsigned int 			        uint32_t;
typedef unsigned long int 		        uint64_t;

typedef signed char 			        sint8_t;
typedef signed short int 		        sint16_t;
typedef signed int 			     	    sint32_t;
typedef signed long int 		        sint64_t;

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

#endif
