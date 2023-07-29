#include <stdlib.h>
#include <stdio.h>

int countOnesInBinary(int number)
{
	int numOfOnes = 0;

	while(number != 0)
	{
		if((number & 1) == 1)
			numOfOnes++;
		number = number>>1;
	}

	return numOfOnes;
}

int main(void)
{
	int number;
	printf("Enter number to count its ones in binary:");
	fflush(stdout);
	scanf("%d",&number);
	printf("The number of ones in %d is %d",number,countOnesInBinary(number));
	return 0;
}
