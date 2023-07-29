#include <stdlib.h>
#include <stdio.h>

#define ISPRIME		1

int Prime(int number)
{
	int isPrime = 1 , i = 0;

	for(i=2 ; i<number/2 ; i++)
	{
		if(number%i==0)
		{
			isPrime = 0;
			break;
		}
	}

	return isPrime;
}

int main(void)
{
	int number;
	printf("Enter the number you want to check is it prime or not:");
	fflush(stdout);
	scanf("%d",&number);
	Prime(number) == ISPRIME ? printf("%d is prime number",number) : printf("%d isn't prime number",number);
	return 0;
}
