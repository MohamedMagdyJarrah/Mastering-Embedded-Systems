#include <stdio.h>
#include <stdlib.h>


/****************************************************************************/
/**************** C Program to find the sum of two matrices *****************/
/****************************************************************************/
void EX1(void)
{
	float mat1[2][2] , mat2[2][2];
	int i=0 , j=0;
	printf("Enter the element of the 1st matrix :\n");
	for(i=0 ; i<2 ; i++)
	{
		for(j=0 ; j<2 ; j++)
		{
			printf("Enter a%d%d:",i+1,j+1);
			fflush(stdout);
			scanf("%f",&mat1[i][j]);
		}
	}
	printf("Enter the element of the 2nd matrix :\n");
	for(i=0 ; i<2 ; i++)
	{
		for(j=0 ; j<2 ; j++)
		{
			printf("Enter b%d%d:",i+1,j+1);
			fflush(stdout);
			scanf("%f",&mat2[i][j]);
		}
	}

	printf("Sum of Matrix:\n");
	for(i=0 ; i<2 ; i++)
	{
		for(j=0 ; j<2 ; j++)
		{
			printf("%.1f ",mat1[i][j]+mat2[i][j]);
		}
		printf("\n");
	}
}

/*******************************************************************************/
/**************** C Program to Calculate Average Using Arrays *****************/
/******************************************************************************/
void EX2(void)
{
	int i , numberOfData;
	printf("Enter the numbers of data: ");
	fflush(stdout);
	scanf("%d",&numberOfData);

	float array[numberOfData] , sum;
	for(i=0 ; i< numberOfData ; i++)
	{
		printf("%d. Enter number: ",i+1);
		fflush(stdout);
		scanf("%f",&array[i]);

		sum += array[i];
	}

	printf("Average= %.2f",sum/numberOfData);

}

/*******************************************************************************/
/******************* C Program to Find Transpose of a Matrix *******************/
/*******************************************************************************/
void EX3(void)
{
	int rows , columns , i , j;
	printf("Enter number of rows: ");
	fflush(stdout);
	scanf("%d",&rows);
	printf("Enter number of columns: ");
	fflush(stdout);
	scanf("%d",&columns);

	int matrix[rows][columns] , transMatrix[columns][rows];

	printf("Enter elements of matrix :\n");
	for(i=0 ; i<rows ; i++)
	{
		for(j=0 ; j<columns ; j++)
		{
			printf("Enter a%d%d:",i+1,j+1);
			fflush(stdout);
			scanf("%d",&matrix[i][j]);
			transMatrix[j][i] = matrix[i][j];
		}
	}

	printf("Transpose of the Matrix:\n");
	for(i=0 ; i<columns ; i++)
	{
		for(j=0 ; j<rows ; j++)
		{
			printf("%d ",transMatrix[i][j]);
		}
		printf("\n");
	}
}

/**********************************************************************************/
/******************* C Program to insert an element in an Array *******************/
/**********************************************************************************/
void EX4(void)
{
	int numOfElements , array[40] , i , location , element;
	printf("Enter no of elements: ");
	fflush(stdout);
	scanf("%d",&numOfElements);

	printf("Enter the array:\n");
	fflush(stdout);
	for(i=0 ; i<numOfElements ; i++)
	{
		scanf("%d",&array[i]);
	}

	printf("Enter the element to be inserted: ");
	fflush(stdout);
	scanf("%d",&element);

	printf("Enter the location: ");
	fflush(stdout);
	scanf("%d",&location);

	for(i = numOfElements-1 ; i>=location-1 ; i--)
	{
		array[i+1] = array[i];
	}
	array[location-1] = element;

	printf("Enter the array after inserting element %d at location %d\n",element,location);
	for(i=0 ; i < numOfElements+1 ; i++)
	{
		printf("%d ",array[i]);
	}
}

/**********************************************************************************/
/******************* C Program to search an element in an Array *******************/
/**********************************************************************************/
void EX5(void)
{
	int numOfElements , i , element;
	printf("Enter no of elements: ");
	fflush(stdout);
	scanf("%d",&numOfElements);

	int array[numOfElements];
	printf("Enter the array:\n");
	fflush(stdout);
	for(i=0 ; i<numOfElements ; i++)
	{
		scanf("%d",&array[i]);
	}

	printf("Enter the element to be searched: ");
	fflush(stdout);
	scanf("%d",&element);

	for(i=0 ; i<numOfElements ; i++)
	{
		if(array[i] == element)
		{
			printf("Number found at the location = %d",i+1);
			break;
		}
	}

	if(i == numOfElements)
	{
		printf("Number not found");
	}
}

int main(void) {

	return 0;
}
