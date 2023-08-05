#include <stdlib.h>
#include <stdio.h>


void checkEvenOrOdd(unsigned char num)
{
	(num&1) ? printf("%d is odd number",num) : printf("%d is even number",num);
}


int main(void)
{
	checkEvenOrOdd(6);
	return 0;
}