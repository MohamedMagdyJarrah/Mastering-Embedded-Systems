#include <stdlib.h>
#include <stdio.h>

int NearestTenthNum(int number)
{
	int result;

	if( (number%10) > 5 )
	{
		result = number + (10 -(number%10));
	}
	else
	{
		result = number - (number%10);
	}

	return result;
}

int main(void)
{
	int number;
	printf("Enter number to get its nearest 10th:");
	fflush(stdout);
	scanf("%d",&number);
	printf("The Nearest 10th is %d",NearestTenthNum(number));
	return 0;
}
