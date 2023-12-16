################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit15_Create_Your_Own_RTOS/Create_Your_Own_RTOS/MY_RTOS/MCAL/Inc" -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit15_Create_Your_Own_RTOS/Create_Your_Own_RTOS/MY_RTOS/MYxx_RTOS/Inc" -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit15_Create_Your_Own_RTOS/Create_Your_Own_RTOS/MY_RTOS/HAL/SevenSegment" -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit15_Create_Your_Own_RTOS/Create_Your_Own_RTOS/MY_RTOS/HAL/KeyPad" -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit15_Create_Your_Own_RTOS/Create_Your_Own_RTOS/MY_RTOS/HAL/LCD" -I../Inc -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit15_Create_Your_Own_RTOS/Create_Your_Own_RTOS/MY_RTOS/HAL/EEPROM" -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit15_Create_Your_Own_RTOS/Create_Your_Own_RTOS/MY_RTOS/CMSIS_V5" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

