#include <stdio.h>
#include <stdlib.h>
#include "string.h"

int sumAllDigits(int x);
void PrimeNumbers(void);
int reverseNumber(int num);
int sum_from1to100_WithoutLoop();
void reverseArray(int arr[],int arrSize);
int countOnesInBinary(int num);
int uniqueNumInArr(int arr[],int arrSize);
void reverseWords(char str[]);
int maxOnesNumBetZeros(int num);
double squareRootOfNum(int num);

int main(void)
{
	int choice;
	int a[7] ={4,2,5,2,5,7,4};
	int a2[3]={4,2,4};
	int a3[5]={1,2,3,4,5};
	char str[] = "Mohamed Gamal";
	printf("Choose function\n"
			"------------------\n"
			"1-sum all digit\n"
			"2-calculate square root\n"
			"3-prime numbers between two numbers\n"
			"4-reverse digits in number\n"
			"5-count number of ones in binary number\n"
			"6-unique number in array\n"
			"7-sum numbers from 1 to 100(without loop)\n"
			"8-take an array and revers its elements\n"
			"9-reverse words in string\n"
			"10-count the max number of ones between two zeros\n"
			"-------------------------------------------------------\n"
			"Enter number that you have chosen: ");
	fflush(stdout);
	scanf("%d",&choice);

	switch(choice)
	{
	case 1:
		printf("Test case 1: %d\n",sumAllDigits(123));
		printf("Test case 2: %d\n",sumAllDigits(4565));
		break;

	case 2:
		printf("Test case 1: %.3lf\n",squareRootOfNum(4));
		printf("Test case 2: %.3lf\n",squareRootOfNum(10));
		break;

	case 3:
		PrimeNumbers();
		break;

	case 4:
		printf("Test case 1: %d\n",reverseNumber(2457));
		printf("Test case 2: %d\n",reverseNumber(1057));
		break;

	case 5:
		printf("Test case 1: %d\n",countOnesInBinary(5));
		printf("Test case 2: %d\n",countOnesInBinary(15));
		break;

	case 6:
		printf("Test case 1: %d\n",uniqueNumInArr(a,sizeof(a)/sizeof(a[0])));
		printf("Test case 2: %d\n",uniqueNumInArr(a2,sizeof(a2)/sizeof(a2[0])));
		break;

	case 7:
		printf("Test case: %d\n",sum_from1to100_WithoutLoop());
		break;

	case 8:
		reverseArray(a3,sizeof(a3)/sizeof(a3[0]));
		break;

	case 9:
		reverseWords(str);
		break;

	case 10:
		printf("Test case 1: %d\n",maxOnesNumBetZeros(14));
		printf("Test case 2: %d\n",maxOnesNumBetZeros(110));
		break;

	default:
		printf("Wrong Choice !!!!!");
		break;
	}
	return 0;
}

double squareRootOfNum(int num)		//using binary search
{
	int start=0 , end = num , mid , i;
	double ans;
	/*Finding integral part*/
	while (start <= end)
	{
		mid = (end+start)/2;
		if (mid * mid == num)			// This is perfect square
		{
			ans = mid;
			break;
		}
		/* the integral part will be in the right side
		 *  (that mean that number want to be bigger to get more closer to the integral part)
		 */
		else if(mid * mid < num)
		{
			ans = start;
			start = mid+1;
		}
		/* the integral part will be in the right side
		 *  (that mean that number want to be smaller to get more closer to the integral part)
		 */
		else
		{
			end = mid-1;				// the integral part will be in the left side
		}
	}
	/*Finding the decimal part*/
	float incrementing_value = 0.1;
	for(i=0 ; i < 3 ; i++)
	{
		while(ans *ans <= num)
		{
			ans += incrementing_value;
		}
		/*Substracting last incremented decimal num*/
		ans -= incrementing_value;
		/*calculating the next decimal number*/
		incrementing_value /=10;
	}
	return ans;
}

int maxOnesNumBetZeros(int num)
{
	int ones =0 , maxOnesCount=0;
	while (num != 0)			/*Loop to check if the number is zero after shifting*/
	{
		if((num&1) == 0)		/*Check if the ones start with zero before them*/
		{
			num = num >>1;		/*if yes shift one time and start counting until it ends with zero*/
			while((num&1) != 0)
			{
				ones++;
				num = num >>1;			/*counting ones and shifting the number to continue counting*/
			}
			if(ones > maxOnesCount)
			{
				maxOnesCount = ones;	/*Save the greatest number of ones occured*/
			}
			ones =0;
		}

	}
	return maxOnesCount;
}

void reverseWords(char str[])
{
	int i=0 , firstWordFlag = 0;;
	char reversedStr[100];
	for(i=strlen(str) -1 ; i>=0 ; i--)
	{
		if(str[i] == ' ' && firstWordFlag == 0) 	/*Copy the last word in empty string first*/
		{
			strcpy(reversedStr,str+i+1);
			firstWordFlag = 1;
			str[i] = '\0';
		}
		else if(str[i] == ' ' || i==0)				/*Concatenate the rest of the words based on its location*/
		{
			if(i==0)
			{
				strcat(reversedStr," ");
				strcat(reversedStr,str+i);
			}
			else
			{
				strcat(reversedStr,str+i);
				str[i] = '\0';
			}
		}
	}
	strcpy(str,reversedStr);
	printf("%s" ,str);
}

int sumAllDigits(int x)
{
	int sum =0;
	while(x!=0)
	{
		sum += (x%10);
		x /= 10;
	}
	return sum;
}

void PrimeNumbers(void)
{
	int firstNum, lastNum;
	int i=0 , j=0 , primeFlag =1;
	printf("Enter two numbers (intervals): ");
	fflush(stdout);
	scanf("%d %d",&firstNum,&lastNum);

	printf("Prime numbers between %d and %d are: ",firstNum,lastNum);
	for(i=firstNum+1 ; i<lastNum ; i++)
	{
		/*Check if the number divisible by any number and down the flag if it is not prime*/
		for(j=2 ; j <i/2 ; j++)
		{
			if(i%j == 0)
			{
				primeFlag = 0;
				break;
			}
		}

		/*Printing the number if the number is prime */
		if(primeFlag == 1)
		{
			printf("%d ",i);
		}
		/*Return the flags to normal state*/
		primeFlag=1;
	}
}

int reverseNumber(int num)
{
	int rem=0 , reversedNum=0;
	while (num != 0)
	{
		rem = num % 10;
		reversedNum = (reversedNum*10)+rem;
		num /=10;
	}
	return reversedNum;
}

int sum_from1to100_WithoutLoop()
{
	static int i=1 ,sum =0;
	if(i <= 100)
	{
		sum += i;
		i++;
		sum_from1to100_WithoutLoop();
	}
	return sum;

}

void reverseArray(int arr[],int arrSize)
{
	int i=0 , reversedIndex;
	reversedIndex = arrSize - 1;

	for(i=0;i<arrSize/2;i++)
	{
		/*Swapping*/
		arr[i] = arr[i]+arr[reversedIndex];
		arr[reversedIndex] = arr[i] - arr[reversedIndex];
		arr[i] = arr[i] - arr[reversedIndex];
		reversedIndex--;
	}

	for(i=0 ; i<arrSize ; i++)
	{
		printf("%d ",arr[i]);
	}
}

int countOnesInBinary(int num)
{
	int ones =0;
	while (num != 0)
	{
		ones += (num & 1);	// "And" the first bit with 1 and add the result to counter (It will be 0 or 1 only)
		num = num>>1;		//shifting the number right to continue counting depending on the first bit
	}
	return ones;
}

int uniqueNumInArr(int arr[],int arrSize)
{
	int uniqueNum=0 , i=0,j=0 , numCounts = 0;
	/*Sort array first*/
	for(i=0;i<arrSize-1 ;i++)
	{
		for(j=i+1;j<arrSize ;j++)
		{
			if(arr[i] > arr[j])
			{
				arr[i] = arr[i] + arr[j];
				arr[j] = arr[i] - arr[j];
				arr[i] = arr[i] - arr[j];
			}
		}
	}
	/*Get the unique number*/
	for(i=0;i<arrSize ;i++)
	{
		for(j=0;j<arrSize;j++)
		{
			if(arr[i] == arr[j])
				numCounts++;

			if(numCounts > 1)
				break;
		}
		if(numCounts == 1)
		{
			uniqueNum = arr[i];
			break;
		}
		else
			numCounts=0;
	}
	return uniqueNum;
}
