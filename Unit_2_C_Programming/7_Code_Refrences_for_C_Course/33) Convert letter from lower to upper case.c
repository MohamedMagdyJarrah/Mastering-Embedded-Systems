#include <stdlib.h>
#include <stdio.h>

char convertLowertoUpper(char letter)
{
	return letter - 32;			/* 32 is the difference in ascii code */
}

int main(void)
{
	printf("%c",convertLowertoUpper('f'));
	return 0;
}
