#include <stdlib.h>
#include <stdio.h>
#include "string.h"

void sortWordsInString(char *str , int strSize)
{
	int i,numOfWords=0,j;
	char word[50][MAX_LEN];
	/* Taking words individually from the back */
	for(i = strSize-1 ; i>=0 ; i--)
	{
		if(str[i] == ' ')
		{
			strcpy(word[numOfWords],str+i+1);
			str[i] = '\0';
			numOfWords++;
		}
		else if(i==0)
		{
			strcpy(word[numOfWords],str+i);
			numOfWords++;
		}
	}
	str[0] = '\0';

	for(i=0 ; i<numOfWords ;i++)
	{

		for(j = i+1;j<numOfWords ;j++)
		{
			if(word[i][0] > word[j][0])
			{
				char temp[MAX_LEN];
				strcpy(temp,word[j]);
				strcpy(word[j],word[i]);
				strcpy(word[i],temp);
			}
		}
		if(i==0)
			strcpy(str,word[i]);
		else
		{
			strcat(str,",");
			strcat(str,word[i]);
		}
	}


}

int main()
{
	char str[]= "mohamed bahaa zahra xeon ahmed jaida wessam lara hana";
	int n = sizeof(str)/sizeof(str[0]);

	printf("String before Sorting is {%s}\n",str);

	sortWordsInString(str,n);

	printf("String after being sorted: {%s}",str);

	return 0;

}