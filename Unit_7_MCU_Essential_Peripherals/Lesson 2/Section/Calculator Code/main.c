#include <avr/io.h>
#include "LCD Driver/LCD.h"
#include "KEYPAD Driver/KPD.h"

int main(void)
{
	/* Initialize variables*/
	char keypressed = 0, op = 0;
	int num1 = 0 , num2= 0 , result = 0; 
	
	/* Initialize I/O devices */
	KEYPAD_INIT();
	LCD_INIT();
	
	/* Application */
	while (1) 
    {
		/* Take the reading continuously */
		keypressed = KEYPAD_GET_KEY();
		
		/* If I didn't press on the keypad It will return ? so don't do anything */
		if (keypressed != '?')
		{
		/* Print every key pressed on the LCD */
		LCD_SEND_CHAR(keypressed);
		/* If I pressed on any operator on the keypad I will save it to do the calculations later */
		if (keypressed == '+' || keypressed == '-' || keypressed == '*' || keypressed == '/' )
		{
			op = keypressed;
		}
		/* Saving the first operand until I press on the operator I want */
		if((keypressed>='0' && keypressed<='9') && (op==0))
		{
			num1 += (keypressed-48);
			num1 *= 10;
		}
		/* Saving the second operand until I pressed on the wanted operator */
		if((keypressed>='0' && keypressed<='9') && (op!=0))
		{
			num2 += (keypressed-48);
			num2 *= 10;
		}		
		/* After pressing on = sign the calculations will occur according to the saved operator */
		if (keypressed == '=')
		{
			switch(op)
			{
				case '+': result = (num1/10) + (num2/10); break;
				case '-': result = (num1/10) - (num2/10); break;
				case '*': result = (num1/10) * (num2/10); break;
				case '/': result = (num1/10) / (num2/10); break;
			}
			/* Showing the result in the second line */
			LCD_GO_TO_XY(1,0);
			LCD_SEND_NUMBER(result);
			
			/* And wait until the user to restart the keypad by pressing on @ key, then clear the screen */
			while(keypressed != '@')
			{
				keypressed = KEYPAD_GET_KEY();
			}
			LCD_SEND_COMMAND(LCD_CLEAR_SCREEN);
			/* Re-initialize all the variables to use them in the next operation */
			result=0 , num1 = 0 ,num2 = 0 , op = 0;
		}
		}
    }
}

