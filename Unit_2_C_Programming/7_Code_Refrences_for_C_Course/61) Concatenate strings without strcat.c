#include <stdlib.h>
#include <stdio.h>

void concatenateStrings(char* to,char* from)
{
	while(*to != '\0')
	{
		to++;
	}

	while(*from != '\0')
	{
		*to = *from;
		from++;
		to++;
	}
	*to = '\0';
}

int main()
{
	char str[50] = "Mohamed",strToConcat[60] = " Magdy";
	printf("The string we want to copy is %s\n",str);
	concatenateStrings(str,strToConcat);
	printf("The string copied is %s\n",str);
	return 0;
}