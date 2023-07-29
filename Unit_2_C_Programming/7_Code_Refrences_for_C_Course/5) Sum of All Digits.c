#include <stdlib.h>
#include <stdio.h>

int SumAllDigit(int number)
{
	int sumDigit=0;

	while(number !=0)
	{
		sumDigit += (number%10);
		number /= 10;
	}

	return sumDigit;
}


int main(void)
{
	int number;
	printf("Enter number to get the sum of its all digits:");
	fflush(stdout);
	scanf("%d",&number);
	printf("The sum of all digits is %d",SumAllDigit(number));
	return 0;
}