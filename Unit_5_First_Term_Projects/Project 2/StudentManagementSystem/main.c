/*****************************************************************************/
/*****************************************************************************/
/*****************		Author: Mohamed Magdy				******************/
/*****************		Layer:  APP							******************/
/*****************		SWC: Student Management System		******************/
/*****************************************************************************/
/*****************************************************************************/

/* Include Application Header */
#include "APP.h"

/* Decleration of needed Variables */
const uint8_t QUEUE_SIZE = 50;
boolean ProgIsRunning = TRUE;
char UserInput[40];
FIFO_Buff_t StudentQueue;
FILE* StudentsData = NULL;

int main(void)
{
	/* Show Welcome message and Initialize the database */
	DPRINT("Welcome to the Student Management System.\n");
	CreateStudentDatabase(&StudentQueue,QUEUE_SIZE);

	/* Keep running the program until the user exit from it */
	while(ProgIsRunning)
	{
		/* Show Options List */
		ShowOptionsList();
		/* Take option from the User  */
		DPRINT("Enter your choice to perform the task: ");
		GETS(UserInput);
		DPRINT("--------------------------------------\n");
		/* Take an action based on the input of the user*/
		switch(atoi(UserInput))
		{
		case 1: AddStudentsFromTxtFile(&StudentQueue,StudentsData);	break;
		case 2:	AddStudentsManually(&StudentQueue); 				break;
		case 3: GetStudentByRollNum(&StudentQueue,GET_STUDENT);		break;
		case 4: GetStudentByFirstName(&StudentQueue);				break;
		case 5: GetStudentsInSpecificCourse(&StudentQueue);			break;
		case 6: GetNumberOfStudents();								break;
		case 7: DeleteStudentInfoByRollNum(&StudentQueue);			break;
		case 8: UpdateStudentInfoByRollNum(&StudentQueue);			break;
		case 9: ShowAllStudentsInfo(&StudentQueue);     			break;
		case 10: ProgIsRunning = FALSE; DPRINT("Goodbye !!\n");		break;
		}

		DPRINT("\n");
	}


	return 0;
}




