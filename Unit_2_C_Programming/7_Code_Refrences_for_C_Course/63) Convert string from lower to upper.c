#include <stdlib.h>
#include <stdio.h>

void convertStringToUpper(char* str)
{
	while(*str != '\0')
	{
		*str = (*str) - 32 ;
		str++;
	}
}

int main()
{
	char str[50] = "mohamed";
	printf("String before converting to upper is %s\n",str);
	convertStringToUpper(str);
	printf("String after converting to upper is %s",str);
	return 0;
}