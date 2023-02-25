/*
 * main.c
 *
 *  Created on: Feb 22, 2023
 *      Author: Abdelaziz Maher
 */

#include "Database.h"
#include "fifo.h"

int main()
{
	char option[40];

	if( Init_DataBaseQueue()  != FIFO_NO_ERROR )
	{
		DPRINTF("\n[ERROR] DataBase Not Initialized Successfully");

		return FIFO_ERROR;
	}

	DPRINTF("\n\t <<========== Welcome To The Students Management System =========>>\n");
	while(1)
	{
		DPRINTF("\n=============================");
		DPRINTF("\n\tChoose one of the following options");
		DPRINTF("\n1: Add The Student Details Manually");
		DPRINTF("\n2: Add The Student Details From Text File");
		DPRINTF("\n3: Find The Student Details By Roll Number");
		DPRINTF("\n4: Find The Student Details By First Name");
		DPRINTF("\n5: Find The Student Details By Course ID");
		DPRINTF("\n6: Find The Total Number Of Students");
		DPRINTF("\n7: Delete The Student Details By Roll Number");
		DPRINTF("\n8: Update The Student Details By Roll Number");
		DPRINTF("\n9: Show All Students Information");
		DPRINTF("\n10: EXIT");
		DPRINTF("\n=============================");

		DPRINTF("\nEnter Option Number : ");
		gets(option);

		DPRINTF("\n=============================");

		switch( atoi(option) )
		{
		case 1:
			AddStudent_Manually();
			break;
		case 2:
			AddStudent_From_File();
			break;
		case 3:
			FindBy_Roll();
			break;
		case 4:
			FindBy_FirstName();
			break;
		case 5:
			FindBy_CourseID();
			break;
		case 6:
			TotalStudents();
			break;
		case 7:
			DeleteStudent_ByRoll();
			break;
		case 8:
			UpdateStudent_Details_ByRoll();
			break;
		case 9:
			ViewStudents();
			break;
		case 10:
			exit(0);
			break;
		default:
			DPRINTF("\nWrong Option");
			break;
		}
	}

    return 0;
}
