#include <stdlib.h>
#include <stdio.h>

void Swap2Zeroes(int* arr)
{
	int i=0 ,temp, firstZeroIndex = -1, SecondZeroIndex = -1;
	while(SecondZeroIndex == -1)
	{
		if(arr[i] == 0 && firstZeroIndex == -1)
		{
			firstZeroIndex = i;
		}
		else if(arr[i] == 0 && SecondZeroIndex == -1)
		{
			SecondZeroIndex = i;
		}
		i++;
	}

	for(i=1 ; i <= 3 ;i++)
	{
		temp = arr[firstZeroIndex+i];
		arr[firstZeroIndex+i] = arr[SecondZeroIndex+i];
		arr[SecondZeroIndex+i] = temp;
	}

}

int main(void)
{
	int i , size;
	int a[]={1,2,5,0,3,4,5,6,10,0,30,40,50,60,80,100};
	size = sizeof(a)/sizeof(a[0]);

	printf("Before Swapping : ");
	for(i=0 ; i<size ; i++)
	{
		printf("%d ",a[i]);
	}
	printf("\nAfter Swapping :");

	Swap2Zeroes(a);

	for(i=0 ; i<size ; i++)
	{
		printf("%d ",a[i]);
	}
	return 0;
}