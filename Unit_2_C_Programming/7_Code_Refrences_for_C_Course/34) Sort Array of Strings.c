#include <stdlib.h>
#include <stdio.h>
#include "string.h"

void sortArrayOfString(char arrOfStr[][MAX_LEN] , int arrSize)
{
	int i=0 , j=0;
	int minStrIndex;
	for(i=0 ; i<arrSize-1 ; i++)
	{
		minStrIndex = i;
		for(j=i+1 ; j<arrSize ; j++)
		{
			if(arrOfStr[i][0] > arrOfStr[j][0])
			{
				minStrIndex = j;	/* save the index of the minimum string */
			}
		}
		if(minStrIndex != i)		/* Swap if the minimum index changed from the first element*/
		{
			char temp[MAX_LEN];
			strcpy(temp,arrOfStr[i]);
			strcpy(arrOfStr[i],arrOfStr[minStrIndex]);
			strcpy(arrOfStr[minStrIndex],temp);
		}
	}
}


int main()
{
    char arr[][MAX_LEN] = {"wkue", "qoi","sbv","fekls"};
    int n = sizeof(arr)/sizeof(arr[0]);
    int i;

    printf("Given array is\n");
    for (i = 0; i < n; i++)
        printf("%d: %s \n", i, arr[i]);

    sortArrayOfString(arr, n);

    printf("\nSorted array is\n");
    for (i = 0; i < n; i++)
        printf("%d: %s \n", i, arr[i]);

    return 0;

}
