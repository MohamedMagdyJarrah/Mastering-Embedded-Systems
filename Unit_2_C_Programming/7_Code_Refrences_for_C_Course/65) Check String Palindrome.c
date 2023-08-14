#include <stdlib.h>
#include <stdio.h>

void checkStringPalindromeOrNot(char *str)
{
	char *reversedStr;
	reversedStr = (char*)malloc(strlen(str));
	int i;

	for(i=strlen(str)-1; i>=0 ; i--)
	{
		reversedStr[strlen(str)-i-1] = str[i];
	}

	if(!(strcmp(str,reversedStr)))
		printf("The String %s is palindrome\n",str);
	else
		printf("The String %s isn't palindrome\n",str);
}


int main()
{
	char str[50] = "racecar";
	checkStringPalindromeOrNot(str);
	return 0;
}
