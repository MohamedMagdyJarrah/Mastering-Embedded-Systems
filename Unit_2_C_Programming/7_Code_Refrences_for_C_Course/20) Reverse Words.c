#include <stdlib.h>
#include <stdio.h>
#include "string.h"

void ReverseWords(char* words)
{
	char reversedWords[100];
	int i=0;
	for(i = strlen(words)-1; i >= 0 ; i--)
	{
		if(words[i] == ' ')
		{
			strcat(reversedWords,words+i+1);
			strcat(reversedWords," ");
			words[i] = '\0';
		}
		else if(i==0)
		{
			strcat(reversedWords,words);
		}
	}

	strcpy(words,reversedWords);
}

int main(void)
{
	char sentence[] = "Mohamed Magdy Ismail Jarrah";
	printf("The string is %s\n",sentence);
	ReverseWords(sentence);
	printf("The Reversed string is %s",sentence);
	return 0;
}
