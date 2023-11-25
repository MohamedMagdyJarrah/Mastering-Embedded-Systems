//#include "LIB/Platform_Types.h"
#include "LIB/Utils.h"
#include "DIO_registers.h"
#define F_CPU 8000000UL
#include <util/delay.h>


#define TASK_1_LEDS							0
#define TASK_2_LEDS_WITH_BUTTON				1
#define TASK_3_7_SEGMENT_MULTIPLEXING		2		
#define CURRENT_TASK						TASK_1_LEDS

void DIO_init()
{
	/* Configure PINs (D) 4,5,6,7 as outputs */
	SET_BIT(DDRD,4);
	SET_BIT(DDRD,5);
	SET_BIT(DDRD,6);
	SET_BIT(DDRD,7);
	
	/* Configure PINs (C) 2,3,4,5,6,7 as outputs */
	SET_BIT(DDRC,2);
	SET_BIT(DDRC,3);
	SET_BIT(DDRC,4);
	SET_BIT(DDRC,5);
	SET_BIT(DDRC,6);
	SET_BIT(DDRC,7);
	
	/* Set the initial state (D) to be 0 volt */
	CLR_BIT(PORTD,4);
	CLR_BIT(PORTD,5);
	CLR_BIT(PORTD,6);
	CLR_BIT(PORTD,7);
	
	/* Set the initial state (C) to be 0 volt */
	CLR_BIT(DDRC,2);
	CLR_BIT(DDRC,3);
	CLR_BIT(DDRC,4);
	CLR_BIT(DDRC,5);
	CLR_BIT(DDRC,6);
	CLR_BIT(DDRC,7);
	
	/* Configure PIN 0 as input */
	CLR_BIT(DDRD,0);
}

int main(void)
{
	unsigned char i=0,j=0;
	unsigned char counter=4;
	DIO_init();
	
    while (1) 
    {
		/************************************* Task 1 *************************************/
		#if CURRENT_TASK == TASK_1_LEDS
		for(i=5;i<=7;i++)
		{
			SET_BIT(PORTD,i);
			_delay_ms(1000);
		}
		for(i=7;i>=5;i--)
		{
			CLR_BIT(PORTD,i);
			_delay_ms(1000);
		}
		/************************************* Task 2 *************************************/
		#elif CURRENT_TASK == TASK_2_LEDS_WITH_BUTTON
		if (GET_BIT(PIND,0) == 1)
		{
			if(counter == 7)
			{
				SET_BIT(PORTD,4);
				counter=4;
			}
			else
			{
				counter++;
				SET_BIT(PORTD,counter);
			}
			
			/* Polling until release the switch */
			while (GET_BIT(PIND,0) == 1);
		}
		/************************************* Task 3 *************************************/
		#elif CURRENT_TASK == TASK_3_7_SEGMENT_MULTIPLEXING
		for (i=0 ; i<10 ; i++)
		{
			for (j=0 ; j<10 ; j++)
			{
				PORTC = 0b1011 | (i<<4);
				_delay_ms(500);
				PORTC = 0b0111 | (j<<4);
				_delay_ms(500);
			}
		}
		#endif
    }
}

