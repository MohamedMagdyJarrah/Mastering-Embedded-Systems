#include <stdlib.h>
#include <stdio.h>

int reverseFirstAndLastDigit(int num)
{
	int firstDigit,lastDigit,newNum,numOfDigits=1;
	newNum = num;

	/* Get the first digit */
	firstDigit = num%10;
	num = num/10;
	numOfDigits *= 10;

	while(num > 10)
	{
		lastDigit = num/10;
		num = num/10;
		numOfDigits *= 10;
	}

	newNum = newNum - (numOfDigits*lastDigit);
	newNum = newNum + (numOfDigits*firstDigit);
	newNum /= 10;
	newNum = (newNum*10)+lastDigit;

	return newNum;
}


int main()
{
	int num;
	printf("enter num:");
	fflush(stdout);
	scanf("%d",&num);
	printf("The number %d after reversing the first and the last digits is %d",num,reverseFirstAndLastDigit(num));
	return 0;
}