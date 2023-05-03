#include <stdio.h>
#include <stdlib.h>
#include "string.h"

/*Prototypes*/
void PrimeNumbers(void);
long int factorialRecurseve(int num);
void sentenceReverse(char string[],int stringLength);
long int NumberPowerRecurseve(int num, int power);

int main(void)
{
	int example , factNum ,powNum , power;
	long int factResult , powResult;
	char string[100];
	printf("Choose which example you want to run: ");
	fflush(stdout);
	scanf("%d",&example);
	fflush(stdout);

	switch (example)
	{

	case 1:
		PrimeNumbers();
		break;

	case 2:
		printf("Enter an positive integer: ");
		fflush(stdout);
		scanf("%d",&factNum);
		factResult= factorialRecurseve(factNum);
		printf("Factorial of %d = %ld",factNum,factResult);
		break;

	case 3:
		printf("Enter a sentence: ");
		fflush(stdin);fflush(stdout);
		gets(string);
		sentenceReverse(string, strlen(string));

		printf("%s",string);
		break;

	case 4:
		printf("Enter base number: ");
		fflush(stdout);
		scanf("%d",&powNum);
		printf("Enter power number (positive integer): ");
		fflush(stdout);
		scanf("%d",&power);

		powResult = NumberPowerRecurseve(powNum,power);
		printf("%d^%d = %ld",powNum,power,powResult);
		break;

	default:	printf("There is no example with this number !!"); break;
	}

	return 0;
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

long int factorialRecurseve(int num)
{
	if(num == 1)
	{
		return 1;
	}
	else
	{
		return num*factorialRecurseve(num-1);
	}
}

void sentenceReverse(char string[],int stringLength)
{
	static int i=0 , lastIndx=0;
	char temp;
	/*Setting last index in first call to the end of the string*/
	if(i == 0)
	{
		lastIndx = stringLength-1;
	}
	else
	{
		lastIndx--;
	}

	/*if the first iterator exceeds the iterator comming from the end of string it will stop and the sentence is reversed*/
	if(i > lastIndx )
	{
		return;
	}
	else
	{
		/*Swapping*/
		temp = string[lastIndx];
		string[lastIndx] = string[i];
		string[i] = temp;
		i++;
		sentenceReverse(string,lastIndx);
	}
}

long int NumberPowerRecurseve(int num, int power)
{
	if(power == 0)
	{
		return 1;
	}
	else
	{
		return num*NumberPowerRecurseve(num,--power);
	}

}


