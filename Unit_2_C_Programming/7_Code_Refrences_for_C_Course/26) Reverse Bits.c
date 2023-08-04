#include <stdlib.h>
#include <stdio.h>

int ReverseBits(unsigned char num)
{
	unsigned char reversedNum = 0 , i=0;
	for(i=0 ; i < 8 ; i++)
	{
		reversedNum = reversedNum << 1;
		reversedNum = reversedNum | ( (num>>i) & 1 );
	}

	return reversedNum;
}

int main(void)
{
	printf("When you reverse bits of %d it will be %d",149,ReverseBits(149));
	return 0;
}