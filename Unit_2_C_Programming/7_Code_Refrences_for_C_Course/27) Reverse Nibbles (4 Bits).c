#include <stdlib.h>
#include <stdio.h>

unsigned char Reverse4Bits_Nibbles(unsigned char num)
{
	return num << 4 | num >> 4;
}

int main(void)
{
	printf("When you reverse nibbles of %d it will be %d",149,Reverse4Bits_Nibbles(149));
	return 0;
}
