#include <stdlib.h>
#include <stdio.h>

int HighestCommonFactorBet2Nums(int num1 , int num2)
{
	int HCF = 0, i=0 , smallestNum;
	smallestNum = (num1<num2) ? num1:num2;

	for(i = smallestNum ; i>=0 ; i--)
	{
		if( (num1%i==0) && (num2%i==0) )
		{
			HCF = i;
			break;
		}
	}
	return HCF;
}


int main()
{
	int num1 , num2 ;
	printf("enter 2 num:");
	fflush(stdout);
	scanf("%d %d",&num1,&num2);
	printf("The highest common factor between %d and %d is %d",num1,num2,HighestCommonFactorBet2Nums(num1,num2));
	return 0;
}