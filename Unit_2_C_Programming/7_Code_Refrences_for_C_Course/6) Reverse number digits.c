#include <stdlib.h>
#include <stdio.h>

int ReverseNumber(int number)
{
	int reversedNum = 0;

	while(number!=0)
	{
		reversedNum += (number%10);
		reversedNum *= 10;
		number /=10;
	}
	reversedNum /= 10;

	return reversedNum;
}


int main(void)
{
	int number;
	printf("Enter number to reverse it:");
	fflush(stdout);
	scanf("%d",&number);
	printf("The reversed number is %d",ReverseNumber(number));
	return 0;
}
