/*****************************************************************************/
/*****************************************************************************/
/*****************		Author: Mohamed Magdy				******************/
/*****************		Layer:  APP							******************/
/*****************		SWC: Student Management System		******************/
/*****************************************************************************/
/*****************************************************************************/
#ifndef APP_H_
#define APP_H_

/*****************************************************************************
 *							Include used libraries
 ****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Platform_Types.h"
#include "FIFO.h"

/*****************************************************************************
 *								 Helper Macros
 ****************************************************************************/
#define DPRINT(...) 			fflush(stdin);\
		fflush(stdout);\
		printf(__VA_ARGS__);\
		fflush(stdout);\
		fflush(stdin);\

#define GETS(...)				gets(__VA_ARGS__);\
		fflush(stdout);\
		fflush(stdin);\

#define GET_STUDENT				((uint8_t)(0))
#define UPDATE_STUDENT			((uint8_t)(1))

#define FILE_NAME				"Database.txt"


/*****************************************************************************
 *							 App Error States
 ****************************************************************************/
typedef enum{
	APP_No_Errors,
	APP_Error
}APP_Status_t;

/*****************************************************************************
 *							 Application APIs
 ****************************************************************************/
void CreateStudentDatabase(FIFO_Buff_t* studentDataBase,uint8_t DatabaseSize);
void ShowOptionsList(void);
void AddStudentsFromTxtFile(FIFO_Buff_t* studentDataBase,FILE* textFile);
APP_Status_t AddStudentsManually(FIFO_Buff_t* studentDataBase);
int GetStudentByRollNum(FIFO_Buff_t* studentDataBase,uint8_t Command);
void GetStudentByFirstName(FIFO_Buff_t* studentDataBase);
void GetStudentsInSpecificCourse(FIFO_Buff_t* studentDataBase);
void GetNumberOfStudents(void);
void DeleteStudentInfoByRollNum(FIFO_Buff_t* studentDataBase);
void UpdateStudentInfoByRollNum(FIFO_Buff_t* studentDataBase);
void ShowAllStudentsInfo(FIFO_Buff_t* studentDataBase);

#endif /* APP_H_ */
