#include <stdlib.h>
#include <stdio.h>

#define MAXSIZE		50

void SwapTwoDifferentSizeArr(int *arr1 ,int* arr1Size,int *arr2,int* arr2Size)
{
	int i=0 , biggerSize , temp;
	biggerSize = *arr1Size > *arr2Size ? *arr1Size : *arr2Size;

	for(i=0 ; i< biggerSize ; i++)
	{
		temp = arr1[i];
		arr1[i] = arr2[i];
		arr2[i] = temp;
	}

	temp = *arr1Size;
	*arr1Size = *arr2Size;
	*arr2Size = temp;
}


int main(void)
{
	int i;
	int arr1[MAXSIZE] = {1,2,3,4,5} ,size1Arr = 5;
	int arr2[MAXSIZE] = {6,7,8,9} ,size2Arr = 4;

	printf("First Array: ");
	for(i=0 ; i< size1Arr ; i++)
	{
		printf("%d ",arr1[i]);
	}
	printf("\n");
	printf("Second Array: ");
	for(i=0 ; i< size2Arr ; i++)
	{
		printf("%d ",arr2[i]);
	}
	printf("\nSwapping Two Arrays...\n");
	SwapTwoDifferentSizeArr(arr1,&size1Arr,arr2,&size2Arr);

	printf("First Array: ");
	for(i=0 ; i< size1Arr ; i++)
	{
		printf("%d ",arr1[i]);
	}
	printf("\n");
	printf("Second Array: ");
	for(i=0 ; i< size2Arr ; i++)
	{
		printf("%d ",arr2[i]);
	}
	return 0;
}
