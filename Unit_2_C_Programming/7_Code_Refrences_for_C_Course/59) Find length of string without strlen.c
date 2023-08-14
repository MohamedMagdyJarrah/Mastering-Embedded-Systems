#include <stdlib.h>
#include <stdio.h>

int lengthOfString(char* str)
{
	int length=0;
	while(*str != '\0')
	{
		length++;
		str++;
	}
	return length;
}


int main()
{
	char str[] = "Mohamed";
	printf("The length of string {%s} is %d",str,lengthOfString(str));
	return 0;
}