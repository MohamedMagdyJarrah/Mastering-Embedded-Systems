#include <stdio.h>
#include <stdlib.h>

void printAllUniqueElements(int* arr, int arrSize)
{
	int* occurence , i , j , count=0;
	occurence = (int*)calloc(arrSize,sizeof(int));
	for(i=0 ; i<arrSize ;i++)
	{
		for(j=0 ; j< arrSize ;j++)
		{
			if(arr[i] == arr[j])
				count++;
		}
		occurence[i] = count;
		count=0;
	}

	for(i=0 ; i<arrSize ;i++)
	{

		if(occurence[i] == 1)
			printf("The unique numbers is %d\n",arr[i]);
	}
}


int main()
{
	int a[]={1,2,3,1,4,3,2},size;
	size=sizeof(a)/sizeof(*a);
	printAllUniqueElements(a,size);
	return 0;
}