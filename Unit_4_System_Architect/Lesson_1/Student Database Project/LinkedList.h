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

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_


/* Macros helps me to use printf in eclipse */
#define DPRINT(...) 			fflush(stdin);\
		fflush(stdout);\
		printf(__VA_ARGS__);\
		fflush(stdout);\
		fflush(stdin);\

#define GETS(...)				gets(__VA_ARGS__);\
		fflush(stdout);\
		fflush(stdin);\


/* Node data structure */
typedef struct{
	int ID;
	char name[40];
	float height;
}SData_t;

/* Node structure */
typedef struct node{
	SData_t data;
	struct node* nextNode;
}SNode_t;

/* LinkedList Error States */
typedef enum{
	LinkedList_No_Error,
	LinkedList_Empty,
	Linkedlist_Heap_Full
}LinkedList_State;

/**
  * @brief  This API insert a node at the beginnig of the linkedlist.
  * @param  (listHead) pointer to pointer of the linkedlist head (Pass by refrence help me to change in the head).
  * @retval Status returned while performing this operation.
  */
LinkedList_State LinkedList_InsertNodeAtBeginning(SNode_t** listHead);

/**
  * @brief  This API insert a node at the end of the linkedlist.
  * @param  (listHead) pointer to pointer of the linkedlist head (Pass by refrence help me to change in the head).
  * @retval Status returned while performing this operation.
  */
LinkedList_State LinkedList_InsertNodeAtEnd(SNode_t** listHead);

/**
  * @brief  This API delete a node according to the student ID in the linkedlist.
  * @param  (listHead) pointer to pointer of the linkedlist head (Pass by refrence help me to change in the head).
  * @retval Status returned while performing this operation.
  */
LinkedList_State LinkedList_DeleteNode(SNode_t** listHead);

/**
  * @brief  This API destroy all the nodes in the linkedlist.
  * @param  (listHead) pointer to pointer of the linkedlist head (Pass by refrence help me to change in the head).
  * @retval Status returned while performing this operation.
  */
LinkedList_State LinkedList_DeleteAllNodes(SNode_t** listHead);

/**
  * @brief  This API get the length of the linkedlist (number of nodes).
  * @param  (listHead) pointer of the linkedlist head (Pass by value as I don't need to change in listhead).
  * @retval The length of the linkedlist.
  */
uint32_t LinkedList_GetLength(SNode_t* listHead);

/**
  * @brief  This API view all the nodes of the linkedlist.
  * @param  (listHead) pointer of the linkedlist head (Pass by value as I don't need to change in listhead).
  * @retval Doesn't return anything.
  */
void LinkedList_ViewAllNodes(SNode_t* listHead);

/**
  * @brief  This API get the Nth node in the linkedlist from the first node.
  * @param  (listHead) pointer of the linkedlist head (Pass by value as I don't need to change in listhead).
  * @retval Doesn't return anything.
  */
void LinkedList_GetNthNodeFromFirst(SNode_t* listHead);

/**
  * @brief  This API get the Nth node in the linkedlist from the last node.
  * @param  (listHead) pointer of the linkedlist head (Pass by value as I don't need to change in listhead).
  * @retval Doesn't return anything.
  */
void LinkedList_GetNthNodeFromEnd(SNode_t* listHead);

/**
  * @brief  This API get the middle node in the linkedlist (if length of linkedlist is even we get the second node in the middle.
  * @param  (listHead) pointer of the linkedlist head (Pass by value as I don't need to change in listhead).
  * @retval Doesn't return anything.
  */
void LinkedList_FindMiddleNode(SNode_t* listHead);

/**
  * @brief  This API detects if there is a loop in the linkedlist.
  * @param  (listHead) pointer of the linkedlist head (Pass by value as I don't need to change in listhead).
  * @retval Doesn't return anything.
  */
void LinkedList_DetectLoop(SNode_t* listHead);

/**
  * @brief  This API reverse the linkedlist.
  * @param  (listHead) pointer to pointer of the linkedlist head (Pass by refrence help me to change in the head).
  * @retval Doesn't return anything.
  */
void LinkedList_ReverseList(SNode_t** listHead);

#endif /* LINKEDLIST_H_ */
