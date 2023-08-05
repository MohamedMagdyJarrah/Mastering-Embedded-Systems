#include <stdlib.h>
#include <stdio.h>

void swap(int *a , int *b)
{
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}
int ascending(int a ,int b)
{
	return a>b ? 1:0;
}
void SortArrayUsingFunctionPointer(int *arr , int arrSize ,int (*compare)(int , int))
{
	int i=0 , j=0;
	for(i=0 ; i<arrSize-1 ; i++)
	{
		for(j=i+1 ; j<arrSize ; j++)
		{
			if( compare(arr[i],arr[j]) )
			{
				swap(&arr[i],&arr[j]);
			}
		}
	}
}

int main(void)
{
	int a[]={5,4,7,1,9,15,0},size,i;
	size=sizeof(a)/sizeof(*a);
	SortArrayUsingFunctionPointer(a,size,ascending);
	for(i=0; i<size; i++)
		printf("%d ",a[i]);
	return 0;
}
