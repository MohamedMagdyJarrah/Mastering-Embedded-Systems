#include "LIB/Platform_Types.h"
#include "LIB/Utils.h"
#include "LIB/STM32F103x6_MemMap.h"
#include "MCAL/GPIO Driver/GPIO_interface.h"
#include "MCAL/EXTI Driver/EXTI_interface.h"
#include "HAL/LCD Driver/LCD_interface.h"
#define F_CPU				8000000UL

void delay_ms(uint32_t time)
{
	for(uint32_t i =0 ; i<time ; i++)
	{
		for(uint8_t j=0 ; j<255 ; j++);
	}
}


void interruptFunc(void)
{
	LCD_SendString("IRQ0 is happened");
	delay_ms(2000);
}


int main(void)
{
	EXTI_PinConfig_t externalINT;
	externalINT.EXTI_PIN = EXTI_PIN_LINE0PB0;
	externalINT.Trigger_Case = EXTI_TRIGGER_FALLING;
	externalINT.IRQ_EN = EXTI_STATE_ENABLE;
	externalINT.P_IRQ_CallBack = interruptFunc;

	CLOCK_AFIO_EN();
	CLOCK_GPIOA_EN();
	CLOCK_GPIOB_EN();

	MCAL_EXTI_GPIO_Init(&externalINT);
	LCD_Init();


	while(1)
	{
		LCD_ClearDisplay();
	}
}
