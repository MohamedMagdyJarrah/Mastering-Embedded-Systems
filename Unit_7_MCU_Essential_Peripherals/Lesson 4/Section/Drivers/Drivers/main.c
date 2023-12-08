#include "ATMEGA32.h"
#include "ATMEGA32_GPIO.h"
#include "LCD.h"

int main(void)
{
    /* Replace with your application code */
    LCD_INIT();
	//LCD_SEND_COMMAND(LCD_CLEAR_SCREEN);
	//LCD_SEND_CHAR('M');
	LCD_SEND_STRING("Learn in Depth");
	
	while (1) 
    {
    }
}

