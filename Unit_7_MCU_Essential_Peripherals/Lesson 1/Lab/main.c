#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef volatile unsigned int vuint32_t ;

/********************** RCC Registers ********************/
#define RCC_BASE 		 0x40021000
#define RCC_CR 			*(volatile uint32_t *)(RCC_BASE + 0x00)
#define RCC_CFGR 		*(volatile uint32_t *)(RCC_BASE + 0x04)
#define RCC_APB2ENR	 	*(volatile uint32_t *)(RCC_BASE + 0x18)

/********************** GPIOA Registers ********************/
#define GPIOA_BASE 		0x40010800
#define GPIOA_CRL		*(volatile uint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA_CRH		*(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR		*(volatile uint32_t *)(GPIOA_BASE + 0x0C)
#define GPIOA_IDR		*(volatile uint32_t *)(GPIOA_BASE + 0x08)
/********************** GPIOB Registers ********************/
#define GPIOB_BASE 		0x40010C00
#define GPIOB_CRL		*(volatile uint32_t *)(GPIOB_BASE + 0x00)
#define GPIOB_CRH		*(volatile uint32_t *)(GPIOB_BASE + 0x04)
#define GPIOB_ODR		*(volatile uint32_t *)(GPIOB_BASE + 0x0C)
#define GPIOB_IDR		*(volatile uint32_t *)(GPIOB_BASE + 0x08)

/********************** Clock Initialization ********************/
void Clock_init(void)
{
	/* Use internal HSI_RC */
	/* Enable the HSI to be the source of the SYSCLK */
	RCC_CFGR |= (0b00<<0);

	/* Enable the HSI*/
	RCC_CR |= (1<<0);

	/* Enable GPIOA Peripheral */
	RCC_APB2ENR |= (1<<2);

	/* Enable GPIOB Peripheral */
	RCC_APB2ENR |= (1<<3);
}

/********************** GPIOA Initialization ********************/
void GPIO_init(void)
{
	/* Clear CRH and CRL Registers to configure it */
	GPIOA_CRL = 0;
	GPIOA_CRH = 0;
	GPIOB_CRL = 0;
	GPIOB_CRH = 0;
	GPIOA_ODR = 0;
	GPIOB_ODR = 0;

	/* Make Pin A1 as input floating */
	GPIOA_CRL &= ~(0b11<<4);	// Configure it in input mode
	GPIOA_CRL |= (0b01<<6);		// Configure it as floating

	/* Make Pin A13 as input floating */
	GPIOA_CRH &= ~(0b11<<20);	// Configure it in input mode
	GPIOA_CRH |= (0b01<<22);	// Configure it as floating

	/* Make Pin B1 as output push-pull */
	GPIOB_CRL |= (0b01<<4);		// Configure it in output mode with speed 10 MHZ
	GPIOB_CRL &= ~(0b11<<6);	// Configure it as push-pull

	/* Make Pin B13 as output push-pull */
	GPIOB_CRH |= (0b01<<20);	// Configure it in output mode with speed 10 MHZ
	GPIOB_CRH &= ~(0b11<<22);	// Configure it as push-pull
}



int main(void)
{
	unsigned int x=0;

	/* Initialization of the peripherals */
	Clock_init();
	GPIO_init();

	while(1)
	{
		/* Check if Pin A1 is pressed */
		/* Pull-up pin */
		if(  ((GPIOA_IDR & (1<<1))>>1) == 0 ) // Single Pressing
		{
			/* Toggle Pin B1 */
			GPIOB_ODR ^= (1<<1);

			/* Polling on the pin to make the pin act as single press*/
			while(((GPIOA_IDR & (1<<1))>>1) == 0 );
		}

		/* Check if Pin A13 is pressed */
		/* Pull-down pin */
		if( ((GPIOA_IDR & (1<<13))>>13) == 1 )	// Multi Pressing
		{
			/* Toggle Pin B13 */
			GPIOB_ODR ^= (1<<13);

			/* Without polling to make it multiple press only solve de-bouncing issue with delay */
			for(x=0;x<255;x++);
		}
	}
}

