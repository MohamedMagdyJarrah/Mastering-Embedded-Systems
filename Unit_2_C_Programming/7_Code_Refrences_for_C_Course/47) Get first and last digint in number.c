#include <stdlib.h>
#include <stdio.h>

void findFirstAndLastDigit(int num , int* firstDigit , int* lastDigit)
{
	*firstDigit = num%10;
	num = num/10;
	while(num > 10)
	{
		*lastDigit = num/10;
		num = num/10;
	}
}

int main()
{
	int num,firstdigit,lastDigit;
	printf("enter num:");
	fflush(stdout);
	scanf("%d",&num);
	findFirstAndLastDigit(num,&firstdigit,&lastDigit);
	printf("The first digit in %d is %d and the last digit is %d",num,firstdigit,lastDigit);
	return 0;
}