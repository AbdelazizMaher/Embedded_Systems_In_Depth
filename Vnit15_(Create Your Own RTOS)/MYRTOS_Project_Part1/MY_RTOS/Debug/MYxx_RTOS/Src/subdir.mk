################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MYxx_RTOS/Src/CortexMx_OS_Porting.c \
../MYxx_RTOS/Src/OS_Queue.c \
../MYxx_RTOS/Src/OS_Scheduler.c 

OBJS += \
./MYxx_RTOS/Src/CortexMx_OS_Porting.o \
./MYxx_RTOS/Src/OS_Queue.o \
./MYxx_RTOS/Src/OS_Scheduler.o 

C_DEPS += \
./MYxx_RTOS/Src/CortexMx_OS_Porting.d \
./MYxx_RTOS/Src/OS_Queue.d \
./MYxx_RTOS/Src/OS_Scheduler.d 


# Each subdirectory must supply rules for building sources it contributes
MYxx_RTOS/Src/%.o MYxx_RTOS/Src/%.su: ../MYxx_RTOS/Src/%.c MYxx_RTOS/Src/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit15_Create_Your_Own_RTOS/Create_Your_Own_RTOS/MY_RTOS/MCAL/Inc" -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit15_Create_Your_Own_RTOS/Create_Your_Own_RTOS/MY_RTOS/MYxx_RTOS/Inc" -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit15_Create_Your_Own_RTOS/Create_Your_Own_RTOS/MY_RTOS/HAL/SevenSegment" -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit15_Create_Your_Own_RTOS/Create_Your_Own_RTOS/MY_RTOS/HAL/KeyPad" -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit15_Create_Your_Own_RTOS/Create_Your_Own_RTOS/MY_RTOS/HAL/LCD" -I../Inc -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit15_Create_Your_Own_RTOS/Create_Your_Own_RTOS/MY_RTOS/HAL/EEPROM" -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit15_Create_Your_Own_RTOS/Create_Your_Own_RTOS/MY_RTOS/CMSIS_V5" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MYxx_RTOS-2f-Src

clean-MYxx_RTOS-2f-Src:
	-$(RM) ./MYxx_RTOS/Src/CortexMx_OS_Porting.d ./MYxx_RTOS/Src/CortexMx_OS_Porting.o ./MYxx_RTOS/Src/CortexMx_OS_Porting.su ./MYxx_RTOS/Src/OS_Queue.d ./MYxx_RTOS/Src/OS_Queue.o ./MYxx_RTOS/Src/OS_Queue.su ./MYxx_RTOS/Src/OS_Scheduler.d ./MYxx_RTOS/Src/OS_Scheduler.o ./MYxx_RTOS/Src/OS_Scheduler.su

.PHONY: clean-MYxx_RTOS-2f-Src

