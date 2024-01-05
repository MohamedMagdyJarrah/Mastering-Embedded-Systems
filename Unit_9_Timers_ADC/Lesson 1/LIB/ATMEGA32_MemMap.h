#ifndef ATMEGA32_MEM_MAP_H_
#define ATMEGA32_MEM_MAP_H_

/*********************************************** Includes **********************************************/
#include "Utils.h"
#include "Platform_Types.h"

/************************************** Peripherals Addresses *************************************/
/*************************************************************************************************
										DIO Registers
**************************************************************************************************/
#define PORTA					*((vuint8*)0x3B)
#define DDRA					*((vuint8*)0x3A)
#define PINA					*((vuint8*)0x39)
#define PORTB					*((vuint8*)0x38)
#define DDRB					*((vuint8*)0x37)
#define PINB					*((vuint8*)0x36)
#define PORTC					*((vuint8*)0x35)
#define DDRC					*((vuint8*)0x34)
#define PINC					*((vuint8*)0x33)
#define PORTD					*((vuint8*)0x32)
#define DDRD					*((vuint8*)0x31)
#define PIND					*((vuint8*)0x30)
/****************  DIO Macros ******************/
#define DIO_PIN_INPUT_FLOATING		0
#define DIO_PIN_INPUT_PULL_UP		1
#define DIO_PIN_OUTPUT				2

#define DIO_PORT_INPUT_FLOATING		0
#define DIO_PORT_INPUT_PULL_UP		1
#define DIO_PORT_OUTPUT				2


#define DIO_PIN_HIGH				1
#define DIO_PIN_LOW 				0

#define DIO_PORT_HIGH				0xff
#define DIO_PORT_LOW 				0

#define DIO_PORTA 					0
#define DIO_PORTB 					1
#define DIO_PORTC 					2
#define DIO_PORTD 					3

#define DIO_PIN0 					0
#define DIO_PIN1 					1
#define DIO_PIN2 					2
#define DIO_PIN3 					3
#define DIO_PIN4 					4
#define DIO_PIN5 					5
#define DIO_PIN6 					6
#define DIO_PIN7 					7

/*************************************************************************************************
										EXTI Registers
**************************************************************************************************/
#define GICR				*((volatile uint8*)0x5B)
#define GICR_INT1			7
#define GICR_INT0			6
#define GICR_INT2			5

#define GIFR				*((volatile uint8*)0x5A)

#define MCUCR				*((volatile uint8*)0x55)
#define MCUCR_ISC11			3
#define MCUCR_ISC10			2
#define MCUCR_ISC01			1
#define MCUCR_ISC00			0

#define MCUCSR				*((volatile uint8*)0x54)
#define MCUCSR_ISC2			6
/****************  EXTI Macros ******************/
/* EXTI enable and disable */
#define EXTI_ENABLED					1
#define EXTI_DISABLED					2

/* Sense Control */
#define EXTI_LOW_LEVEL					0b00
#define EXTI_ON_CHANGE					0b01
#define EXTI_FALLING_EDGE				0b10
#define EXTI_RISING_EDGE				0b11

/* Interrupts Pins */
#define INT0					1
#define INT1					2
#define INT2					3


/*************************************************************************************************
								   Interrupt Controller Register
**************************************************************************************************/
#define SREG				*((volatile uint8*)0x5F)
#define SREG_I				7

/*************************************************************************************************
								   	   	USART Registers
**************************************************************************************************/
#define UDR					*((volatile uint8*)0x2C)

#define UCSRA				*((volatile uint8*)0x2B)
#define UCSRA_RXC			7
#define UCSRA_TXC			6
#define UCSRA_UDRE			5

#define UCSRB				*((volatile uint8*)0x2A)
#define UCSRB_RXCIE			7
#define UCSRB_TXCIE			6
#define UCSRB_UDRIE			5
#define UCSRB_RXEN 			4
#define UCSRB_TXEN 			3
#define UCSRB_UCSZ2			2

#define UCSRC				*((volatile uint8*)0x40)
#define UCSRC_URSEL			7
#define UCSRC_UMSEL			6
#define UCSRC_UPM1			5
#define UCSRC_UPM0			4
#define UCSRC_UCSZ1			2
#define UCSRC_UCSZ0			1

#define UBRRL				*((volatile uint8*)0x29)
#define UBRRH				*((volatile uint8*)0x40)	//The same register of UCSRC
/****************  USART Macros ******************/
//@ref  USART_MODE_define
#define	USART_MODE_SYNCHRONOUS			0
#define	USART_MODE_ASYNCHRONOUS			1
//@ref  USART_BAUDRATE_define
#define	USART_BAUDRATE_2400				207
#define	USART_BAUDRATE_4800				103
#define	USART_BAUDRATE_9600				51
#define	USART_BAUDRATE_14400			34
#define	USART_BAUDRATE_19200			25
#define	USART_BAUDRATE_28800			16
#define	USART_BAUDRATE_38400			12
#define	USART_BAUDRATE_57600			8
#define	USART_BAUDRATE_76800			6
#define	USART_BAUDRATE_115200			3
#define	USART_BAUDRATE_230400			1
#define	USART_BAUDRATE_250000			1
//@ref USART_DATALENGTH_define
#define	USART_DATALENGTH_5BITS			0b000
#define	USART_DATALENGTH_6BITS			0b001
#define	USART_DATALENGTH_7BITS			0b010
#define	USART_DATALENGTH_8BITS			0b011
#define	USART_DATALENGTH_9BITS			0b111
// @ref USART_PARITY_define
#define USART_PARITY_DISABLED			0b00
#define USART_PARITY_EVEN				0b10
#define USART_PARITY_ODD				0b11
// @ref USART_STOPBITS_define
#define USART_STOPBITS_ONEBIT			0
#define USART_STOPBITS_TWOBITS			1

#define IDLE					0
#define BUSY					1

#define SINGLE_CHAR				0
#define STRING					1

#define RECIEVE_CHAR			0
#define BUFFER					1

/*************************************************************************************************
								   	   	SPI Registers
**************************************************************************************************/
#define SPDR				*((volatile uint8*)0x2F)		//SPI Data Register

#define SPSR				*((volatile uint8*)0x2E)		//SPI Status Register
#define SPSR_SPIF			7								//SPI interrupt flag
#define SPSR_WCOL			6								//SPI write collision flag
#define SPSR_SPI2X			0								//Prescaler bit 2


#define SPCR			 	*((volatile uint8*)0x2D)		//SPI Control Register
#define SPCR_SPIE			7								//SPI interrupt enable
#define SPCR_SPE			6								//SPI enable
#define SPCR_DORD			5								//SPI Data order
#define SPCR_MSTR			4								//SPI MASTER/SLAVE select
#define SPCR_CPOL			3								//SPI Clock polarity
#define SPCR_CPHA			2								//SPI Clock phase
#define SPCR_SPR1			1								//Prescaler bit 1
#define SPCR_SPR0			0								//Prescaler bit 0
/****************  SPI Macros ******************/
#define F_OSC_DIV_4					0b000
#define F_OSC_DIV_16				0b001
#define F_OSC_DIV_64				0b010
#define F_OSC_DIV_128				0b011
#define F_OSC_DIV_2					0b100
#define F_OSC_DIV_8					0b101
#define F_OSC_DIV_32				0b110

/*************************************************************************************************
										TWI Registers
**************************************************************************************************/
#define TWDR			*((volatile uint8*)0x23)	//TWI Data Register

#define TWAR			*((volatile uint8*)0x22)	//TWI (Slave) Address Register
#define TWAR_TWA6		7						// Bits 7..1 – TWA: TWI (Slave) Address Register
#define TWAR_TWA5		6
#define TWAR_TWA4		5
#define TWAR_TWA3		4
#define TWAR_TWA2		3
#define TWAR_TWA1		2
#define TWAR_TWA0		1
#define TWAR_TWGCE		0						// TWI General Call Recognition Enable Bit


#define TWSR			*((volatile uint8*)0x21)	//TWI Status Register
#define TWSR_TWS7		7						// Bits 7..3 – TWS: TWI Status
#define TWSR_TWS6		6
#define TWSR_TWS5		5
#define TWSR_TWS4		4
#define TWSR_TWS3		3
#define TWSR_TWPS1		1						// TWI Prescaler Bit1
#define TWSR_TWPS0		0						// TWI Prescaler Bit0

#define TWBR			*((volatile uint8*)0x20)	//TWI Bit Rate Register

#define TWCR			*((volatile uint8*)0x56)	//TWI Control Register
#define TWCR_TWINT		7						// TWI Interrupt Flag
#define TWCR_TWEA 		6						// TWI Enable Acknowledge Bit
#define TWCR_TWSTA		5						// TWI START Condition Bit
#define TWCR_TWSTO		4						// TWI STOP Condition Bit
#define TWCR_TWWC		3						// TWI Write Collision Flag
#define TWCR_TWEN		2						// TWI Enable Bit
#define TWCR_TWIE		0						// TWI Interrupt Enable

/****************  TWI Macros ******************/
#define PRESCALER_1					0b00
#define PRESCALER_4					0b01
#define PRESCALER_16				0b10
#define PRESCALER_64				0b11

#define START_ACK                	0x08 /* start has been sent */
#define REP_START_ACK           	0x10 /* repeated start */
#define SLAVE_ADD_AND_WR_ACK    	0x18 /* Master transmit ( slave address + Write request ) ACK */
#define SLAVE_ADD_AND_RD_ACK   	 	0x40 /* Master transmit ( slave address + Read request ) ACK */
#define MSTR_WR_BYTE_ACK       	  	0x28 /* Master transmit data ACK */
#define MSTR_RD_BYTE_WITH_ACK  	 	0x50 /* Master received data with ACK */
#define MSTR_RD_BYTE_WITH_NACK   	0x58 /* Master received data with not ACK */
#define SLAVE_ADD_RCVD_RD_REQ    	0xA8 /* means that slave address is received with read request */
#define SLAVE_ADD_RCVD_WR_REQ    	0x60 /* means that slave address is received with write request */
#define SLAVE_DATA_RECEIVED      	0x80 /* means that a byte is received */
#define SLAVE_BYTE_TRANSMITTED   	0xB8 /* means that the written byte is transmitted */

/*************************************************************************************************
										WDT Registers
**************************************************************************************************/
#define WDTCR				*((volatile uint8*)0x41)
#define WDTCR_WDTOE			4
#define WDTCR_WDE			3
#define WDTCR_WDP2			2
#define WDTCR_WDP1			1
#define WDTCR_WDP0			0

/*Watchdog timeout options at Vcc=5V*/
#define WDT_TIMEOUT_16_3ms				0b000
#define WDT_TIMEOUT_32_5ms				0b001
#define WDT_TIMEOUT_65ms				0b010
#define WDT_TIMEOUT_0_13s				0b011
#define WDT_TIMEOUT_0_26s				0b100
#define WDT_TIMEOUT_0_52s				0b101
#define WDT_TIMEOUT_1s					0b110
#define WDT_TIMEOUT_2_1s				0b111


/*************************************************************************************************
										Timers Registers
**************************************************************************************************/
/*Timer interrupt Registers*/
#define TIMSK					*((volatile uint8*)0x59)			//Timer Interrupt Mask Register
#define TIMSK_TOIE0				0									//Timer overflow interrupt enable
#define TIMSK_OCIE0				1									//Output Compare match 0 interrupt enable

#define TIFR					*((volatile uint8*)0x58)			//Timer Interrupt flags Register
#define TIFR_TOV0				0									//Timer overflow interrupt enable
#define TIFR_OCF0				1

/*Timer 0 Registers*/
#define TCCR0					*((volatile uint8*)0x53)			//Timer/Counter 0 Control Register
#define TCCR0_FOC0				7									//Force Output compare bit
#define TCCR0_WGM00				6									//Waveform generation Mode bit 0
#define TCCR0_COM01				5									//Compare match output mode bit 1
#define TCCR0_COM00				4									//Compare match output mode bit 0
#define TCCR0_WGM01				3									//Waveform generation Mode bit 1
#define TCCR0_CS02				2									//Prescaler selection bit 2
#define TCCR0_CS01				1									//Prescaler selection bit 1
#define TCCR0_CS00				0									//Prescaler selection bit 0

#define TCNT0					*((volatile uint8*)0x52)			//Timer/Counter 0 Register

#define OCR0					*((volatile uint8*)0x5C)			//Output Compare Match 0 Register


/*Timer 1 Registers*/
#define TCCR1A					*((volatile uint8*)0x4F)
#define TCCR1A_WGM10			0
#define TCCR1A_WGM11			1
#define TCCR1A_COM1A0			6
#define TCCR1A_COM1A1			7

#define TCCR1B					*((volatile uint8*)0x4E)
#define TCCR1B_WGM12			3
#define TCCR1B_WGM13			4
#define TCCR1B_CS12				2								//Prescaler selection bit 2
#define TCCR1B_CS11				1								//Prescaler selection bit 1
#define TCCR1B_CS10				0

#define TCNT1					*((volatile uint16*)0x4C)
#define ICR1					*((volatile uint16*)0x46)
#define OCR1A					*((volatile uint16*)0x4A)

/*Timer 2 Registers*/
#define TCCR2					*((volatile uint8*)0x45)			//Timer/Counter 2 Control Register
#define TCNT2					*((volatile uint8*)0x44)			//Timer/Counter 2 Register
#define OCR2					*((volatile uint8*)0x43)			//Output Compare Match 2 Register

/****************  Timer Macros ******************/
/*Timer Modes Configurations*/
#define TIMER_MODE_MASK				0xB7					//CLR WGM00:01 bits
#define NORMAL						0xB7
#define PWM_PHASE_CORRECT			0x40
#define CTC							0x08
#define FAST_PWM					0x48

/*Compare Output Mode*/
#define COMPARE_OUTPUT_MASK			0xCF			//CLR Compare output bits
/*Non PWM*/
#define OC_DISCONNECTED				0
#define OC_TOGGLE					0x10
#define OC_CLR						0x20
#define OC_SET						0x30

/*Fast PWM*/
#define OC_DISCONNECTED				0
#define CLR_CM_SET_TOP				0x20
#define SET_CM_CLR_TOP				0x30

/*Clock selection */
#define CLK_SELECT_MASK				0xF8			//CLR Clock selection bits

#define NO_CLK_SOURCE				0
#define NO_PRESCALING				1
#define PRESCALER_8_BIT				2
#define PRESCALER_64_BIT			3
#define PRESCALER_256_BIT			4
#define PRESCALER_1024_BIT			5
#define EXT_CLK_FALLING_EDGE		6
#define EXT_CLK_RISING_EDGE			7

#endif /* ATMEGA32_MEM_MAP_H_ */
