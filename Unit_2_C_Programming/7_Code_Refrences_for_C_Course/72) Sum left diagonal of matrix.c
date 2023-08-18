#include <stdio.h>
#include <stdlib.h>

#define N 4

int sumOfLeftDiagonalMatrix(int mat[][N])
{
	int sum=0 , row , column;
	for(row = N-1 ; row>=0 ; row--)
	{
		for(column=0 ; column<N ; column++)
		{
			if(row+column == (N-1))
				sum += mat[row][column];
		}
	}
	return sum;
}

int main()
{
	int a[][N]={{1,2,3,5},{8,4,4,5}, {10,4,9,0},{5,6,7,9} };
	int ret=sumOfLeftDiagonalMatrix(a);
	printf("sum is %d",ret);
	return 0;
}