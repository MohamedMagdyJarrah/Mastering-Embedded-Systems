#include <stdlib.h>
#include <stdio.h>

void checkAlphabetOrNot(char letter)
{
	(letter>='a' && letter <='z') || (letter>='A' && letter <='Z') ? printf("%c is alphabet",letter) : printf("%c isn't alphabet",letter);
}


int main()
{
	char letter;
	printf("enter char:");
	fflush(stdout);
	scanf("%c",&letter);
	checkAlphabetOrNot(letter);
	return 0;
}