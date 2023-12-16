/*
 * CortexMx_OS_Porting.h
 *
 *  Created on: Dec 13, 2023
 *      Author: Abdelaziz Maher
 */

#ifndef INC_CORTEXMX_OS_PORTING_H_
#define INC_CORTEXMX_OS_PORTING_H_

#include "core_cm3.h"

extern int _estack;
extern int _eheap;
#define MainStackSize 3072

#define OS_SwitchCPU_AccessLevel_privileged() 		  __asm volatile(" mrs r3,CONTROL \n\t  lsr r3,r3,#0x1 \n\t  lsl r3,r3,#0x1 \n\t  msr CONTROL,r3")
#define OS_SwitchCPU_AccessLevel_unprivileged()       __asm volatile(" mrs r3,CONTROL \n\t  orr r3,r3,#0x1 \n\t  msr CONTROL,r3")

#define OS_SetPSP(Addr)                               __asm volatile(" msr PSP,%[in] " : :[in] "r" (Addr) )
#define OS_GetPSP(Addr)                               __asm volatile(" mrs %[out],PSP " : [out] "=r" (Addr) )
#define OS_SwitchSP_ToPSP()                           __asm volatile(" mrs r3,CONTROL \n\t  orr r3,r3,#0x02 \n\t  msr CONTROL,r3")
#define OS_SwitchSP_ToMSP()                           __asm volatile(" mrs r3,CONTROL \n\t  and r3,r3,#0x05 \n\t  msr CONTROL,r3")

void OS_SVC_Set(int SVC_ID);
void OS_SVC_Services(int* StackFramePointer );
void OS_SVC(unsigned char SVC_Number);

#endif /* INC_CORTEXMX_OS_PORTING_H_ */
