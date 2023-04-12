#include <stdio.h>
#include <stdlib.h>

/***********************************************************************************/
/*************** C Program to Check whether a Number is Odd or Even ****************/
/***********************************************************************************/
void EX1()
{
	int x;
	printf("Enter an integer you want to check: ");
	fflush(stdout);
	scanf("%d",&x);

	if(x%2 == 0)
	{
		printf("%d is even",x);
	}
	else
	{
		printf("%d is odd",x);
	}
}

/***********************************************************************************/
/******************* C Program to Check Vowel or Consonant *************************/
/***********************************************************************************/
void EX2()
{
	char x;
	printf("Enter an alphabet: ");
	fflush(stdout);
	scanf("%c",&x);
	switch(x)
	{
	case 'a':case 'A':case 'i':case 'I':case 'o':case 'O':case 'e':case 'E':case 'u':case 'U':
		printf("%c is a vowel",x);
		break;
	default:
		printf("%c is a consonant",x);
		break;
	}
}

/***********************************************************************************/
/*********** C Program to Find the Largest Number among Three Numbers **************/
/***********************************************************************************/
void EX3()
{
	float x,y,z;
	printf("Enter three numbers: ");
	fflush(stdout);
	scanf("%f %f %f",&x,&y,&z);

	if(x > y)
	{
		if(x > z)
		{
			printf("Largest number: %f",x);
		}
		else
		{
			printf("Largest number: %f",z);
		}
	}
	else
	{
		if (y > z)
		{
			printf("Largest number: %f",y);
		}
		else
		{
			printf("Largest number: %f",z);
		}
	}
}

/***********************************************************************************/
/********** C Program to Check whether a Number is Positive or Negative ************/
/***********************************************************************************/
void EX4()
{
	float x;
	printf("Enter a number: ");
	fflush(stdout);
	scanf("%f",&x);

	if(x == 0)
	{
		printf("You entered Zero");
	}
	else
	{
		if(x > 0)
		{
			printf("%f is positive",x);
		}
		else
		{
			printf("%f is negative",x);
		}
	}
}

/***********************************************************************************/
/******** C Program to Check whether a Character is an Alphabet or not *************/
/***********************************************************************************/
void EX5()
{
	char x;
	printf("Enter a character: ");
	fflush(stdout);
	scanf("%c",&x);

	if( (x >= 'a' && x<= 'z' ) || (x >= 'A' && x<= 'Z' ) )
	{
		printf("%c is an alphabet",x);
	}
	else
	{
		printf("%c is not an alphabet",x);
	}
}

/***********************************************************************************/
/************* C Program to Calculate Sum of Natural Numbers ***********************/
/***********************************************************************************/
void EX6()
{
	int i , n , sum=0;
	printf("Enter an integer: ");
	fflush(stdout);
	scanf("%d",&n);

	for (i=1 ; i<=n ; i++)
	{
		sum += i ;
	}

	printf("Sum = %d",sum);
}

/***********************************************************************************/
/***************** C Program to Find Factorial of a Number *************************/
/***********************************************************************************/
void EX7()
{
	int fact = 1,i,x;
	printf("Enter an integer: ");
	fflush(stdout);
	scanf("%d",&x);

	if(x<0)
	{
		printf("Error!!! Factorial of negative number doesn't exist");
	}
	else
	{
		for(i=x;i>1;i--)
		{
			fact *=i;
		}
		printf("Factorial = %d",fact);
	}
}

/***********************************************************************************/
/**************** Making Simple Calculator Using Switch...case *********************/
/***********************************************************************************/
void EX8()
{
	char operator;
	float result , num1 , num2;
	printf("Enter operator either + or - or * or divide: ");
	fflush(stdout);
	scanf("%c",&operator);

	printf("Enter two operands: ");
	fflush(stdout);
	scanf("%f %f",&num1,&num2);

	switch(operator)
	{
	case '+': result = num1+num2; break;
	case '-': result = num1-num2; break;
	case '*': result = num1*num2; break;
	case '/': result = num1/num2; break;
	}
	printf("%.1f - %.1f = %.1f",num1,num2,result);
}

int main(void) {

	return 0;
}
