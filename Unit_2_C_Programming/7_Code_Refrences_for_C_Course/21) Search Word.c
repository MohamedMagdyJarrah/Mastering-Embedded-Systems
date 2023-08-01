#include <stdlib.h>
#include <stdio.h>
#include "string.h"

void SearchWordInString(char *str , char* word)
{
	int i=0 , found = 0;
	char *temp;
	/* to copy the string to temp without pointing to it as we change in the string and we want the string return as it is at the end */
	
	/*
	char *temp;
	temp = str;		here if we change in temp or str the string will change in both as they are pointers 
	*/
	
	/*
	char *temp = " ";
	strcpy(temp,str);		not valid here ( doesn't work ) 
	*/
	
	temp = (char*)malloc(strlen(str));
	strcpy(temp,str);
	
	for(i=strlen(temp)-1 ; i>=0 ; i--)
	{

		if(i==0)
		{
			if(!strcmp(word,temp))
			{
				found =1;
			}
		}
		else if(temp[i] == ' ')
		{
			temp[i] = '\0';
			if(!strcmp(word,temp+i+1))
			{
				found =1;
				break;
			}
		}
	}
	
	if(found)
		printf("%s appeared in the string\n",word);
	else
		printf("%s not appeared in the string\n",word);
}

int main(void)
{
	char sentence[] = "Mohamed Magdy Ismail Jarrah";
	char *wordToTest1 = "Mohamed" , *wordToTest2 = "Ahmed";
	printf("The word to search is %s in {%s}\n",wordToTest1,sentence);
	SearchWordInString(sentence,wordToTest1);
	printf("The word to search is %s in {%s}\n",wordToTest2,sentence);
	SearchWordInString(sentence,wordToTest2);
	SearchWordInString(sentence,"Ismail");
	return 0;
}
