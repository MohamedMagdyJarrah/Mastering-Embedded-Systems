#include <stdlib.h>
#include <stdio.h>
#include "string.h"

void reverseString(char *str , int strLength)
{
	char *temp;
	temp = (char*)malloc(strLength);
	int i=0;
	for(i=0 ; i<strLength ; i++)
	{
		temp[i] = str[strLength-i-1];
	}
	temp[i] = '\0';
	strcpy(str,temp);
	
	/* Better idea */
//	int i;
//	for(i=0 ; i<strLength/2; i++)
//	{
//		str[i] ^= str[strLength-i-1];
//		str[strLength-i-1] ^= str[i];
//		str[i] ^= str[strLength-i-1];
//	}
}

int main(void)
{
	char str[] = "mohamed";
	printf("Before Reversing : %s\n",str);
	reverseString(str,strlen(str));
	printf("String after reversing is %s",str);
	return 0;
}
