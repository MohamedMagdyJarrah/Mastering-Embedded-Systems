/*****************************************************************************/
/*****************************************************************************/
/*****************		Author: Mohamed Magdy				******************/
/*****************		Layer:  APP							******************/
/*****************		SWC: Student Management System		******************/
/*****************************************************************************/
/*****************************************************************************/
#include "APP.h"

/* Variable to store the data sent by the user and track the number of students */
char line[80];
uint8_t courses = 5;
char Input[40];
uint8_t NumberofStudents = 0;
static void GetOneStudent(StudentData_t* student);
static boolean checkCoursesID(int* CoursesList,uint8_t courseID);
static boolean PresenceOfRollNumber(FIFO_Buff_t* studentDataBase,uint8_t rollNumber);

/*****************************************************************************
 *					Function to initialize the database
 ****************************************************************************/
void CreateStudentDatabase(FIFO_Buff_t* studentDataBase,uint8_t DatabaseSize)
{
	/* Create a Queue for student database */
	FIFO_InitQueue(studentDataBase,DatabaseSize);
}

/*****************************************************************************
 *					Function to print the options list
 ****************************************************************************/
void ShowOptionsList(void)
{
	DPRINT("------------------------------------------------\n");
	DPRINT("	Choose an Option from list to do:  			\n");
	DPRINT("------------------------------------------------\n");
	DPRINT("1 : Add student from text file.        			\n");
	DPRINT("2 : Add student manually. 		   				\n");
	DPRINT("3 : Get student by Roll number.   				\n");
	DPRINT("4 : Get student by first name.	   				\n");
	DPRINT("5 : Get students registered in specific course.	\n");
	DPRINT("6 : Get number of students.						\n");
	DPRINT("7 : Delete student by Roll number.           	\n");
	DPRINT("8 : Update student by Roll number.             	\n");
	DPRINT("9 : Show all information.				        \n");
	DPRINT("10: Exit system.				               	\n");
	DPRINT("------------------------------------------------\n");
}


/*****************************************************************************
 *			Function to Add students data from file in the database
 ****************************************************************************/
void AddStudentsFromTxtFile(FIFO_Buff_t* studentDataBase,FILE* textFile)
{
	uint8_t i = 0 , j = 0 ,closeFileState = 0;
	/* Open the file with read command */
	textFile = fopen(FILE_NAME,"r");

	/* Check the file opened successfully or not */
	if(NULL != textFile)
	{
		/* Loop on each line(student) in the file */
		while(fgets(line,80,textFile) != NULL)
		{
			studentDataBase->data[i].rollNumber = atoi(strtok(line,","));
			/* Check the roll number is availabe or already taken */
			if(PresenceOfRollNumber(studentDataBase,studentDataBase->data[i].rollNumber) == TRUE)
			{
				DPRINT("[ERROR] Roll Number %d is already taken.\n",studentDataBase->data[i].rollNumber);
				continue;
			}
			/* Save the rest of the student details if the roll number is unique */
			strcpy(studentDataBase->data[i].FirstName , strtok(NULL,","));
			strcpy(studentDataBase->data[i].LastName , strtok(NULL,","));
			studentDataBase->data[i].GPA = atof(strtok(NULL,","));
			for(j=0 ; j<courses ; j++)
			{
				studentDataBase->data[i].coursesID[j] = atoi(strtok(NULL,","));
			}

			DPRINT("[INFO] Roll Number %d is saved successfully.\n",studentDataBase->data[i].rollNumber);

			NumberofStudents++;
			i++;
		}
	}
	else
	{
		DPRINT("[ERROR] Problem Reading the file.\n");
	}

	/* Closing the file after reading all the data */
	closeFileState = fclose(textFile);
	if(0 == closeFileState)
	{
		DPRINT("[INFO] Students Detail is added successfully.\n");
		DPRINT("----------------------------------------------\n");
		GetNumberOfStudents();
	}
	else
	{
		DPRINT("[ERROR] Problem Closing the file.\n");
	}
}


/*****************************************************************************
 *			Function to Add student data manually in the database
 ****************************************************************************/
APP_Status_t AddStudentsManually(FIFO_Buff_t* studentDataBase)
{
	APP_Status_t ErrorStatus = APP_No_Errors;
	FIFO_Status_t QueueStatus = FIFO_No_Errors;
	uint8_t i = 0;
	StudentData_t inputData;

	/* Take the data from the user manually */
	DPRINT("Add the Student Details  \n");
	DPRINT("-------------------------\n");

	DPRINT("Enter the Roll Number: ");
	GETS(Input);

	/* Check the roll number is availabe or already taken and keep asking until the user choose unique one */
	while(PresenceOfRollNumber(studentDataBase,atoi(Input)) == TRUE)
	{
		DPRINT("[ERROR] Roll Number %d is already taken.\n",atoi(Input));
		DPRINT("Enter unique Roll Number: ");
		GETS(Input);
	}
	inputData.rollNumber = atoi(Input);

	DPRINT("Enter the first name of student: ");
	GETS(Input);
	strcpy(inputData.FirstName,Input);

	DPRINT("Enter the last name of student: ");
	GETS(Input);
	strcpy(inputData.LastName,Input);

	DPRINT("Enter the GPA you obtained: ");
	GETS(Input);
	inputData.GPA = atof(Input);

	DPRINT("Enter the course ID for each course:\n");
	for(i = 0 ; i < courses ; i++)
	{
		DPRINT("Course %d ID: ",i+1);
		GETS(Input);
		if(checkCoursesID(inputData.coursesID,atoi(Input)) == TRUE)
		{
			DPRINT("===>Course ID entered before<===\n");
			i--;
			continue;
		}
		inputData.coursesID[i] = atoi(Input);
	}

	/* Enqueue the new student in the queue created for the database */
	QueueStatus = FIFO_EnqueueItem(studentDataBase,&inputData);

	/* Check the buffer can take this student or not */
	if(FIFO_Full == QueueStatus)
	{
		DPRINT("[ERROR] Student Database is full, We can't save this student.\n");
		ErrorStatus = APP_Error;
	}
	else
	{
		NumberofStudents++;
		DPRINT("[INFO] Student Details is added Successfully.\n");
		DPRINT("---------------------------------------------\n");
		GetNumberOfStudents();
	}


	return ErrorStatus;
}

/*****************************************************************************
 *		Function to get the students from the database by Roll Number
 *	Note: This function is used also to return the place
 *		   of the student's data to update its values
 ****************************************************************************/
int GetStudentByRollNum(FIFO_Buff_t* studentDataBase,uint8_t Command)
{
	uint8_t i = 0 , studentFound = 0;

	DPRINT("Enter the Roll Number of the student: ");
	GETS(Input);

	/* Loop on all the students in the database until finding the roll number */
	for(i=0 ; i<NumberofStudents ; i++)
	{
		if((atoi(Input)) == studentDataBase->data[i].rollNumber)
		{
			studentFound = 1;

			/* If the we want to only get the student details we will print it on the screen */
			if(Command == GET_STUDENT)
			{
				DPRINT("The Student Details are: \n");
				DPRINT("---------------------------------\n");
				GetOneStudent(&(studentDataBase->data[i]));
				DPRINT("---------------------------------\n");
			}
			/* If the command is to update the student we will return the index of the student's details */
			else if(Command == UPDATE_STUDENT)
			{
				return i;
			}
		}
	}

	/* If the student not found the flag will still zero so print error message */
	if(!studentFound)
	{
		DPRINT("[ERROR] Roll number %d not found.\n",atoi(Input));
	}
	/* Return -1 if we didn't find the student */
	return -1;
}

/*****************************************************************************
 *		Function to get the students from the database by First Name
 ****************************************************************************/
void GetStudentByFirstName(FIFO_Buff_t* studentDataBase)
{
	uint8_t i = 0 , studentFound = 0;

	DPRINT("Enter the first name of the student: ");
	GETS(Input);

	/* Loop on all the students in the database until finding students with entered first name
	 * and print every the student's details with the entered first name
	 *  */
	for(i=0 ; i<NumberofStudents ; i++)
	{
		if(!strcmp(Input,studentDataBase->data[i].FirstName))
		{
			DPRINT("The Student Details are: \n");
			DPRINT("---------------------------------\n");
			GetOneStudent(&(studentDataBase->data[i]));
			DPRINT("---------------------------------\n");
			studentFound = 1;
		}
	}

	/* If the student not found the flag will still zero so print error message */
	if(!studentFound)
	{
		DPRINT("[ERROR] first name %s not found.\n",Input);
	}
}

/*****************************************************************************
 *		Function to get the students enrolled in specific course
 ****************************************************************************/
void GetStudentsInSpecificCourse(FIFO_Buff_t* studentDataBase)
{
	boolean courseFound = FALSE;
	uint8_t i = 0;

	DPRINT("Enter the course ID: ");
	GETS(Input);

	/* Loop on all the students in the database and print there data if they take the entered course ID */
	for(i=0 ; i<NumberofStudents ; i++)
	{
		if(checkCoursesID(studentDataBase->data[i].coursesID,atoi(Input)) == TRUE)
		{
			DPRINT("The Student Details are: \n");
			DPRINT("---------------------------------\n");
			DPRINT("Student first name: %s\n"  , studentDataBase->data[i].FirstName);
			DPRINT("Student last name: %s\n"   , studentDataBase->data[i].LastName  );
			DPRINT("Student roll number: %d\n" , studentDataBase->data[i].rollNumber);
			DPRINT("Student GPA number: %.2f\n", studentDataBase->data[i].GPA	   );
			DPRINT("---------------------------------\n");
			courseFound = TRUE;
		}
	}

	/* Print Error message if there is no one registered the course */
	if(!courseFound)
	{
		DPRINT("Course ID %d not found\n",atoi(Input));
	}
}

/*****************************************************************************
 *			Function to get the number of students in the database
 ****************************************************************************/
void GetNumberOfStudents(void)
{
	DPRINT("[INFO] The total number of Student is %d.\n",NumberofStudents);
	DPRINT("[INFO] You can add up to 50 Students.\n");
	DPRINT("[INFO] You can add up %d more Students.\n",50-NumberofStudents);
}

/*****************************************************************************
 *		Function to delete the student details by the Roll Number
 ****************************************************************************/
void DeleteStudentInfoByRollNum(FIFO_Buff_t* studentDataBase)
{
	int chosenStudent = 0;
	uint8_t i = 0;

	/* Get the student roll number with checking if it occurs or not */
	chosenStudent = GetStudentByRollNum(studentDataBase,UPDATE_STUDENT);
	if(chosenStudent == -1)
		return;

	/* Shift back all the remaining students */
	for(i=chosenStudent ; i<NumberofStudents-1 ; i++)
	{
		strcpy(studentDataBase->data[i].FirstName,studentDataBase->data[i+1].FirstName);
		strcpy(studentDataBase->data[i].LastName,studentDataBase->data[i+1].LastName);
		studentDataBase->data[i].rollNumber = studentDataBase->data[i+1].rollNumber;
		studentDataBase->data[i].GPA = studentDataBase->data[i+1].GPA;
		studentDataBase->data[i].coursesID[0] = studentDataBase->data[i+1].coursesID[0];
		studentDataBase->data[i].coursesID[1] = studentDataBase->data[i+1].coursesID[1];
		studentDataBase->data[i].coursesID[2] = studentDataBase->data[i+1].coursesID[2];
		studentDataBase->data[i].coursesID[3] = studentDataBase->data[i+1].coursesID[3];
		studentDataBase->data[i].coursesID[4] = studentDataBase->data[i+1].coursesID[4];
	}
	DPRINT("[INFO] Student Details is removed Successfully.\n");
	/* Dequeue the last student in the buffer after shifting all the students */
	FIFO_DequeueItem(studentDataBase,NULL);
	/* Decremenet the number of the students */
	NumberofStudents--;
}

/*****************************************************************************
 *		Function to update the student details by the Roll Number
 ****************************************************************************/
void UpdateStudentInfoByRollNum(FIFO_Buff_t* studentDataBase)
{
	int chosenStudent = 0;
	char choice[10] , courseID[2];

	/* Get the student roll number with checking if it occurs or not */
	chosenStudent = GetStudentByRollNum(studentDataBase,UPDATE_STUDENT);
	if(chosenStudent == -1)
		return;

	/* Label to come back and re-enter the correct option if the user entered wrong one */
	VIEW_AGAIN:
	DPRINT("---------------------------------\n");
	DPRINT("1. first name.\n");
	DPRINT("2. last name.\n");
	DPRINT("3. Roll Number.\n");
	DPRINT("4. GPA.\n");
	DPRINT("5. Courses.\n");
	DPRINT("Choose the sector you want to update: ");
	GETS(choice);

	/* Take the action based on the choice taken */
	switch (atoi(choice)) {
	case 1:
		DPRINT("Enter the new first name: ");
		GETS(choice);
		strcpy(studentDataBase->data[chosenStudent].FirstName,choice);
		break;
	case 2:
		DPRINT("Enter the new last name: ");
		GETS(choice);
		strcpy(studentDataBase->data[chosenStudent].LastName,choice);
		break;
	case 3:
		DPRINT("Enter the new roll number: ");
		GETS(choice);
		studentDataBase->data[chosenStudent].rollNumber = atoi(choice);
		break;
	case 4:
		DPRINT("Enter the new GPA: ");
		GETS(choice);
		studentDataBase->data[chosenStudent].GPA = atof(choice);
		break;
	case 5:
		DPRINT("Enter the which course: ");
		GETS(choice);
		DPRINT("Enter the new course ID: ");
		GETS(courseID);
		studentDataBase->data[chosenStudent].coursesID[atoi(choice)] = atof(courseID);
		break;
	default:
		DPRINT("Wrong Choice, Choose again.\n");
		goto VIEW_AGAIN;
		break;
	}

}

/*****************************************************************************
 *			Function to show all the data of all students
 ****************************************************************************/
void ShowAllStudentsInfo(FIFO_Buff_t* studentDataBase)
{
	uint8_t i = 0;

	if(0 == NumberofStudents)
	{
		DPRINT("There are no students yet in the database.\n");
	}
	else
	{
		for(i=0 ; i<NumberofStudents ; i++)
		{
			DPRINT("The Student Details are: \n");
			DPRINT("---------------------------------\n");
			GetOneStudent(&(studentDataBase->data[i]));
			DPRINT("---------------------------------\n");
		}
	}

}


/*****************************************************************************
 *			Static Function to print the student details
 ****************************************************************************/
static void GetOneStudent(StudentData_t* student)
{
	uint8_t i =0;
	DPRINT("Student first name: %s\n"  , student->FirstName );
	DPRINT("Student last name: %s\n"   , student->LastName  );
	DPRINT("Student roll number: %d\n" , student->rollNumber);
	DPRINT("Student GPA number: %.2f\n", student->GPA	   );

	for(i = 0 ; i < courses ; i++)
	{
		DPRINT("%d. The Course ID: %d\n", i+1 ,student->coursesID[i]);
	}

}

/*****************************************************************************
 *			Static Function to check the courses ID list
 ****************************************************************************/
static boolean checkCoursesID(int* CoursesList,uint8_t courseID)
{
	boolean courseFound = FALSE;
	uint8_t i=0;

	for(i=0 ; i<courses ; i++)
	{
		if(CoursesList[i] == courseID)
		{
			courseFound = TRUE;
			break;
		}
	}

	return courseFound;
}

/*****************************************************************************
 *			Static Function to check the Roll number of the students
 ****************************************************************************/
static boolean PresenceOfRollNumber(FIFO_Buff_t* studentDataBase,uint8_t rollNumber)
{
	boolean rollNumberFound = FALSE;
	uint8_t i=0;

	for(i=0 ; i<NumberofStudents ; i++)
	{
		if(studentDataBase->data[i].rollNumber == rollNumber)
		{
			rollNumberFound = TRUE;
			break;
		}
	}

	return rollNumberFound;
}
