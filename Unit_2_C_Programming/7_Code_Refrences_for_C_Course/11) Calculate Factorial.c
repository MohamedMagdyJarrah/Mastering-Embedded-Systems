#include <stdlib.h>
#include <stdio.h>

unsigned int Factorial(int number)
{
	int result = 1 , i = 0;
	for(i=number ; i> 0 ; i--)
	{
		result *= i;
	}
	return result;
}
unsigned int FactorialRecursive(int number)
{
	static int result = 1;

	if(number > 0)
	{
		result *= number;
		FactorialRecursive(number-1);
	}
	return result;
}

int main(void)
{
	int number;
	printf("Enter number to get its factorial: ");
	fflush(stdout);
	scanf("%d",&number);
	printf("The factorial of %d is %d\n",number,Factorial(number));
	printf("The factorial (Recursive Function) of %d is %d",number,FactorialRecursive(number));
	return 0;
