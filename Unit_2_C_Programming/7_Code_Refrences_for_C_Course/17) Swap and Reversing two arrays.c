#include <stdlib.h>
#include <stdio.h>

#define MAXSIZE		50

void ReverseArray(int *arr,int arrSize)
{
	int i=0 , temp;
	for(i=0 ; i< arrSize/2 ; i++)
	{
		temp = arr[i];
		arr[i] = arr[arrSize - i -1];
		arr[arrSize - i -1] = temp;
	}
}

void SwapAndReverseTwoArrays(int *a , int *b , int size)
{
	int i=0 , temp;
	ReverseArray(a,size);
	ReverseArray(b,size);

	for(i=0 ; i< size ; i++)
	{
		temp = a[i];
		a[i] = b[i];
		b[i] = temp;
	}
}

int main(void)
{
	int i , sizeArr = 5;
	int arr1[MAXSIZE] = {1,2,3,4,5};
	int arr2[MAXSIZE] = {6,7,8,9,10};

	printf("First Array: ");
	for(i=0 ; i< sizeArr ; i++)
	{
		printf("%d ",arr1[i]);
	}
	printf("\n");
	printf("Second Array: ");
	for(i=0 ; i< sizeArr ; i++)
	{
		printf("%d ",arr2[i]);
	}
	printf("\nSwapping and Reversing the Two Arrays...\n");
	SwapAndReverseTwoArrays(arr1,arr2,sizeArr);

	printf("First Array: ");
	for(i=0 ; i< sizeArr ; i++)
	{
		printf("%d ",arr1[i]);
	}
	printf("\n");
	printf("Second Array: ");
	for(i=0 ; i< sizeArr ; i++)
	{
		printf("%d ",arr2[i]);
	}
	return 0;
}
