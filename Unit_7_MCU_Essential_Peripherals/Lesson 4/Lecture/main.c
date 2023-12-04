#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define F_CPU		1000000UL
#include "stm32f103x6.h"
#include "MCAL/GPIO Driver/STM32F103x6_GPIO.h"
#include "MCAL/EXTI Driver/STM32F103x6_EXTI.h"
#include "HAL/LCD_Driver/LCD.h"

uint8_t IRQ_Flag = 0;

void wait_ms(uint32_t time)
{
	uint32_t i, j;
	for (i = 0; i < time; i++)
		for (j = 0; j < 255; j++);
}


void clock_init()
{
	// Enable clock GPIOA
	CLOCK_GPIOA_EN();
	// Enable clock GPIOB
	CLOCK_GPIOB_EN();
	// Enable clock AFIO
	CLOCK_AFIO_EN();
}

void EXTIB9_CallBack(void)
{
	IRQ_Flag = 1;
	LCD_SEND_STRING("IRQ_9 is happened by _|-");
	wait_ms(2000);
}

int main(void) {
	/* Enable the clocks of used ports and AFIO */
	clock_init();

	/* Initialize the LCD */
	LCD_INIT();
	LCD_SEND_COMMAND(LCD_CLEAR_SCREEN);

	/* Configure the EXTI */
	EXTI_PinConfig_t PinCfg;
	PinCfg.EXTI_PIN = EXTI9PB9;
	PinCfg.Trigger_Case = EXTI_TRIGGER_RISING;
	PinCfg.P_IRQ_CallBack = EXTIB9_CallBack;
	PinCfg.IRQ_EN = EXTI_STATE_ENABLE;
	MCAL_EXTI_GPIO_Init(&PinCfg);
	IRQ_Flag = 1;


	while (1)
	{
		if(IRQ_Flag)
		{
			LCD_SEND_STRING("HI");
			wait_ms(1000);
			LCD_SEND_COMMAND(LCD_CLEAR_SCREEN);
			IRQ_Flag = 0;
		}

	}
}

