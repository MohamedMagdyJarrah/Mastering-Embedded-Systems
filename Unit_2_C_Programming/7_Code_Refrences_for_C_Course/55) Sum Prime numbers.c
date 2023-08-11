#include <stdlib.h>
#include <stdio.h>

int Prime(int number)
{
	int isPrime = 1 , i = 0;

	for(i=2 ; i<= number/2 ; i++)
	{
		if(number%i==0)
		{
			isPrime = 0;
			break;
		}
	}

	return isPrime;
}

int sumOfPrimeNumbers(int num)
{
	int sum = 0 , i =0;
	for(i = 1 ; i <= num ; i++ )
	{
		if(Prime(i))
		{
			sum += i;
		}
	}
	return sum;
}

int main()
{
	int num;
	printf("enter num:");
	fflush(stdout);
	scanf("%d",&num);
	printf("The sum of prime numbers until %d is %d",num,sumOfPrimeNumbers(num));
	return 0;
}
