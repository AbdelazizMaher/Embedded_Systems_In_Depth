################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Session07_SVC_PendSV\ Exceptions.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/Session07_SVC_PendSV\ Exceptions.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/Session07_SVC_PendSV\ Exceptions.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Session07_SVC_PendSV\ Exceptions.o: ../Src/Session07_SVC_PendSV\ Exceptions.c Src/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit14_ARM_CORTEX(M3-M4)/ARM/ARM_CortexM3_M4/MCAL/Inc" -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit14_ARM_CORTEX(M3-M4)/ARM/ARM_CortexM3_M4/HAL/SevenSegment" -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit14_ARM_CORTEX(M3-M4)/ARM/ARM_CortexM3_M4/HAL/KeyPad" -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit14_ARM_CORTEX(M3-M4)/ARM/ARM_CortexM3_M4/HAL/LCD" -I../Inc -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit14_ARM_CORTEX(M3-M4)/ARM/ARM_CortexM3_M4/HAL/EEPROM" -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit14_ARM_CORTEX(M3-M4)/ARM/ARM_CortexM3_M4/CMSIS_V5" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/Session07_SVC_PendSV Exceptions.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit14_ARM_CORTEX(M3-M4)/ARM/ARM_CortexM3_M4/MCAL/Inc" -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit14_ARM_CORTEX(M3-M4)/ARM/ARM_CortexM3_M4/HAL/SevenSegment" -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit14_ARM_CORTEX(M3-M4)/ARM/ARM_CortexM3_M4/HAL/KeyPad" -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit14_ARM_CORTEX(M3-M4)/ARM/ARM_CortexM3_M4/HAL/LCD" -I../Inc -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit14_ARM_CORTEX(M3-M4)/ARM/ARM_CortexM3_M4/HAL/EEPROM" -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit14_ARM_CORTEX(M3-M4)/ARM/ARM_CortexM3_M4/CMSIS_V5" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/Session07_SVC_PendSV\ Exceptions.d ./Src/Session07_SVC_PendSV\ Exceptions.o ./Src/Session07_SVC_PendSV\ Exceptions.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

