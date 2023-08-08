#include <stdlib.h>
#include <stdio.h>

void countOnesAndZeroesInBin(int num, int* zeroes , int* ones)
{
	int i=0 , bits;
	*zeroes = 0;
	*ones = 0;
	bits = sizeof(num)*8;
	for(i=0 ; i<bits ; i++)
	{
		if((num>>i)&1)
			(*ones)++;
		else
			(*zeroes)++;
	}
}

int main()
{
	int num,ones,zeros;
	printf("enter num:");
	fflush(stdout);
	scanf("%d",&num);
	countOnesAndZeroesInBin(num,&ones,&zeros);
	printf("number of zeros is %d\nno of ones is %d",zeros,ones);
	return 0;
}