/*****************************************************************************/
/*****************************************************************************/
/*****************		Author: Mohamed Magdy				******************/
/*****************		Layer:  APP							******************/
/*****************		SWC:    LinkedList					******************/
/*****************		Version: 1.00 						******************/
/*****************************************************************************/
/*****************************************************************************/


/*****************************************************************************/
/*********** This Driver is written for specific application *****************/
/***********		   which is Student data base  			 *****************/
/*****************************************************************************/

#include "stdio.h"
#include "stdlib.h"
#include "Platform_Types.h"
#include "LinkedList.h"


LinkedList_State LinkedList_InsertNodeAtBeginning(SNode_t** listHead)
{
	LinkedList_State returnState = LinkedList_No_Error;
	/* Storage to save the input of the user */
	char temptext[40];
	/* Temporary node used to traverse in the linkedlist */
	SNode_t* TempNode = NULL;
	TempNode = (SNode_t*)malloc(sizeof(SNode_t));		/* It will return NULL if heap is full */
	/* If there is place in heap to allocate */
	if(NULL != TempNode)
	{
		/* Storing the data of the student */
		DPRINT("Enter the ID: ");
		GETS(temptext);
		TempNode->data.ID = atoi(temptext);

		DPRINT("Enter your name: ");
		gets(TempNode->data.name);

		DPRINT("Enter your height: ");
		GETS(temptext);
		TempNode->data.height = atof(temptext);
		/* Check if the list is empty */
		if(NULL == *listHead)
		{
			*listHead = TempNode;				/* Make the linkedlist head points to the only node added */
			(*listHead)->nextNode = NULL;		/* Make the next node if the first node points to NULL */
		}
		/* The linkedlist has nodes */
		else
		{
			TempNode->nextNode = *listHead;		/* Make the next of the new node points to the first node in the list */
			*listHead = TempNode;				/* Make the head of the linkedlist to be the new node in the front */
		}
	}
	/* If there isn't place in heap to allocate */
	else
	{
		returnState = Linkedlist_Heap_Full;
	}


	return returnState;
}

LinkedList_State LinkedList_InsertNodeAtEnd(SNode_t** listHead)
{
	LinkedList_State returnState = LinkedList_No_Error;
	/* Temporary nodes used to traverse in the linkedlist */
	SNode_t* TempNode = NULL;
	SNode_t* LastNode = NULL;
	TempNode = (SNode_t*)malloc(sizeof(SNode_t));		/* It will return NULL if heap is full */
	/* Storage to save the input of the user */
	char temptext[40];
	/* If there is place in heap to allocate */
	if(NULL != TempNode)
	{
		/* Storing the data of the student */
		DPRINT("Enter the ID: ");
		GETS(temptext);
		TempNode->data.ID = atoi(temptext);

		DPRINT("Enter your name: ");
		gets(TempNode->data.name);

		DPRINT("Enter your height: ");
		GETS(temptext);
		TempNode->data.height = atof(temptext);
		/* Check if the list is empty */
		if(NULL == *listHead)
		{
			/* Make the linkedlist head points to the only node added */
			*listHead = TempNode;
		}
		/* The linkedlist has nodes */
		else
		{
			/* Put the pointer to the first of the list to move it to the last node */
			LastNode = *listHead;
			/* Traverse until the last node in the linkedlist */
			while(LastNode->nextNode != NULL)
			{
				LastNode = LastNode->nextNode;
			}
			/* Insert the added node to the last node */
			LastNode->nextNode = TempNode;
		}
		/* Assign at last the next of the node you added to NULL */
		TempNode->nextNode = NULL;
	}
	/* If there isn't place in heap to allocate */
	else
	{
		returnState = Linkedlist_Heap_Full;
	}
	return returnState;
}

LinkedList_State LinkedList_DeleteNode(SNode_t** listHead)
{
	LinkedList_State returnState = LinkedList_No_Error;
	/* Temporary nodes used to traverse in the linkedlist */
	SNode_t* previousNode = NULL;
	SNode_t* NodeToDelete = NULL;
	/* Storage to save the input of the user */
	char input[10];

	DPRINT("Enter the ID of the student you want to remove: ");
	GETS(input);

	/* Check if the list is empty or not */
	if(NULL != *listHead)
	{
		/* Put the pointer to the first of the list to move it to the last node while the previous node is behind it */
		NodeToDelete = *listHead;
		/* Traverse until the last node in the linkedlist */
		while(NodeToDelete != NULL)
		{
			/* Check if the current node is the wanted node to delete or not */
			if( atoi(input) == NodeToDelete->data.ID )
			{
				/* Check if it the first node in the list */
				if(previousNode == NULL)
				{
					*listHead = NodeToDelete->nextNode;
				}
				else
				{
					/* Skip the node will be deleted and make the previous node link with the node next to the deleted node */
					previousNode->nextNode = NodeToDelete->nextNode;
				}
				free(NodeToDelete);
				return LinkedList_No_Error;
			}
			/* Move along the linkedlist */
			previousNode = NodeToDelete;
			NodeToDelete = NodeToDelete->nextNode;
		}

		DPRINT("Cannot find this student\n");
	}
	else
	{
		returnState = LinkedList_Empty;
	}

	return returnState;
}

LinkedList_State LinkedList_DeleteAllNodes(SNode_t** listHead)
{
	LinkedList_State returnState = LinkedList_No_Error;
	/* Temporary node used to traverse in the linkedlist */
	SNode_t* TempNode = NULL;
	/* Check if the list is empty or not */
	if(NULL != *listHead)
	{
		/* Put the pointer to the first of the list to move it to the last node */
		TempNode = *listHead;
		/* Traverse until the last node in the linkedlist */
		while(NULL != TempNode)
		{
			/* Move the head to the next node to delete from the beginning */
			*listHead = (*listHead)->nextNode;
			/* Unlink the Temp node (first node) and delete it */
			TempNode->nextNode = NULL;
			free(TempNode);
			/* Points to the head of the linkedlist again */
			TempNode = *listHead;
		}
		/* Make the head of the empty list points to NULL */
		*listHead = NULL;
	}
	else
	{
		returnState = LinkedList_Empty;
	}
	return returnState;
}

uint32_t LinkedList_GetLength(SNode_t* listHead)
{
	/* Variable to count the number of nodes */
	uint32_t count=0;
	/* Temporary node used to traverse in the linkedlist */
	SNode_t* TempNode = NULL;
	/* Put the pointer to the first of the list to move it to the last node */
	TempNode = listHead;
	/* Traverse until the last node in the linkedlist */
	while(NULL != TempNode)
	{
		count++;
		TempNode = TempNode->nextNode;
	}
	return count;
}

void LinkedList_ViewAllNodes(SNode_t* listHead)
{
	/* Temporary node used to traverse in the linkedlist */
	SNode_t* TempNode = NULL;
	/* Variable to count the number of nodes and show the record number of the student */
	uint32_t count = 0;
	/* Check if the list is empty or not */
	if(NULL == listHead)
	{
		DPRINT("Your list is empty\n");
	}
	else
	{
		/* Put the pointer to the first of the list to move it to the last node */
		TempNode = listHead;
		/* Traverse until the last node in the linkedlist printing the data of the nodes */
		while(TempNode != NULL)
		{
			DPRINT("\nRecord Number: %d",++count);
			DPRINT("\nID: %d",TempNode->data.ID);
			DPRINT("\nName: %s",TempNode->data.name);
			DPRINT("\nHeight: %.3f\n",TempNode->data.height);
			TempNode=TempNode->nextNode;
		}
	}
}

void LinkedList_GetNthNodeFromFirst(SNode_t* listHead)
{
	/* Temporary node used to traverse in the linkedlist */
	SNode_t* TempNode = listHead;
	/* Variable to track the number of nodes */
	uint32_t count=0;
	/* Storage to save the input of the user */
	char nodeNumber[5];
	/* Asking the user the number of the student */
	DPRINT("Enter the Nth Student you want to get: ");
	GETS(nodeNumber);
	/* Traverse until the Nth node in the linkedlist */
	while((TempNode != NULL) && (atoi(nodeNumber) != count))
	{
		TempNode=TempNode->nextNode;
		count++;
	}
	/* Showing the data of the student */
	DPRINT("\nID: %d",TempNode->data.ID);
	DPRINT("\nName: %s",TempNode->data.name);
	DPRINT("\nHeight: %.3f\n",TempNode->data.height);
}

void LinkedList_GetNthNodeFromEnd(SNode_t* listHead)
{
	/* Temporary node used to traverse in the linkedlist */
	SNode_t* TempNode = NULL;
	/* Save the length of the linkedlist */
	uint32_t listLength = LinkedList_GetLength(listHead);
	/* Variable to the store the target we want to reach */
	uint32_t target;
	/* Storage to save the input of the user */
	char nodeNumber[5];
	/* Put the pointer to the first of the list to move it to the last node */
	TempNode = listHead;
	/* Asking the user the number of the student from the end */
	DPRINT("Enter the Nth Student from the end you want to get: ");
	GETS(nodeNumber);
	target = listLength - atoi(nodeNumber);
	listLength = 0;				/* reuse the variable to traverse */

	/* Traverse until we reach the student */
	while((TempNode != NULL) && (listLength != target))
	{
		TempNode=TempNode->nextNode;
		listLength++;
	}
	/* Showing the data of the student */
	DPRINT("\nID: %d",TempNode->data.ID);
	DPRINT("\nName: %s",TempNode->data.name);
	DPRINT("\nHeight: %.3f\n",TempNode->data.height);
}

void LinkedList_FindMiddleNode(SNode_t* listHead)
{
	/* Temporary nodes used to traverse in the linkedlist */
	SNode_t* slowPtr = listHead;				// Pointer traverse with one step
	SNode_t* fastPtr = listHead;				// Pointer traverse with two steps
	/* Traverse until the fast pointer stops at the last node */
	while(fastPtr->nextNode != NULL)
	{
		/* If the number of the nodes in list is even and we stopped at the before last node */
		if(fastPtr->nextNode->nextNode == NULL)
		{
			fastPtr= fastPtr->nextNode;
		}
		else
		{
			fastPtr= fastPtr->nextNode->nextNode;
		}
		/* Slow Pointer traverse with one step */
		slowPtr= slowPtr->nextNode;
	}
	/* Showing the data of the student */
	DPRINT("\nID: %d",slowPtr->data.ID);
	DPRINT("\nName: %s",slowPtr->data.name);
	DPRINT("\nHeight: %.3f\n",slowPtr->data.height);
}

void LinkedList_DetectLoop(SNode_t* listHead)
{
	/* Temporary nodes used to traverse in the linkedlist */
	SNode_t* slowPtr = listHead;            // Pointer traverse with one step
	SNode_t* fastPtr = listHead;            // Pointer traverse with two steps

	/* Traverse until an indictaion that there is an end of the list or At a time the slow and fast pointer will be the same */
	while(slowPtr!=NULL && fastPtr!=NULL && fastPtr->nextNode!=NULL)
	{
		fastPtr = fastPtr->nextNode->nextNode;
		slowPtr = slowPtr->nextNode;
		if(slowPtr == fastPtr)
		{
			DPRINT("Loop Detected\n");
			return;
		}
		DPRINT("There is no loop detected\n");
	}
}

void LinkedList_ReverseList(SNode_t** listHead)
{
	/* Temporary nodes used to traverse in the linkedlist */
	SNode_t* reversedListHead = NULL;
	SNode_t* TempNode = *listHead;
	/* Traverse until the last node in the linkedlist */
	while(*listHead != NULL)
	{
		/* For the first node in the list */
		if(reversedListHead == NULL)
		{
			reversedListHead = TempNode;
			*listHead = (*listHead)->nextNode;
			TempNode->nextNode = NULL;
			reversedListHead->nextNode = NULL;
		}
		else
		{
			TempNode = *listHead;
			*listHead = (*listHead)->nextNode;
			TempNode->nextNode=reversedListHead;
			reversedListHead = TempNode;
		}
	}
	*listHead = reversedListHead;
}

