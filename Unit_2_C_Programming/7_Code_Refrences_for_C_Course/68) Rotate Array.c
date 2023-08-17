#include <stdio.h>
#include <stdlib.h>


void rotateArray(int* arr , int size , int D)
{
	int i , *newArr , newIndex=0;
	newArr = (int*)malloc(size*sizeof(int));

	for(i=0 ; i<size ; i++)
	{
		newIndex = (i+size-D)%size;
		newArr[newIndex] = arr[i];
	}


	for(i=0 ; i<size ; i++)
	{
		arr[i] = newArr[i];
	}
}

int main(void) {
	int arr[] = {1,2,3,4,5} , arrSize , i , D;
	arrSize = sizeof(arr)/sizeof(*arr);
	printf("Enter the number of rotations: ");
	fflush(stdout);
	scanf("%d",&D);

	printf("Array before Rotating: ");
	for(i=0;i<arrSize;i++)
		printf("%d ",arr[i]);

	printf("\n");

	rotateArray(arr,arrSize,D);

	printf("Array after Rotating: ");
	for(i=0;i<arrSize;i++)
		printf("%d ",arr[i]);


	return 0;
}