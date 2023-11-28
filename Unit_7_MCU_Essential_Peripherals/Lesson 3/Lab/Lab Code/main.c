#include "MCAL_H/STM32F103x6_GPIO.h"
typedef volatile unsigned int vuint32_t ;



/* Pins Configurations */
//GPIO_PinConfig_t A1 =  {GPIO_PIN_1,GPIO_MODE_INPUT_FLOATING};
//GPIO_PinConfig_t A13 = {GPIO_PIN_13,GPIO_MODE_INPUT_FLOATING};
//GPIO_PinConfig_t B1 =  {GPIO_PIN_1,GPIO_MODE_OUTPUT_PUSH_PULL_2_MHZ};
//GPIO_PinConfig_t B13 = {GPIO_PIN_13,GPIO_MODE_OUTPUT_PUSH_PULL_2_MHZ};

GPIO_PinConfig_t PORTA =  {GPIO_PIN_ALL,GPIO_MODE_PORT_INPUT_FLOATING};
GPIO_PinConfig_t PORTB = {GPIO_PIN_ALL,GPIO_MODE_PORT_OUTPUT_PUSH_PULL_2_MHZ};

int main(void)
{
	unsigned int x=0;

	/* Enable Clocks */
	CLOCK_GPIOA_EN();
	CLOCK_GPIOB_EN();
	/* Configure the pins */
//	MCAL_GPIO_Init(GPIOA,&A1);
//	MCAL_GPIO_Init(GPIOA,&A13);
//	MCAL_GPIO_Init(GPIOB,&B1);
//	MCAL_GPIO_Init(GPIOB,&B13);

		MCAL_GPIO_Init(GPIOA,&PORTA);
		MCAL_GPIO_Init(GPIOB,&PORTB);
	while(1)
	{
		/* Check if Pin A1 is pressed */
		/* Pull-up pin */
		if(  MCAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1) == GPIO_PINSTATE_LOW ) // Single Pressing
		{
			/* Toggle Pin B1 */
			MCAL_GPIO_TogglePin(GPIOB,GPIO_PIN_1);

			/* Polling on the pin to make the pin act as single press*/
			while(MCAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)== GPIO_PINSTATE_LOW);
		}

		/* Check if Pin A13 is pressed */
		/* Pull-down pin */
		if( MCAL_GPIO_ReadPin(GPIOA,GPIO_PIN_13)== GPIO_PINSTATE_HIGH )	// Multi Pressing
		{
			/* Toggle Pin B13 */
			MCAL_GPIO_TogglePin(GPIOB,GPIO_PIN_13);

			/* Without polling to make it multiple press only solve de-bouncing issue with delay */
			for(x=0;x<255;x++);
		}
	}
}

