#include <stdlib.h>
#include <stdio.h>

typedef struct Info{
	int min;
	int max;
	int indexMin;
	int indexMax;
}Info;

void MinMaxArray(int* arr , int arrSize , Info* Result)
{
	int i=0;
	Result->min = arr[0];
	Result->max = arr[0];
	for(i = 0 ; i< arrSize ; i++)
	{
		if(arr[i] >= Result->max)
		{
			Result->max = arr[i];
			Result->indexMax = i;
		}
		else if(arr[i] <= Result->min)
		{
			Result->min = arr[i];
			Result->indexMin = i;
		}
	}
}


int main(void)
{
	int array[5] = {8,2,3,1,0} , sizeOfArr , i=0;
	Info Answer;

	sizeOfArr = sizeof(array)/sizeof(array[0]);
	printf("The Array is ");
	for(i=0; i < sizeOfArr ; i++)
	{
		printf("%d ",array[i]);
	}
	printf("\n");

	MinMaxArray(array,sizeOfArr,&Answer);
	printf("Maximum number is %d at index %d\n",Answer.max,Answer.indexMax);
	printf("Minimum number is %d at index %d\n",Answer.min,Answer.indexMin);

	return 0;
}
