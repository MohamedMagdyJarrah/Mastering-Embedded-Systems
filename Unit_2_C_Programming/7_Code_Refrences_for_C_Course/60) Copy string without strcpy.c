#include <stdlib.h>
#include <stdio.h>

void copyString(char* to, char* from)
{
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
	char str[50] = "Mohamed",strToPaste[60];
	printf("The string we want to copy is %s\n",str);
	copyString(strToPaste,str);
	printf("The string copied is %s\n",strToPaste);
	return 0;
}