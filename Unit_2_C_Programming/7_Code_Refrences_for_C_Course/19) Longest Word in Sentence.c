#include <stdlib.h>
#include <stdio.h>

char* FindingLongestWord(char* sentence)
{
	int i=0 , maxCharNum = 0 , numOfChar = 0;
	char* longestWord;

	while(sentence[i] != '\0')
	{
		if(sentence[i] != ' ')
		{
			numOfChar++;
		}
		else
		{
			if(numOfChar > maxCharNum)
			{
				maxCharNum = numOfChar;
				longestWord = sentence+i-maxCharNum;
			}
			numOfChar=0;
		}
		i++;
	}

	longestWord[maxCharNum] = '\0';

	return longestWord;
}


int main(void)
{
	char sentence[] = "my name is mohamed ali" , *longestWord;
	longestWord = FindingLongestWord(sentence);
	printf("The longest word is %s",longestWord);
	return 0;
}
