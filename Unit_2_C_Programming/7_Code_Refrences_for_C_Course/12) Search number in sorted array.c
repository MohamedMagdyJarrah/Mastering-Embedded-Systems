#include stdlib.h
#include stdio.h

#define NOTFOUND	-1

int FindNumInSortedArr(int *arr , int arrSize , int numToSearch)
{
	char NumIndexFound = -1;
	int i = 0;
	for(i=0 ; i < arrSize ; i++)
	{
		if(arr[i] == numToSearch)
		{
			NumIndexFound = i;
			break;
		}
	}
	return NumIndexFound;
}


int main(void)
{
	int number , array[5] = {1,2,3,4,5} , indexOfNum;
	printf("Enter number to search: ");
	fflush(stdout);
	scanf("%d",&number);
	indexOfNum = FindNumInSortedArr(array,5,number);
	indexOfNum == NOTFOUND ? printf("%d not found in the array",number) :printf("%d found at index %d\n",number,indexOfNum);
	return 0;
}
