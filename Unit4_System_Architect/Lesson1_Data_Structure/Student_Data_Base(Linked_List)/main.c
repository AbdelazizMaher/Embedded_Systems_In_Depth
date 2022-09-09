/*
 * main.c
 *
 *  Created on: Aug 13, 2022
 *      Author: Abdelaziz Maher
 */


#include "linked_list.h"


int main()
{
	char option[40];

	while(1)
	{
		DPRINTF("\n=============================");
		DPRINTF("\n\tChoose one of the following options");
		DPRINTF("\n1: AddStudent");
		DPRINTF("\n2: DeleteStudent");
		DPRINTF("\n3: ViewStudents");
		DPRINTF("\n4: DeleteAll");
		DPRINTF("\n5: GetNth_Student");
		DPRINTF("\n6: LengthOf_StudentList");
		DPRINTF("\n7: GetNth_StudentFromEnd");
		DPRINTF("\n8: GetMiddle_Student");
		DPRINTF("\n9: Reverse_StudentList");
		DPRINTF("\n=============================");

		DPRINTF("\nEnter Option Number : ");
		gets(option);

		DPRINTF("\n=============================");

		switch( atoi(option) )
		{
		case 1:
			AddStudent();
			break;
		case 2:
			DeleteStudent();
			break;
		case 3:
			ViewStudents();
			break;
		case 4:
			DeleteAll();
			break;
		case 5:
			GetNth_Student();
			break;
		case 6:
			LengthOf_StudentList();
			break;
		case 7:
			GetNth_StudentFromEnd();
			break;
		case 8:
			GetMiddle_Student();
			break;
		case 9:
			Reverse_StudentList();
			break;
		default:
			DPRINTF("\nWrong Option");
			break;
		}
	}

    return 0;
}
