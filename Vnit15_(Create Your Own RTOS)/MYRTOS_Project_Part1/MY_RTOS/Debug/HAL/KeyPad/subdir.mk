################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/KeyPad/keypad.c 

OBJS += \
./HAL/KeyPad/keypad.o 

C_DEPS += \
./HAL/KeyPad/keypad.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/KeyPad/%.o HAL/KeyPad/%.su: ../HAL/KeyPad/%.c HAL/KeyPad/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit15_Create_Your_Own_RTOS/Create_Your_Own_RTOS/MY_RTOS/MCAL/Inc" -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit15_Create_Your_Own_RTOS/Create_Your_Own_RTOS/MY_RTOS/MYxx_RTOS/Inc" -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit15_Create_Your_Own_RTOS/Create_Your_Own_RTOS/MY_RTOS/HAL/SevenSegment" -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit15_Create_Your_Own_RTOS/Create_Your_Own_RTOS/MY_RTOS/HAL/KeyPad" -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit15_Create_Your_Own_RTOS/Create_Your_Own_RTOS/MY_RTOS/HAL/LCD" -I../Inc -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit15_Create_Your_Own_RTOS/Create_Your_Own_RTOS/MY_RTOS/HAL/EEPROM" -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit15_Create_Your_Own_RTOS/Create_Your_Own_RTOS/MY_RTOS/CMSIS_V5" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-HAL-2f-KeyPad

clean-HAL-2f-KeyPad:
	-$(RM) ./HAL/KeyPad/keypad.d ./HAL/KeyPad/keypad.o ./HAL/KeyPad/keypad.su

.PHONY: clean-HAL-2f-KeyPad

