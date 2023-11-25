#ifndef DIO_REGISTERS_H_
#define DIO_REGISTERS_H_
/* Assigning the addresses to the registers */

/* Port A Registers */
#define PORTA 		*((volatile unsigned int*)0x3b)
#define PINA 		*((volatile unsigned int*)0x39)
#define DDRA		*((volatile unsigned int*)0x3A)

/* Port B Registers */
#define PORTB 		*((volatile unsigned int*)0x38)
#define PINB 		*((volatile unsigned int*)0x36)
#define DDRB		*((volatile unsigned int*)0x37)

/* Port C Registers */
#define PORTC 		*((volatile unsigned int*)0x35)
#define PINC 		*((volatile unsigned int*)0x33)
#define DDRC		*((volatile unsigned int*)0x34)

/* Port D Registers */
#define PORTD 		*((volatile unsigned int*)0x32)
#define PIND 		*((volatile unsigned int*)0x30)
#define DDRD		*((volatile unsigned int*)0x31)

#endif /* DIO_REGISTERS_H_ */