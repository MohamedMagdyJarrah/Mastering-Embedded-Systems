#include "ATMEGA32.h"
#include "MCAL/GPIO Driver/ATMEGA32_GPIO.h"
#include "MCAL/USART Driver/ATMEGA32_USART.h"
#include "HAL/LCD Driver/LCD.h"

int main(void)
{
	uint8_t buff[5];
	
	GPIO_PinConfig_t pinConfig;
	pinConfig.GPIO_PinNumber = GPIO_PIN_0;
	pinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(GPIOD,&pinConfig);
	
	pinConfig.GPIO_PinNumber = GPIO_PIN_1;
	pinConfig.GPIO_Mode = GPIO_MODE_OUTPUT;
	MCAL_GPIO_Init(GPIOD,&pinConfig);
	
	MCAL_USART_voidInit();
	LCD_INIT();
	
	LCD_SEND_STRING("Welcome to UART");
	
	
	USART_SendStringSynch("Mohamed");

	
	while (1) 
    {
		LCD_GO_TO_XY(1,0);
		USART_RecieveBufferSynch(buff,5);
		LCD_SEND_STRING(buff);
    }
}

