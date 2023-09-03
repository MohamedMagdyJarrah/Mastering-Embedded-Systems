/*****************************************************************************/
/*****************************************************************************/
/*****************		Author: Mohamed Magdy				******************/
/*****************		Layer:  APP							******************/
/*****************		SWC:    LinkedList					******************/
/*****************		Version: 1.00 						******************/
/*****************************************************************************/
/*****************************************************************************/
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "Platform_Types.h"
#include "LinkedList.h"

SNode_t* StudentsDataBase = NULL;

int main(void)
{

	DPRINT("_________________________________  \n");
	DPRINT("Choose an Option from list to do:  \n");
	DPRINT("_________________________________  \n");
	DPRINT("1 : Add student                   \n");
	DPRINT("2 : Delete student                \n");
	DPRINT("3 : view students                 \n");
	DPRINT("4 : Delete all                    \n");
	DPRINT("5 : Get Nth of node from the first\n");
	DPRINT("6 : Get Nth of node from the end  \n");
	DPRINT("7 : Find the length               \n");
	DPRINT("8 : Find the middle               \n");
	DPRINT("9 : Detect loop                   \n");
	DPRINT("10: Reverse                       \n");

	while(1)
	{
		DPRINT("_________________________________  \n");
		DPRINT("Enter an option: ");

		char input[40];
		GETS(input);

		switch(atoi(input))
		{
		case 1:	LinkedList_InsertNodeAtEnd(&StudentsDataBase); break;
		case 2:	LinkedList_DeleteNode(&StudentsDataBase); break;
		case 3:	LinkedList_ViewAllNodes(StudentsDataBase); break;
		case 4:	LinkedList_DeleteAllNodes(&StudentsDataBase); break;
		case 5:	LinkedList_GetNthNodeFromFirst(StudentsDataBase); break;
		case 6:	LinkedList_GetNthNodeFromEnd(StudentsDataBase); break;
		case 7:	DPRINT("Linkedlist length is %d\n",LinkedList_GetLength(StudentsDataBase)); break;
		case 8:	LinkedList_FindMiddleNode(StudentsDataBase); break;
		case 9:	LinkedList_DetectLoop(StudentsDataBase); break;
		case 10:LinkedList_ReverseList(&StudentsDataBase); break;
		default: DPRINT("Wrong Option\n"); break;
		}
	}

	return 0;
}



