#include "LIB/Platform_Types.h"
#include "LIB/Utils.h"
#include "LIB/STM32F103x6_MemMap.h"
#include "MCAL/GPIO Driver/GPIO_interface.h"
#include "MCAL/EXTI Driver/EXTI_interface.h"
#include "MCAL/USART Driver/USART_interface.h"
#include "HAL/LCD Driver/LCD_interface.h"
#include "HAL/Keypad Driver/Keypad_interface.h"
#define F_CPU				8000000UL

typedef enum accessMode
{
	privileged,
	unprivileged
}accessMode;


void SwitchCpuAccesss(accessMode mode)
{
	switch (mode)
	{
	case privileged:

		__asm("MRS R3,CONTROL \n\t"		// Store the value of the Control register in general purpose register
			  "LSR R3,R3,#0x1 \n\t"		// Shift right the value of the control register
			  "LSL R3,R3,#0x1 \n\t"		// Then shift it left again to to make the first bit(LSB) to be zero (privileged access)
			  "MSR CONTROL,R3");		// Store the result again in the control register

		break;

	case unprivileged:

		__asm("MRS R3,CONTROL \n\t"	// Store the value of the Control register in general purpose register
			  "ORR R3,R3,#0x1 \n\t"	// Or the first bit (LSB) with one to switch to unprivileged access
			  "MSR CONTROL,R3");	// Store the result again in the control register

		break;
	}
}

void HardFault_Handler()
{

}



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
	SwitchCpuAccesss(privileged); /* We switch here the access mode because we was in unprivileged mode and to change access
									the only way to switch from handler mode as in handler mode the default is privileged mode */
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

	SwitchCpuAccesss(unprivileged);
	SwitchCpuAccesss(privileged);

	while (1)
	{
		if(IRQ_Flag)
		{
			IRQ_Flag = 0;
		}

	}
}
