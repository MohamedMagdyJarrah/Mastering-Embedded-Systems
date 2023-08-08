#include <stdlib.h>
#include <stdio.h>


void convertDecToBinary(unsigned int num)
{
	int numSize = sizeof(num)*8 , i;
	for(i=numSize-1 ; i>=0 ; i--)
	{
		((num>>i)&1) ? printf("1") : printf("0");
	}
	printf("\n");
}

int main()
{
	int num;
	printf("enter num:");
	fflush(stdout);
	scanf("%d",&num);
	convertDecToBinary(num);
	return 0;
}