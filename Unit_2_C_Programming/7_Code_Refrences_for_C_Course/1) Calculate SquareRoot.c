#include <stdlib.h>
#include <stdio.h>

double SquareRoot(int number)
{
	int start=0 , end = number , mid , i;
	double result;

	/* Finding the integral Part*/
	while(start <= end)				//0<=5		3<=5	3<=3
	{
		mid = (start+end)/2;		//mid = 2 , mid = 4	,mid =3
		/* Perfect Square */
		if(mid*mid == number)
		{
			result = mid;
			break;
		}
		/* The number should be in the right side if the multiplication is smaller than the result (Should be bigger) */
		else if(mid*mid < number)	//2*2<5
		{
			result = start;			//result = 0
			start = mid+1;			//start = 3
		}
		/* The number should be in the left side if the multiplication is bigger than the result (Should be smaller) */
		else
		{
			end = mid-1;			//end = 3		//end =2
		}
	}

	/* Finding the Decimal Part with percison up to 3 decimals*/
	float increamentingValue = 0.1;
	for(i=0 ; i<3 ;i++)
	{
		/* Approx the number as we can */
		while(result*result<number)
		{
			result += increamentingValue;
		}
		/* Subtract the last incremented decmial value (Because of While Coniditon)*/
		result -= increamentingValue;
		/* Move to the next decimal number*/
		increamentingValue /=10;
	}

	return result;
}



int main(void)
{
	int number;
	printf("Enter the number you want to calculate its Square root:");
	fflush(stdout);
	scanf("%d",&number);
	printf("The Square root is %.3lf",SquareRoot(number));
	return 0;
}
