/*
 * Session07_SVC_PendSV Exceptions.c
 *
 *  Created on: Mar 24, 2023
 *      Author: Abdelaziz Maher
 */

#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


#include"Stm32f103x6.h"
#include "OS_Scheduler.h"

sOS_Task_ControlBlock TCB_Task1 , TCB_Task2 , TCB_Task3;

void Task1()
{
	while(1)
	{
		//Task1 Code
	}
}

void Task2()
{
	while(1)
	{
		//Task2 Code
	}
}

void Task3()
{
	while(1)
	{
		//Task3 Code
	}
}

int main(void)
{
	eOS_ErrorState err = NOERROR;

	// HW_Init (Initialize clock tree , Reset controller)

	// Init OS
	if( MYRTOS_Init() != NOERROR )
		while(1);

	//Configure Task1
	strcpy( TCB_Task1.TaskName , "Task1" );
	TCB_Task1.Priority = 3;
	TCB_Task1.pTaskEntry = Task1;
	TCB_Task1.Stack_Size = 1024;

	//Configure Task2
	strcpy( TCB_Task2.TaskName , "Task2" );
	TCB_Task2.Priority = 3;
	TCB_Task2.pTaskEntry = Task2;
	TCB_Task2.Stack_Size = 1024;

	//Configure Task3
	strcpy( TCB_Task3.TaskName , "Task3" );
	TCB_Task3.Priority = 3;
	TCB_Task3.pTaskEntry = Task3;
	TCB_Task3.Stack_Size = 1024;

	err += MYRTOS_CreateTask(&TCB_Task1);
	err += MYRTOS_CreateTask(&TCB_Task2);
	err += MYRTOS_CreateTask(&TCB_Task3);


	while(1)
	{

	}
	return 0;
}


