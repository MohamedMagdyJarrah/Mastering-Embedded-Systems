#include <stdio.h>
#include <stdlib.h>
#include "string.h"

/*************************************************************************************/
/*********** C Program to Find the Frequency of Characters in a String ***************/
/*************************************************************************************/
void EX1(void)
{
	char string[100] , character;
	int i=0 , freq=0;
	printf("Enter a string: ");
	fflush(stdout);
	gets(string);

	printf("Enter a character to find frequency: ");
	fflush(stdout);
	scanf("%c",&character);

	while(string[i] != '\0')
	{
		if(string[i] == character)
		{
			freq++;
		}
		i++;
	}

	printf("Frequency of %c = %d",character,freq);
}

/********************************************************************/
/*************** C Program to Find Length of a String ***************/
/********************************************************************/
void EX2(void)
{
	char string[100];
	int length = 0;
	printf("Enter a string: ");
	fflush(stdout);
	gets(string);

	while(string[length] != '\0')
	{
		length++;
	}

	printf("Length of string: %d",length);
}

/******************************************************************************************/
/*************** C Program to Reverse String Without Using Library Function ***************/
/******************************************************************************************/
void EX3(void)
{
	char string[100] , temp;
	int i=0 , length;
	printf("Enter a string: ");
	fflush(stdout);
	gets(string);

	length = strlen(string)-1;

	for(i=0 ; i<length ; i++)
	{
		temp = string[i];
		string[i] = string[length];
		string[length] = temp;
		length--;
	}

	printf("Reversed string is: %s",string);
}

int main(void) {

	return 0;
}
