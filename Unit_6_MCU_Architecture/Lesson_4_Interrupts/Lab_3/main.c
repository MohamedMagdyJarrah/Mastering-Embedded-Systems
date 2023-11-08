#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU					8000000UL
#include <util/delay.h>


/* Macros for manipulating bits */
#define SET_BIT(REG,BIT)		REG |= (1<<BIT);	
#define CLR_BIT(REG,BIT)		REG &= ~(1<<BIT);
#define TOGGLE_BIT(REG,BIT)		REG ^= (1<<BIT);

/********************** DIO Initializations ********************/
void DIO_init(void)
{
	/* Make Pin 2,3 as inputs in PORTD and Pin 2 as input in PORTB*/
	CLR_BIT(DDRD,2);
	CLR_BIT(DDRD,3);
	CLR_BIT(DDRB,2);
	
	/* Make Pin 5,6,7 as outputs in PORTD */
	SET_BIT(DDRD,5);
	SET_BIT(DDRD,6);
	SET_BIT(DDRD,7);
	
	/* Connect Pin 2 in PORTB and Pin 2 in PORTD with Pull-Up Resistors */
	SET_BIT(PORTB,2);
	SET_BIT(PORTD,2);
}
/********************** Interrupts Initializations ********************/
void Interrupt_init(void)
{
	/* Configure (INT0, INT1, INT2) as (any logical change, rising edge, Falling edge) respectively */
	/* INT0 */
	CLR_BIT(MCUCR,1);
	SET_BIT(MCUCR,0);
	/* INT1 */
	SET_BIT(MCUCR,3);
	SET_BIT(MCUCR,2);
	/* INT2 */
	CLR_BIT(MCUCSR,6);
	
	/* Enable Interrupt mask for external interrupt */
	SET_BIT(GICR,5);
	SET_BIT(GICR,6);
	SET_BIT(GICR,7);
	
	/* Enable Interrupt mask for general interrupt controller */
	sei();
}

int main(void)
{
	DIO_init();
	Interrupt_init();

	while(1)
	{
		CLR_BIT(PORTD,5);
		CLR_BIT(PORTD,6);
		CLR_BIT(PORTD,7);
	}
	return 0;
}


ISR(INT0_vect)
{
	SET_BIT(PORTD,5);
	_delay_ms(1000);
}

ISR(INT1_vect)
{
	SET_BIT(PORTD,6);
	_delay_ms(1000);
}

ISR(INT2_vect)
{
	SET_BIT(PORTD,7);
	_delay_ms(1000);
}