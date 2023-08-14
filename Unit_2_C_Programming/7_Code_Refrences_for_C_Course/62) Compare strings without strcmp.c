#include <stdlib.h>
#include <stdio.h>

int compareTwoStings(char* str1,char* str2)
{
	int stringsAreTheSame = 0;
	while( (*str1 != '\0') && (str2 != '\0') )
	{
		if(*str1 != *str2)
		{
			stringsAreTheSame = 1;
			break;
		}
		str1++;
		str2++;
	}
	return stringsAreTheSame;
}

int main()
{
	char str[50] = "Mohamed",strToCompare[60] = "Mohamed";
	compareTwoStings(str,strToCompare) == 0 ? printf("Two strings are the same") : printf("Two strings aren't the same");
	return 0;
}