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
#define GPIOA_CRH		*(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR		*(volatile uint32_t *)(GPIOA_BASE + 0x0C)

/********************** AFIO Registers ********************/
#define AFIO_BASE 		0x40010000
#define AFIO_EXTICR1 	*(volatile uint32_t *)(AFIO_BASE + 0x08)

/********************** EXTI Registers ********************/
#define EXTI_BASE 		0x40010400
#define EXTI_IMR 		*(volatile uint32_t *)(EXTI_BASE + 0x00)
#define EXTI_RTSR 		*(volatile uint32_t *)(EXTI_BASE + 0x08)
#define EXTI_PR 		*(volatile uint32_t *)(EXTI_BASE + 0x14)

/********************** NVIC Registers ********************/
#define NVIC_ISER0		*(volatile uint32_t *)(0xE000E100)

/********************** Clock Initialization ********************/
void Clock_init(void)
{
	/* Use internal HSI_RC */
	/* Enable the HSI to be the source of the sysclk */
	RCC_CFGR |= (0b00<<0);

	/* Enable the HSI*/
	RCC_CR |= (1<<0);

	/* Enable GPIOA Peripheral */
	RCC_APB2ENR |= (1<<2);

	/* Enable AFIO Peripheral */
	RCC_APB2ENR |= (1<<0);
}

/********************** GPIOA Initialization ********************/
void GPIO_init(void)
{
	/* Initialize Pin 13 as output */
	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x00200000;

	/* Initialize Pin 0 as floating input */
	GPIOA_CRH |= (0b01<<2);

	/* Select the input source of the External interrupt to be PORTA Pin 0 */
	AFIO_EXTICR1 |= (0b0000<<0); /* not necessary because it zero by default*/
}

/********************** Interrupt Initialization ********************/
void Interrupt_init(void)
{
	/* Configure the interrupt trigger to be rising edge for Pin0 */
	EXTI_RTSR |= (1<<0);
	/* enable the external interrupt for this pin */
	EXTI_IMR |= (1<<0);
	/* Enable the external interrupt from interrupt controller which has index 6 in vector table */
	NVIC_ISER0 |= (1<<6);
}


int main(void)
{
	Clock_init();
	GPIO_init();
	Interrupt_init();

	while(1);
}

void EXTI0_IRQHandler(void)
{
	/* Toggle the led  */
	GPIOA_ODR ^= (1<<13) ;

	/* Clear the pending flag of the interrupt */
	EXTI_PR |= (1<<0);
}
