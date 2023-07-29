#include <stdlib.h>
#include <stdio.h>

void PrintBinaryRepresentaion(int number)
{
	char BinaryNum[32];
	char *finalBinary = &BinaryNum[31];
	*finalBinary = '\0';

	do
	{
		finalBinary--;
		*finalBinary = "01"[number%2];
		number /= 2;

	}while(number!=0);

	printf("%s",finalBinary);
}

int main(void)
{
	int number;
	printf("Enter number to print it in binary:");
	fflush(stdout);
	scanf("%d",&number);
	PrintBinaryRepresentaion(number);
	return 0;
}
