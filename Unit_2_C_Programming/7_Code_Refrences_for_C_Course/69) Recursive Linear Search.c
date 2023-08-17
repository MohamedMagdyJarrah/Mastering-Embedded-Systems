#include <stdio.h>
#include <stdlib.h>

int recursiveLinearSearch(int* arr, int start,int end,int num)
{
	if(start > end)
		return -1;
	if(arr[start] == num)
		return start;
	if(arr[end] == num)
		return end;
	recursiveLinearSearch(arr,start+1,end-1,num);
}


int main(void) {
	int arr[] = {1,2,3,4,5} , arrSize , num , indexOfNum;
	arrSize = sizeof(arr)/sizeof(*arr);
	printf("Enter the number to search: ");
	fflush(stdout);
	scanf("%d",&num);

	indexOfNum = recursiveLinearSearch(arr,0,arrSize-1,num);

	(indexOfNum == -1) ? printf("The number isn't found") : printf("The number %d is found at index %d",num,indexOfNum);

	return 0;
}