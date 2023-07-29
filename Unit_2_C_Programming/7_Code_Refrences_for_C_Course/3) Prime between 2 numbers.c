#include <stdlib.h>
#include <stdio.h>

void PrimeNumBetIntervals(int start , int end)
{
	int i=0 , j=0 , isPrime = 1;
	for(i=start+1; i<end ; i++)
	{
		for(j=2 ; j<i/2 ; j++)
		{
			if(i%j == 0)
			{
				isPrime = 0;
				break;
			}
		}

		if(isPrime)
		{
			printf("%d ",i);
		}

		isPrime = 1;
	}
}

int main(void)
{
	int number1,number2;
	printf("Enter the intervals of prime numbers:");
	fflush(stdout);
	scanf("%d %d",&number1,&number2);
	PrimeNumBetIntervals(number1,number2);
	return 0;
}
