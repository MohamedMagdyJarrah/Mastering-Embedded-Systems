#include <stdlib.h>
#include <stdio.h>

int power(int base,int exponent)
{
	int result = 1;
	while(exponent != 0)
	{
		result *= base;
		exponent--;
	}
	return result;
}

int main()
{
	int base,exp;
	printf("enter base & exponent:");
	fflush(stdout);
	scanf("%d %d",&base,&exp);
	printf("The result is %d",power(base,exp));
	return 0;
}