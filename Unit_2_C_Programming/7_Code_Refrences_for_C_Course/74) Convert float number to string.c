#include <stdio.h>
#include <stdlib.h>

char* convertFloatNumToString(float num)
{
	static char str[50];
	sprintf(str,"%f",num);
	return str;
}

int main()
{
	printf("The string for the num is %s", convertFloatNumToString(5.654));
	return 0;
}