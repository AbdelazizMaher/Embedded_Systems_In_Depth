/*
 * linked_list.c
 *
 *  Created on: Aug 13, 2022
 *      Author: Abdel
 */

#include "linked_list.h"


struct S_Student* gpFirstStudent = NULL;

void fill_the_record(struct S_Student* data)
{
	char temp_text[50];

	DPRINTF("\nEnter the ID : ");
	gets(temp_text);
	data->Student.ID = atoi(temp_text);

	DPRINTF("\nEnter the student full name : ");
	gets(data->Student.name);

	DPRINTF("\nEnter height : ");
	gets(temp_text);
	data->Student.height = atof(temp_text);
}

void AddStudent()
{
	struct S_Student* pAddedStudent;
	struct S_Student* pLastStudent;

	if( gpFirstStudent == NULL )
	{
		pAddedStudent = ( struct S_Student* )malloc( sizeof(struct S_Student) );
		gpFirstStudent = pAddedStudent;
	}
	else
	{
		pLastStudent = gpFirstStudent;
		while( pLastStudent->pNextStudent )
			pLastStudent = pLastStudent->pNextStudent;

		pAddedStudent = ( struct S_Student* )malloc( sizeof(struct S_Student) );
		pLastStudent->pNextStudent = pAddedStudent;
	}

	pAddedStudent->pNextStudent = NULL;

	fill_the_record(pAddedStudent);
}

void DeleteStudent()
{
	char temp_text[20];
	unsigned int selected_id;

	DPRINTF("\nEnter the student ID to be deleted : ");
	gets(temp_text);
	selected_id = atoi(temp_text);

	if( gpFirstStudent )
	{
		struct S_Student* pPreviousStudent = NULL;
		struct S_Student* pSelectedStudent = gpFirstStudent;

		while( pSelectedStudent )
		{
			if( pSelectedStudent->Student.ID == selected_id )
			{
				if( pPreviousStudent )
				{
					pPreviousStudent->pNextStudent = pSelectedStudent->pNextStudent;
				}
				else
				{
					gpFirstStudent =  pSelectedStudent->pNextStudent;
				}

				free(pSelectedStudent);
				return;
			}
			pPreviousStudent = pSelectedStudent;
			pSelectedStudent->pNextStudent = pSelectedStudent;
		}

	}

	DPRINTF("\nCannot find the student id : ");

	return;
}

void ViewStudents()
{
	int count = 1;
	struct S_Student* pViewStudent = gpFirstStudent;

	if( gpFirstStudent == NULL )
		DPRINTF("\nEmpty List")

	while( pViewStudent )
	{
		DPRINTF("\nRecord Number : %d", count);
		DPRINTF("\nID : %d ", pViewStudent->Student.ID );
		DPRINTF("\nName : %s ", pViewStudent->Student.name);
		DPRINTF("\nHeight : %.2f ", pViewStudent->Student.height);

		pViewStudent = pViewStudent->pNextStudent;
		count++;
	}
}

void DeleteAll()
{
	struct S_Student* pDeleteStudent = gpFirstStudent;

	if( gpFirstStudent == NULL )
		DPRINTF("\nEmpty List")

	while( pDeleteStudent )
	{
		struct S_Student* pTempStudent = pDeleteStudent;

		pDeleteStudent = pDeleteStudent->pNextStudent;
		free(pTempStudent);
	}
	gpFirstStudent = NULL;
}

void GetNth_Student()
{
	int count = 1;
	unsigned int selected_index;
	char temp_text[20];

	DPRINTF("\nEnter the Index of the student : ");
	gets(temp_text);
	selected_index = atoi(temp_text);

	struct S_Student* pGetStudent = gpFirstStudent;

	if( gpFirstStudent == NULL )
		DPRINTF("\nEmpty List ... ")

	while( pGetStudent )
	{
		if( count == selected_index )
		{
			DPRINTF("\nStudent At Index : %d", count);
			DPRINTF("\nID : %d", pGetStudent->Student.ID );
			DPRINTF("\nName : %s", pGetStudent->Student.name);
			DPRINTF("\nHeight: %.2f", pGetStudent->Student.height);
			return;
		}
		pGetStudent = pGetStudent->pNextStudent;
		count++;
	}
	DPRINTF("\nNo Student Found At Index %d ",selected_index);
}

void LengthOf_StudentList()
{
	int length;
	struct S_Student* pLength = gpFirstStudent;

	length = GetLength_Recursive(pLength);

	DPRINTF("\nLength Of List : %d", length);
}

int GetLength_Recursive(struct S_Student* pLength)
{
	if( !pLength )
		return 0;

	return 1 + GetLength_Recursive( pLength->pNextStudent );
}

void GetNth_StudentFromEnd()
{
	unsigned int selected_index;
	char temp_text[20];

	struct S_Student* pRefStudent = gpFirstStudent;
	struct S_Student* pGetStudent = gpFirstStudent;

	DPRINTF("\nEnter the Index of the student : ");
	gets(temp_text);
	selected_index = atoi(temp_text);

    while( selected_index )
    {
    	if( pRefStudent == NULL)
    	{
    		DPRINTF("\nNo Student Found At Index %d From End",atoi(temp_text));
    		return;
    	}
    	pRefStudent = pRefStudent->pNextStudent;
    	selected_index--;
    }

    while( pRefStudent )
    {
    	pRefStudent = pRefStudent->pNextStudent;
    	pGetStudent = pGetStudent->pNextStudent;
    }

	DPRINTF("\nStudent At Index %d From End", atoi(temp_text) );
	DPRINTF("\nID : %d", pGetStudent->Student.ID );
	DPRINTF("\nName : %s", pGetStudent->Student.name);
	DPRINTF("\nHeight: %.2f", pGetStudent->Student.height);
}

void GetMiddle_Student()
{
	struct S_Student* pRefStudent = gpFirstStudent;
	struct S_Student* pGetMidStudent = gpFirstStudent;

    while( pRefStudent )
    {
    	pRefStudent = pRefStudent->pNextStudent;
    	if( pRefStudent == NULL)
    		break;
    	pRefStudent = pRefStudent->pNextStudent;
    	pGetMidStudent = pGetMidStudent->pNextStudent;
    }

	DPRINTF("\nStudent At Middle");
	DPRINTF("\nID : %d", pGetMidStudent->Student.ID );
	DPRINTF("\nName : %s", pGetMidStudent->Student.name);
	DPRINTF("\nHeight: %.2f", pGetMidStudent->Student.height);
}

void Reverse_StudentList()
{
	struct S_Student* pPreviousStudent = NULL;
	struct S_Student* pCurrentStudent = gpFirstStudent;
	struct S_Student* pNextStudent = NULL;

    while( pCurrentStudent )
    {
    	pNextStudent = pCurrentStudent->pNextStudent;
    	pCurrentStudent->pNextStudent = pPreviousStudent;
    	pPreviousStudent = pCurrentStudent;
    	pCurrentStudent = pNextStudent;
    }

    gpFirstStudent = pPreviousStudent;
}
