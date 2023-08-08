#include <stdlib.h>
#include <stdio.h>

int trailingZeroesInBinaryNum(int num)
{
	int i=0 , countZero = 0 , bits;
	bits = sizeof(num)*8;
	for(i=0 ; i<bits ; i++)
	{
		if(! ((num>>i)&1) )
			countZero++;
		else
			break;
	}
	return countZero;
}


int main()
{
	int num;
	printf("enter num:");
	fflush(stdout);
	scanf("%d",&num);
	int ret=trailingZeroesInBinaryNum(num);
	printf("number of trailing zeros is %d",ret);
	return 0;
}