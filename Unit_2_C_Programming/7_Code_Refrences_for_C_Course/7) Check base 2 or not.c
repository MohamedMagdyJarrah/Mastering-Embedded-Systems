#include <stdlib.h>
#include <stdio.h>

#define ISBASETWO	1

int CheckBaseTwoOrNot(int number)
{
	int isBaseTwo = 0;

//	while(number > 2)
//	{
//		if(number%2==0)
//			number /= 2;
//		else
//			break;
//	}
//	if(number == 2)
//		isBaseTwo = 1;


	/****** Best Answer ******/
	// (number & (number-1)) == 0  means if the number is the one which add new bit to the left it will be base 2
	// ex: 	 8 --> 1000	& (8-1)=7 --> 111 here we find to represent the binary of 8 we add one bit to the left
	if( (number !=0) && ((number & (number-1)) == 0) )
	{
		isBaseTwo = 1;
	}

	return isBaseTwo;
}

int main(void)
{
	int number;
	printf("Enter number to check whether the num base 2 or not:");
	fflush(stdout);
	scanf("%d",&number);
	CheckBaseTwoOrNot(number) == ISBASETWO ? printf("The %d is base 2",number) : printf("The %d isn't base 2",number);
	return 0;
}
