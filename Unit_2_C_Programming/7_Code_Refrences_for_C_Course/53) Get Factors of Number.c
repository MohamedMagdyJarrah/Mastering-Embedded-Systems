#include <stdlib.h>
#include <stdio.h>

void getFactorOfNum(int num)
{
	int i=0;
	printf("num = %d -> factors: ",num);
	for(i=1 ; i <= num ; i++)
	{
		if(num%i == 0)
			printf("%d ",i);
	}
	printf("\n");
}

int main()
{
	int num;
	printf("enter num:");
	fflush(stdout);
	scanf("%d",&num);
	getFactorOfNum(num);
	return 0;
}