#include <stdlib.h>
#include <stdio.h>

void swap(int *a , int *b)
{
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

int main()
{
	int x=5,y=10;
	swap(&x,&y);
	printf("x = %d , y = %d  after swapping",x,y);
	return 0;
}