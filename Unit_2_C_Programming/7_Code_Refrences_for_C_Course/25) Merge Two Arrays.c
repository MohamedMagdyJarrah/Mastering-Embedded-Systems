#include <stdlib.h>
#include <stdio.h>

int* MergeTwoArrays(int *arr1,int arr1Size,int *arr2,int arr2Size,int *FinalSize)
{
	int index1 = 0 , index2 = 0 , i=0;
	static int *FinalArr;
	*FinalSize = arr1Size+arr2Size;
	FinalArr = (int*)malloc(*FinalSize * sizeof(int));

	for (i=0 ; i< *FinalSize ; i++)
	{
		if(index1 != arr1Size && index2 != arr2Size)
		{
			if(i%2 == 0)
			{
				FinalArr[i] = arr1[index1];
				index1++;
			}
			else
			{
				FinalArr[i] = arr2[index2];
				index2++;
			}
		}
		else if(index1 != arr1Size && index2 == arr2Size)
		{
			FinalArr[i] = arr1[index1];
			index1++;
		}
		else if(index1 == arr1Size && index2 != arr2Size)
		{
			FinalArr[i] = arr2[index2];
			index2++;
		}

	}
	return FinalArr;
}



int main(void)
{
	int arr1[]={1,2,3,4,5,6},arr2[]={11,12,13,14,15,16},size1,size2,size3,*p,i;
	size1=sizeof(arr1)/sizeof(*arr1);
	size2=sizeof(arr2)/sizeof(*arr2);

	p=MergeTwoArrays(arr1,size1,arr2,size2,&size3);

	for(i=0; i<size3; i++)
		printf("%d ",p[i]);
	return 0;
}
