#include <stdio.h>
#include <stdlib.h>

void checkArchLittleOrBigEndian()
{
	int num = 1;
	char *ptr = (char*)&num;;
	(*ptr == 1) ? printf("The Archeticture is little endian") : printf("The Archeticture is big endian");
}


int main(void) {
	checkArchLittleOrBigEndian();
	return 0;
}
