#include <stdio.h>
#include <stdlib.h>

char* convertNumToString(int num)
{
	static char str[10];
	sprintf(str,"%d",num);
	return str;
}

int main()
{
	printf("The string for the num is %s", convertNumToString(550));
	return 0;
}