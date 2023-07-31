#include <stdlib.h>
#include <stdio.h>

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

int main(void)
{
	int arr[5] = {1,2,3,4,5} , i ,sizeArr;
	sizeArr = sizeof(arr)/sizeof(arr[0]);
	printf("The Original Array: ");
	for(i=0 ; i<sizeArr ; i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");

	ReverseArray(arr,sizeArr);

	printf("The Reversed Array: ");
	for(i=0 ; i<sizeArr ; i++)
	{
		printf("%d ",arr[i]);
	}
	return 0;
}