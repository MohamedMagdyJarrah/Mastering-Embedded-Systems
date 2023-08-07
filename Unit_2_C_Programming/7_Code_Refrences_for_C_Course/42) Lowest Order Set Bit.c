#include <stdlib.h>
#include <stdio.h>

int lowestOrderSetBit(int num)
{
	int numSize = sizeof(num)*8 , i;
	for(i=0 ; i< numSize ; i++)
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
	printf("%d",lowestOrderSetBit(num));
	return 0;
}