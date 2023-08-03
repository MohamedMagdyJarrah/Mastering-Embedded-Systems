#include <stdlib.h>
#include <stdio.h>
#include "string.h"

int FindMostRepeatedChar(char *str,int strSize,char *character)
{
	int maxAppearence=0 , i=0 , j=0 , charCount =0;
	char temp;

	for(i=0 ; i< strlen(str)-1 ; i++)
	{
		temp = str[i];
		for(j=i ; j< strlen(str) ; j++)
		{
			if( temp == ' ' )
			{
				break;
			}
			else
			{
				if(temp == str[j])
				{
					charCount++;
				}

			}
		}

		if(charCount > maxAppearence)
		{
			maxAppearence = charCount;
			*character = temp;
		}
		charCount = 0;
	}
	
	return maxAppearence;
}


int main(void)
{
	char string[] = "aaaaa jjjj asasdaaaa aa" , repeatedChar;
	int stringSize = strlen(string) , maxAppear;
	maxAppear = FindMostRepeatedChar(string,stringSize,&repeatedChar);
	printf("The most repetead char in {%s} is '%c' which exists %d times",string,repeatedChar,maxAppear);
	return 0;
}
