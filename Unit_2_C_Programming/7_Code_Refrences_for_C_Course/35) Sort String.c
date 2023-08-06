#include <stdlib.h>
#include <stdio.h>
#include "string.h"

void sortString(char *str,int strSize)
{
	int i,j;
	for(i=0 ; i<strSize-1 ; i++)
	{
		for(j = i+1 ; j<strSize ; j++)
		{
			if(str[i] > str[j])
			{
				str[i] ^= str[j];
				str[j] ^= str[i];
				str[i] ^= str[j];
			}
		}
	}
}

int main()
{
	char str[]="geeksforgeeks";
	int size=strlen(str);
	sortString(str,size);
	printf("%s",str);
    return 0;

}
