#include <stdio.h>
#include <stdlib.h>
#include "string.h"

/***************************************************************************************************************************/
/*********************A program in C to demonstrate how to handle the pointers in the program*******************************/
/***************************************************************************************************************************/
void EX1()
{
	int m = 29, *ab;
	printf("Address of m: 0x%x\nValue of m: %d\n",&m,m);
	ab = &m;
	printf("\nNow ab is assigned with the address of m.\n");
	printf("Address of the pointer ab: 0x%x\nContent of the pointer ab: %d\n",ab,*ab);
	m = 34;
	printf("\nThe Value of m assigned to 34 now.\n");
	printf("Address of the pointer ab: 0x%x\nContent of the pointer ab: %d\n",ab,*ab);
	*ab = 7;
	printf("\nThe pointer variable ab is assigned with the value 7 now.\n");
	printf("Address of m: 0x%x\nValue of m: %d\n",&m,m);
}

/***************************************************************************************************************************/
/***************************** A program in C to print all the alphabets using a pointer ***********************************/
/***************************************************************************************************************************/
void EX2()
{
	int i=0;
	char *alphabets = "A";
	printf("The Alphabets are :");
	for(i=0;i<26;i++)
	{
		printf("%c ",(*alphabets)+i);
	}
}

/***************************************************************************************************************************/
/**************************** A program in C to print a string in reverse using a pointer **********************************/
/***************************************************************************************************************************/
void EX3()
{
	char inputString[100] , *ptrString , revString[100];
	int i;
	gets(inputString);
	fflush(stdout);
	printf("The Alphabets are : %s\n",inputString);
	ptrString = inputString;
	/* pointing on the last char in string */
	ptrString = ptrString+(strlen(inputString)-1);
	/* save with reversed way the string using the pointer*/
	for(i = 0 ; i < strlen(inputString); i++)
	{
		revString[i] = *ptrString;
		ptrString--;
	}
	revString[i] = '\0';
	printf("Reverse of the string is : %s",revString);
}

/***************************************************************************************************************************/
/************************* A program in C to print the elements of an array in reverse order *******************************/
/***************************************************************************************************************************/
void EX4()
{
	int i, elements , arr[15] , *ptr;
	printf("Input the number of elements to store in the array (max 15) :");
	fflush(stdout);
	scanf("%d",&elements);
	printf("Input %d number of elements in the array :\n",elements);

	/* Storing elements */
	for(i=0 ; i<elements ; i++)
	{
		printf("element - %d: ",i+1);
		fflush(stdout);
		scanf("%d",&arr[i]);
	}

	/* Pointing on the last element*/
	ptr = arr;
	ptr = ptr + (elements-1);

	/* Reversing and move one step back with pointer */
	for(i=0 ; i< elements/2 ; i++)
	{
		arr[i] = arr[i] + *ptr ;
		*ptr = arr[i] - *ptr ;
		arr[i] = arr[i] - *ptr ;
		ptr--;
	}

	/* Printing elements */
	printf("The elements of array in reverse order are :\n");
	for(i=0 ; i<elements ; i++)
	{
		printf("element - %d: %d\n",i+1,arr[i]);
	}

}

/***************************************************************************************************************************/
/**************** A program in C to show a pointer to an array which contents are pointer to structure *********************/
/***************************************************************************************************************************/
struct Employee{
	char *name;
	int id;
};
void EX5()
{
	struct Employee employees[3] = {{"Mohamed",18011588},{"Yasser",18011743},{"Khaled",18011724}};
	struct Employee *ArrayOfPointersToStruct[3] = {&employees[0],&employees[1],&employees[2]};
	struct Employee *(*ptrToArrayOfPointerToStruct)[3] = &ArrayOfPointersToStruct;

	printf("First Employee name : %s\n",(*(*(*ptrToArrayOfPointerToStruct))).name);
	printf("First Employee id : %d\n",(*(*(*ptrToArrayOfPointerToStruct))).id);

	printf("Second Employee name : %s\n",(*(*(*ptrToArrayOfPointerToStruct)+1)).name);
	printf("Second Employee id : %d\n",(*(*(*ptrToArrayOfPointerToStruct)+1)).id);


	printf("Third Employee name : %s\n",(*(*(*ptrToArrayOfPointerToStruct)+2)).name);
	printf("Third Employee id : %d\n",(*(*(*ptrToArrayOfPointerToStruct)+2)).id);
}


int main(void) {

	return 0;
}
