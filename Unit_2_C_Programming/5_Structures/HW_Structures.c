#include <stdio.h>
#include <stdlib.h>

/****************C Program to store information of Student using Structure******************/
struct S_Student
{
	char name[50];
	int roll;
	float marks;
};
void EX1()
{
	struct S_Student studentInfo;

	printf("Enter information of Student:\n");

	printf("Enter name: ");
	fflush(stdout);
	scanf("%s",studentInfo.name);

	printf("Enter roll number: ");
	fflush(stdout);
	scanf("%d",&studentInfo.roll);

	printf("Enter marks: ");
	fflush(stdout);
	scanf("%f",&studentInfo.marks);

	printf("Displaying Information\nname: %s\nRoll: %d\nMarks: %.2f",studentInfo.name,studentInfo.roll,studentInfo.marks);

}

/****************C Program to add two distances in inch-feet system using Structure******************/
struct Sdistance
{
	int feet;
	float inch;
}distance1 , distance2 , result;
void EX2()
{
		printf("Enter information of 1st distance\n");
		printf("Enter feet: ");
		fflush(stdout);
		scanf("%d",&distance1.feet);
		printf("Enter inch: ");
		fflush(stdout);
		scanf("%f",&distance1.inch);

		printf("Enter information of 2nd distance\n");
		printf("Enter feet: ");
		fflush(stdout);
		scanf("%d",&distance2.feet);
		printf("Enter inch: ");
		fflush(stdout);
		scanf("%f",&distance2.inch);

		result.feet = distance1.feet + distance2.feet;
		result.inch = distance1.inch + distance2.inch;

		if(result.inch > 12)
		{
			result.inch -= 12;
			++result.feet;
		}

		printf("Sum of distances = %d'-%.1f\"",result.feet,result.inch);

}

/****************C Program to add two complex numbers by passing Structure to a function******************/
struct Scomplex
{
	float real, img;
}no1 , no2 , sum;
void AddComplex(struct Scomplex* no1,struct Scomplex* no2)
{
	printf("Sum = %.1f+%.1fi",no1->real+no2->real,no1->img+no2->img);
}
void EX3()
{
	printf("For 1st complex number\n");
	printf("Enter real and imaginary respectively:");
	fflush(stdout);
	scanf("%f %f",&no1.real,&no1.img);

	printf("For 2nd complex number\n");
	printf("Enter real and imaginary respectively:");
	fflush(stdout);
	scanf("%f %f",&no2.real,&no2.img);

	AddComplex(&no1,&no2);
}

/****************C Program to store information of Students using Structure******************/
void EX4()
{
	int i;
	struct S_Student studentInfo[10];
	printf("Enter information of Students:\n");

	/*Entering Information*/
	for(i=0; i< sizeof(studentInfo)/sizeof(struct S_Student) ; i++)
	{
		studentInfo[i].roll= i+1;
		printf("For roll number %d\n",i+1);
		printf("Enter name: ");
		fflush(stdout);
		scanf("%s",studentInfo[i].name);

		printf("Enter marks: ");
		fflush(stdout);
		scanf("%f",&studentInfo[i].marks);
	}

	/*Displaying Information*/
	printf("Displaying Information of Students:\n");
	for(i=0; i< sizeof(studentInfo)/sizeof(struct S_Student) ; i++)
	{
		printf("Information for roll number %d:\nname: %s\nMarks: %.2f\n",studentInfo[i].roll,studentInfo[i].name,studentInfo[i].marks);
	}
}

/****************C Program to Find area of a circle using macros******************/
#define PI					3.1415
#define areaOfCircle(r)		(PI*r*r)
void EX5()
{
	double raduis,area;
	printf("Enter the raduis: ");
	fflush(stdout);
	scanf("%lf",&raduis);
	area=areaOfCircle(raduis);
	printf("%.2lf",area);
}

/****************C Program to Find the size of union and structure******************/
void EX6()
{
	union U_job
	{
		char name [32] ;
		float salary;
		int worker_no;

	} U_union;

	struct S_job
	{
		char name [32];
		float salary;
		int worker_no;

	} S_structure;

	printf ("Size of the union is: %d", sizeof (U_union));
	printf ("\nSize of the structure is: %d", sizeof (S_structure));
}


int main(void) {
	EX1();
	return 0;
}
