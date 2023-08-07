#include <stdlib.h>
#include <stdio.h>

#define RIGHT_SHIFT		1
#define LEFT_SHIFT		0

int setBit(int num, int bitNum)
{
	num |= (1<<bitNum);
	return num;
}
int clrBit(int num, int bitNum)
{
	num &= ~(1<<bitNum);
	return num;
}
int toggleBit(int num, int bitNum)
{
	num ^= (1<<bitNum);
	return num;
}
int checkBit(int num, int bitNum)
{
	return ((num>>bitNum)&1) ? 1 : 0;
}
int circularShift(unsigned char num,char shift,char dir)
{
	int numBits = sizeof(num)*8;
	switch (dir)
	{
		case RIGHT_SHIFT:
			num = (num>>shift) | (num << (numBits-shift));
			break;
		case LEFT_SHIFT:
			num = (num<<shift) | (num >> (numBits-shift));
			break;
	}
	return num;
}


int main()
{
	int num = 250;
	printf("%d",circularShift(num,2,RIGHT_SHIFT));
	return 0;
}
