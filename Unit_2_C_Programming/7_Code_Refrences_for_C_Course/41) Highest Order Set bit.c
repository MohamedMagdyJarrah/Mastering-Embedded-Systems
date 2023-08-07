#include <stdlib.h>
#include <stdio.h>

int highestOrderSetBit(int num)
{
	int numSize = sizeof(num)*8 , i;
	for(i=numSize-1 ; i>=0 ; i--)
	{
		if((num>>i)&1)
		{
			break;
		}
	}
	return i;
}

int main()
{
	int num = 22;
	printf("%d",highestOrderSetBit(num));
	return 0;
}