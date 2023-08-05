#include <stdlib.h>
#include <stdio.h>

void DeleteRepeatedElements(int *arr , int arrSize)
{
	int i=0 , j=0 , finalSize=0;
	int *distinctNumbers;
	distinctNumbers = (int*)malloc(arrSize*sizeof(int));

	for(i=0 ; i<arrSize ; i++)
	{
		for(j=0 ; j < finalSize ;j++)
		{
			if(arr[i] == distinctNumbers[j])
			{
				break;
			}
		}
		if(j == finalSize)		/* for loop counted until the end of the array */
		{
			distinctNumbers[finalSize] = arr[i];
			finalSize++;
		}
	}

	
	for(i=0 ; i<finalSize ; i++)
	{
		printf("%d ",distinctNumbers[i]);
	}
}


int main(void)
{
	int a[]={4,7,5,7,8,4,9},size;
	size=sizeof(a)/sizeof(*a);
	DeleteRepeatedElements(a,size);
	return 0;
}
