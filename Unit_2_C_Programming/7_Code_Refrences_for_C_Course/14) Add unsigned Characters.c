#include <stdlib.h>
#include <stdio.h>

unsigned short addUnsignedCharacters(unsigned char num1 ,unsigned char num2)
{
	return num1+num2;
}

int main(void)
{
	unsigned char x = 120 ,y = 160;
	printf("The Result of %d+%d is %d",x,y,addUnsignedCharacters(x,y));
	return 0;
}