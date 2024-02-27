#include "LIB/Platform_Types.h"
#include "LIB/Utils.h"
#include "LIB/STM32F103x6_MemMap.h"
#include "MCAL/GPIO Driver/GPIO_interface.h"
#include "MCAL/EXTI Driver/EXTI_interface.h"
#include "MCAL/USART Driver/USART_interface.h"
#include "HAL/LCD Driver/LCD_interface.h"
#include "HAL/Keypad Driver/Keypad_interface.h"

#define F_CPU				8000000UL

uint8_t IRQ_Flag = 0;
uint8_t Control_Reg = 0;
uint8_t IPSR_Reg = 0;

void wait_ms(uint32_t time)
{
	uint32_t i, j;
	for (i = 0; i < time; i++)
		for (j = 0; j < 255; j++);
}


void clock_init()
{
	// Enable clock GPIOA
	RCC_GPIOA_EN();
	// Enable clock GPIOB
	RCC_GPIOB_EN();
	// Enable clock AFIO
	RCC_AFIO_EN();
}

void EXTIB9_CallBack(void)
{
	IRQ_Flag = 1;

	/* Executing 3 no operation commands in assembly to abstract our assembly commands */
	__asm("nop \n\t nop \n\t nop \n\t");


	__asm("MRS %[out],IPSR"
			: [out] "=r" (IPSR_Reg)
	);


	__asm("nop \n\t nop \n\t nop \n\t");

}

int main(void) {
	/* Enable the clocks of used ports and AFIO */
	clock_init();


	/* Configure the EXTI */
	EXTI_PinConfig_t PinCfg;
	PinCfg.EXTI_PIN = EXTI_PIN_LINE9PB9;
	PinCfg.Trigger_Case = EXTI_TRIGGER_RISING;
	PinCfg.P_IRQ_CallBack = EXTIB9_CallBack;
	PinCfg.IRQ_EN = EXTI_STATE_ENABLE;
	MCAL_EXTI_GPIO_Init(&PinCfg);
	IRQ_Flag = 1;


	/* Executing 3 no operation commands in assembly to abstract our assembly commands */
	__asm("nop \n\t nop \n\t nop \n\t");


	__asm("MRS %[out],CONTROL"
			: [out] "=r" (Control_Reg)			// Defining the output parameter that will saved in Control_Reg with option write only "=r"
	);


	__asm("nop \n\t nop \n\t nop \n\t");



	while (1)
	{
		if(IRQ_Flag)
		{
			IRQ_Flag = 0;
		}

	}
}
