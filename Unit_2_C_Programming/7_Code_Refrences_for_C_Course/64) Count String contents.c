#include <stdlib.h>
#include <stdio.h>

void count_Alphabets_Digits_SpecialChar(char* str,int* alphabets,int* digits,int* specialChar)
{
	*alphabets = 0;
	*digits = 0;
	*specialChar = 0;
	while(*str != '\0')
	{
		if( (*str >= 'a' && *str <= 'z') || (*str >= 'a' && *str <= 'z') )
			(*alphabets)++;
		else if(*str >= '0' && *str <= '9')
			(*digits)++;
		else
			(*specialChar)++;

		str++;
	}
}

int main()
{
	char str[50] = "mohamedmagdy2023@gmail.com";
	int alphabets,digits,specialChar;
	count_Alphabets_Digits_SpecialChar(str,&alphabets,&digits,&specialChar);
	printf("{%s} has %d alphabets , %d digits , %d special characters",str,alphabets,digits,specialChar);
	return 0;
}