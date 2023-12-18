/*
 * OS_Scheduler.h
 *
 *  Created on: Dec 13, 2023
 *      Author: Abdelaziz Maher
 */

#ifndef INC_OS_SCHEDULER_H_
#define INC_OS_SCHEDULER_H_

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//         Includes
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#include "CortexMx_OS_Porting.h"
#include "string.h"
#include "stdint.h"


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//  Type Definitions ( structures/enums )
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
typedef enum
{
	NOERROR,
	OS_QUEUE_INIT_ERROR,
	TASK_EXCEED_STACKSIZE
}eOS_ErrorState;

typedef struct
{
	unsigned int Stack_Size;
	unsigned char Priority;
	void (*pTaskEntry)(void);
	unsigned int _S_PSP_Task;
	unsigned int _E_PSP_Task;
	unsigned int* Current_PSP_Location;
	char TaskName[30];
	enum
	{
		TASK_SUSPEND,
		TASK_WAITING,
		TASK_READY,
		TASK_RUNNING
	}eOS_TaskState;
	struct
	{
		enum
		{
			ENABLE_BLOCKING,
			DISABLE_BLOCKING
		}eBlockState;
		unsigned int Blocking_Ticks;
	}sOS_TaskWaiting;
}sOS_Task_ControlBlock;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//  Public function prototypes
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
eOS_ErrorState MYRTOS_Init();
eOS_ErrorState MYRTOS_CreateTask(sOS_Task_ControlBlock* Task_TCB);
eOS_ErrorState MYRTOS_ActivateTask(sOS_Task_ControlBlock* Task_TCB);
eOS_ErrorState MYRTOS_TerminateTask(sOS_Task_ControlBlock* Task_TCB);
void MYRTOS_StartOS();

#endif /* INC_OS_SCHEDULER_H_ */
