/*
 * Database.c
 *
 *  Created on: Feb 22, 2023
 *      Author: Abdel
 */


#include "Database.h"
#include "fifo.h"


static int fill_the_record(sStudentInfo* data);
static int CheckValid_ID(int id);


FIFO_t DataBase;
sStudentInfo DataBase_BUFF[50];

int Init_DataBaseQueue()
{
	if( FIFO_Init(&DataBase , DataBase_BUFF, 50) == FIFO_NO_ERROR )
		return FIFO_NO_ERROR;

	return FIFO_ERROR;
}


int fill_the_record(sStudentInfo* data)
{
	char temp_text[50];
	int i;

	DPRINTF("\nStudent Roll Number: ");
	gets(temp_text);

	if( CheckValid_ID( atoi(temp_text) ) == UNVALID_ID )
	{
		DPRINTF("\n[ERROR] Roll Number %d Is Already Taken",atoi(temp_text) );

		return UNVALID_ID; // None valid id
	}


	data->Roll = atoi(temp_text);

	DPRINTF("\nStudent First Name: ");
	gets(data->FirstName);

	DPRINTF("\nStudent Last Name: ");
	gets(data->LastName);

	DPRINTF("\nStudent GPA: ");
	gets(temp_text);
	data->GPA = atof(temp_text);

	DPRINTF("\nEnter Course ID of each Course: ");
    for(i = 0 ; i < 5 ; i++ )
    {
    	DPRINTF("\nCourse %d ID : ", i+1 );

    	gets(temp_text);
    	data->Course_ID[i] = atoi(temp_text);
    }

    return 0;
}


int CheckValid_ID(int id)
{
	int i;

	for( i = 0 ; i < DataBase.count ; i++ )
	{
		if( (DataBase_BUFF[i].Roll ) == id )
			return UNVALID_ID;  //None valid id
	}
	return 0;
}



void AddStudent_From_File()
{
	int i;

	FILE *Student_File = fopen("Student_List.txt", "r" );

    if(Student_File == NULL){
        printf("\t[ERROR]File opening Failed\n");
        return;
    }

	while( !feof(Student_File) && FIFO_IsFull(&DataBase) != FIFO_FULL )
	{
		sStudentInfo pAddedStudent ;

		fscanf(Student_File,"%d", &(pAddedStudent.Roll) );
		fscanf(Student_File,"%s", (pAddedStudent.FirstName) );
		fscanf(Student_File,"%s", (pAddedStudent.LastName) );
		fscanf(Student_File,"%f", &(pAddedStudent.GPA) );

	    for(i = 0 ; i < 5 ; i++ )
	    {
	    	fscanf(Student_File,"%d", &(pAddedStudent.Course_ID[i]) );
	    }

		//Check its validity
		if( CheckValid_ID( pAddedStudent.Roll ) == UNVALID_ID )
		{
			DPRINTF("\n[ERROR] Roll Number %d Is Already Taken", pAddedStudent.Roll );

			continue;
		}

	    FIFO_Enqueue(&DataBase , pAddedStudent );
	}
	fclose(Student_File);

	DPRINTF("\n[INFO] Student Details Are Added Successfully" );

}

void AddStudent_Manually()
{
	if( FIFO_IsFull(&DataBase) != FIFO_FULL )
	{
		if( fill_the_record(&DataBase_BUFF[DataBase.count]) == DATA_EXIST )
		{
			DPRINTF("\n[ERROR] Roll Number %d Is Already Taken", DataBase_BUFF[DataBase.count].Roll );
		}
		else
		{
			FIFO_Enqueue(&DataBase , DataBase_BUFF[DataBase.count] );
			DPRINTF("\n[INFO] Student Details Are Added Successfully" );
		}
	}
	else
	{
		DPRINTF("\n[ERROR] DataBase Queue Is FULL:");
	}
}
void DeleteStudent_ByRoll()
{
	int ID_ToDelete;
	int i , Pos = UNVALID_POS;
	DPRINTF("\nEnter The Roll Number You Want To Delete:");
	scanf("%d",&ID_ToDelete);

	for(i = 0 ; i < DataBase.count ; i++)
	{
		if(DataBase_BUFF[i].Roll == ID_ToDelete)
		{
			Pos = i;
			break;
		}
	}

	if( Pos == UNVALID_POS)
	{
		DPRINTF("\n[ERROR] This Roll Number %d Is Not Found",ID_ToDelete);
		return;
	}

	for(i = Pos ; i < DataBase.count ; i++ )
		DataBase_BUFF[i] = DataBase_BUFF[i+1];

	DataBase.head--;
	DataBase.count--;

	DPRINTF("\n[INFO] This Roll Number Is Removed Successfully");

}

void ViewStudents()
{
	int i, j;

	DPRINTF("\n\t==============Students Info In The DataBase=============\n");
	for(i = 0; i < DataBase.count ; i++ )
	{
		DPRINTF("\n===========Student %d Info========== \n", i+1);

		DPRINTF("Student First Name: %s \n", DataBase_BUFF[i].FirstName);
		DPRINTF("Student Last Name: %s \n", DataBase_BUFF[i].LastName);
		DPRINTF("Student Roll Number: %d \n", DataBase_BUFF[i].Roll);
		DPRINTF("Student GPA: %f \n", DataBase_BUFF[i].GPA);
	    for(j = 0 ; j < 5 ; j++ )
	    {
	    	DPRINTF("Course %d ID : %d \n", j+1 , DataBase_BUFF[i].Course_ID[j]);
	    }
	}

}
void TotalStudents()
{
	DPRINTF("\n[INFO] The Total Number Of students is %d",DataBase.count);
	DPRINTF("\n[INFO] You Can Add Up To 50 Students\n");
	DPRINTF("\n[INFO] You Can Add %d More Students", 50-DataBase.count );
}
void FindBy_Roll()
{
	int Roll_ToFind, result = RESULT_NOT_FOUND;
	int i , j;

	DPRINTF("\nEnter The Roll Number Of The Student:");
	scanf("%d",&Roll_ToFind);

	for(i = 0 ; i < DataBase.count ; i++)
	{
		result =  DataBase_BUFF[i].Roll == Roll_ToFind;
		if( result == RESULT_FOUND )
		{
			DPRINTF("\n\t==============The Student Details=============\n");

			DPRINTF("Student First Name: %s \n", DataBase_BUFF[i].FirstName);
			DPRINTF("Student Last Name: %s \n", DataBase_BUFF[i].LastName);
			DPRINTF("Student Roll Number: %d \n", DataBase_BUFF[i].Roll);
			DPRINTF("Student GPA: %f \n", DataBase_BUFF[i].GPA);

		    for(j = 0 ; j < 5 ; j++ )
		    {
		    	DPRINTF("\nCourse %d ID : %d ", j+1 , DataBase_BUFF[i].Course_ID[j]);
		    }

			break;
		}
	}

	if( result == RESULT_NOT_FOUND)
	{
		DPRINTF("\n[ERROR] This Roll Number %d Is Not Found",Roll_ToFind);
		return;
	}


}
void FindBy_CourseID()
{
	int CourseID_ToFind, flag = 0;
	int i , j;

	DPRINTF("\nEnter The Course ID Of The Student:");
	scanf("%d",&CourseID_ToFind);

	for(i = 0 ; i < DataBase.count ; i++)
	{
		for(j = 0 ; j < 5 ; j++)
		{
			if( DataBase_BUFF[i].Course_ID[j] == CourseID_ToFind )
			{
				DPRINTF("\n\t==============The Student Details=============\n");

				DPRINTF("Student First Name: %s \n", DataBase_BUFF[i].FirstName);
				DPRINTF("Student Last Name: %s \n", DataBase_BUFF[i].LastName);
				DPRINTF("Student Roll Number: %d \n", DataBase_BUFF[i].Roll);
				DPRINTF("Student GPA: %f \n", DataBase_BUFF[i].GPA);

			    for(j = 0 ; j < 5 ; j++ )
			    {
			    	DPRINTF("\nCourse %d ID : %d ", j+1 , DataBase_BUFF[i].Course_ID[j]);
			    }
			    flag = 1;
				break;
			}
		}

	}

	if( flag == 0)
	{
		DPRINTF("\n[ERROR] This Course ID %d Is Not Found",CourseID_ToFind);
		return;
	}

}
void FindBy_FirstName()
{
	char Name_ToFind[50];
	int i , j, result = RESULT_NOT_FOUND;

	DPRINTF("\nEnter The First Name Of The Student:");
	scanf("%s",Name_ToFind);

	for(i = 0 ; i < DataBase.count ; i++)
	{
		result = strcmp(DataBase_BUFF[i].FirstName, Name_ToFind);
		if(  result == STR_IDENTICAL )
		{
			DPRINTF("\n\t==============The Student Details=============\n");

			DPRINTF("Student First Name: %s \n", DataBase_BUFF[i].FirstName);
			DPRINTF("Student Last Name: %s \n", DataBase_BUFF[i].LastName);
			DPRINTF("Student Roll Number: %d \n", DataBase_BUFF[i].Roll);
			DPRINTF("Student GPA: %f \n", DataBase_BUFF[i].GPA);

		    for(j = 0 ; j < 5 ; j++ )
		    {
		    	DPRINTF("\nCourse %d ID : %d ", j+1 , DataBase_BUFF[i].Course_ID[j]);
		    }

			break;
		}
	}

	if( result != STR_IDENTICAL)
	{
		DPRINTF("\n[ERROR] This First Name %s Is Not Found",Name_ToFind);
		return;
	}

}
void UpdateStudent_Details_ByRoll()
{
	int Roll_ToUpdate, result = RESULT_NOT_FOUND;
	int Updated_Info;
	int i , j;
	char temp_text[10];

	DPRINTF("\nEnter The Roll Number To Update The Entry:");
	scanf("%d",&Roll_ToUpdate);

	for(i = 0 ; i < DataBase.count ; i++)
	{
		result = DataBase_BUFF[i].Roll == Roll_ToUpdate;
		if( result == RESULT_FOUND )
		{
			DPRINTF("\n\t==============The Student Details=============\n");

			DPRINTF("Student First Name: %s \n", DataBase_BUFF[i].FirstName);
			DPRINTF("Student Last Name: %s \n", DataBase_BUFF[i].LastName);
			DPRINTF("Student Roll Number: %d \n", DataBase_BUFF[i].Roll);
			DPRINTF("Student GPA: %f \n", DataBase_BUFF[i].GPA);

		    for(j = 0 ; j < 5 ; j++ )
		    {
		    	DPRINTF("\nCourse %d ID : %d ", i+1 , DataBase_BUFF[i].Course_ID[j]);
		    }

			break;
		}
	}

	if( result == RESULT_NOT_FOUND )
	{
		DPRINTF("\n[ERROR] This Roll Number %d Is Not Found",Roll_ToUpdate);
		return;
	}


	DPRINTF("\n=================Choose INFO To Update=================");
	DPRINTF("\n(1)First Name");
	DPRINTF("\n(2)Last Name");
	DPRINTF("\n(3)GPA");
	DPRINTF("\n(4)Registered Courses");
	DPRINTF("\nOption: ");
    scanf("%d",&Updated_Info);

    switch(Updated_Info)
    {
    case 1:
    	DPRINTF("\nEnter The New First Name: ");
    	scanf("%s",DataBase_BUFF[i].FirstName);

    	DPRINTF("\n[INFO] UPDATED SUCCESSFULLY");
    	break;
    case 2:
    	DPRINTF("\nEnter The New Last Name:");
    	scanf("%s",DataBase_BUFF[i].LastName);

    	DPRINTF("\n[INFO] UPDATED SUCCESSFULLY");
    	break;
    case 3:
    	DPRINTF("\nEnter The New GPA:");
    	scanf("%f",&DataBase_BUFF[i].GPA);

    	DPRINTF("\n[INFO] UPDATED SUCCESSFULLY");
    	break;
    case 4:

    	DPRINTF("\nEnter The New Courses IDs:");
        for(j = 0 ; j < 5 ; j++ )
        {
        	DPRINTF("\nCourse %d ID : ", j+1 );

        	gets(temp_text);
        	DataBase_BUFF[i].Course_ID[j] = atoi(temp_text);
        }
        DPRINTF("\n[INFO] UPDATED SUCCESSFULLY");
    	break;
    default:
    	DPRINTF("\n[ERROR] Enter Right Option Please");
    }

}

