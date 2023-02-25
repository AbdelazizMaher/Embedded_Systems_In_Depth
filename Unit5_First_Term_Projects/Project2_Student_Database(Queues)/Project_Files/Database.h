/*
 * Database.h
 *
 *  Created on: Feb 22, 2023
 *      Author: Abdel
 */

#ifndef DATABASE_H_
#define DATABASE_H_


#define UNVALID_POS          -1
#define UNVALID_ID           -2

#define RESULT_NOT_FOUND      0
#define RESULT_FOUND          1

#define STR_IDENTICAL         0

#define DATA_EXIST            1

int Init_DataBaseQueue();
void AddStudent_From_File();
void AddStudent_Manually();
void DeleteStudent_ByRoll();
void ViewStudents();
void TotalStudents();
void FindBy_Roll();
void FindBy_CourseID();
void FindBy_FirstName();
void UpdateStudent_Details_ByRoll();

#endif /* DATABASE_H_ */
