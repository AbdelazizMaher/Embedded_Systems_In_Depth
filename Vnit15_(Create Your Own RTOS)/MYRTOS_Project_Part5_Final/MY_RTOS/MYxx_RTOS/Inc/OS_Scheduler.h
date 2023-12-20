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
	TASK_EXCEED_STACKSIZE,
	MUTEX_REACHEDMAXIMUM_NUMBEROF_ACQUIREMENTS
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
			WAITING_DISABLE,
			WAITING_ENABLE
		}eWaitingState;
		unsigned int Waiting_Ticks;
	}sOS_TaskWaiting;
}sOS_Task_ControlBlock;

typedef struct
{
	unsigned char* pPayloadBuffer;
	unsigned int PayloadBuffer_Size;
	sOS_Task_ControlBlock* CurrentMutex_Holder;
	sOS_Task_ControlBlock* NextMutex_Holder;
	char MutexName[30];
}sOS_Mutex_ControlBlock;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//  Public function prototypes
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
eOS_ErrorState MYRTOS_Init();
eOS_ErrorState MYRTOS_CreateTask(sOS_Task_ControlBlock* Task_TCB);
eOS_ErrorState MYRTOS_ActivateTask(sOS_Task_ControlBlock* Task_TCB);
eOS_ErrorState MYRTOS_TerminateTask(sOS_Task_ControlBlock* Task_TCB);
eOS_ErrorState MYRTOS_TaskWait(unsigned int WaitTICKs, sOS_Task_ControlBlock* Task_TCB);
eOS_ErrorState MYRTOS_AcquireMutex(sOS_Mutex_ControlBlock* Mutex_TCB, sOS_Task_ControlBlock* Task_TCB);
void MYRTOS_ReleaseMutex(sOS_Mutex_ControlBlock* Mutex_TCB);

void MYRTOS_StartOS();

#endif /* INC_OS_SCHEDULER_H_ */
