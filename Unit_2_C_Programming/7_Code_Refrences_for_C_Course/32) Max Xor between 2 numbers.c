#include <stdlib.h>
#include <stdio.h>

int Max_Xor(int a , int b)
{
	int maxResult = 0 , i=0 ,j=0;
	for(i=a ; i<b ; i++)
	{
		for(j=i+1 ; j<=b ; j++)
		{
			if((i^j) > maxResult)
			{
				maxResult = i^j;
			}
		}
	}
	return maxResult;
}

int main(void)
{
	int A,B;
	printf("enter A:");
	fflush(stdout);
	scanf("%d",&A);
	printf("enter B:");
	fflush(stdout);
	scanf("%d",&B);
	int ret=Max_Xor(A,B);
	printf("max xor=%d",ret);
	return 0;
}
