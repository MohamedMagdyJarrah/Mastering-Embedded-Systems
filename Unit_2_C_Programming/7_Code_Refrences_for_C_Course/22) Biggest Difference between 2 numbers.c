#include <stdlib.h>
#include <stdio.h>

int biggestDifference(int *arr ,int arrSize)
{
	int smallest = arr[0] , biggest = arr[0] , i=0 , smallestIndex;
	for(i=0 ; i<arrSize ;i++)
	{
		if(arr[i] <= smallest)
		{
			smallest = arr[i];
			smallestIndex = i;
		}
	}
	biggest = arr[smallest]; /* To let us find number bigger than the small found number */
	for(i=smallestIndex+1 ; i<arrSize ;i++)
	{
		if(arr[i] > biggest)
		{
			biggest = arr[i];
		}
	}

	return biggest - smallest;
}

int main(void)
{
	int  arr[] = {10,1,5,3,6,8,7,2} , arrSize , i=0;
	arrSize = sizeof(arr)/sizeof(arr[0]);
	printf("The biggest difference in arr ");
	for(i=0 ; i<arrSize ; i++)
	{
		printf("%d ",arr[i]);
	}
	printf("is %d",biggestDifference(arr,arrSize));

	return 0;
}
