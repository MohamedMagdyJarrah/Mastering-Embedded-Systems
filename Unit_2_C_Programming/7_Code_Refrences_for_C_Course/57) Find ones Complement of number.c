#include <stdlib.h>
#include <stdio.h>

unsigned char findOnesComplement(unsigned char num)
{
	int sizeOfnum = sizeof(num)*8 , i;

	for(i=0 ; i<sizeOfnum ; i++)
	{
		num = num ^ (1<<i);
	}

	return num;
}

void display_binary(unsigned char num)
{
	char i;
	for(i=7; i>=0; i--)
	{
		(num &(1<<i))?printf("1"):printf("0");

	}
}


int main()
{
	int num;
	printf("enter num:");
	fflush(stdout);
	scanf("%d",&num);
	printf("The ones complement of %d is %d\n",num,findOnesComplement(num));
	display_binary(150);
	printf("\n");
	display_binary(105);
	return 0;
}