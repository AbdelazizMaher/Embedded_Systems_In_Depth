################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/Src/Stm32f103c6_EXTI_Driver.c \
../MCAL/Src/Stm32f103c6_GPIO_Driver.c \
../MCAL/Src/Stm32f103c6_I2C_Driver.c \
../MCAL/Src/Stm32f103c6_RCC_Driver.c \
../MCAL/Src/Stm32f103c6_SPI_Driver.c \
../MCAL/Src/Stm32f103c6_USART_Driver.c 

OBJS += \
./MCAL/Src/Stm32f103c6_EXTI_Driver.o \
./MCAL/Src/Stm32f103c6_GPIO_Driver.o \
./MCAL/Src/Stm32f103c6_I2C_Driver.o \
./MCAL/Src/Stm32f103c6_RCC_Driver.o \
./MCAL/Src/Stm32f103c6_SPI_Driver.o \
./MCAL/Src/Stm32f103c6_USART_Driver.o 

C_DEPS += \
./MCAL/Src/Stm32f103c6_EXTI_Driver.d \
./MCAL/Src/Stm32f103c6_GPIO_Driver.d \
./MCAL/Src/Stm32f103c6_I2C_Driver.d \
./MCAL/Src/Stm32f103c6_RCC_Driver.d \
./MCAL/Src/Stm32f103c6_SPI_Driver.d \
./MCAL/Src/Stm32f103c6_USART_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/Src/%.o MCAL/Src/%.su: ../MCAL/Src/%.c MCAL/Src/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit15_Create_Your_Own_RTOS/Create_Your_Own_RTOS/MY_RTOS/MCAL/Inc" -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit15_Create_Your_Own_RTOS/Create_Your_Own_RTOS/MY_RTOS/MYxx_RTOS/Inc" -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit15_Create_Your_Own_RTOS/Create_Your_Own_RTOS/MY_RTOS/HAL/SevenSegment" -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit15_Create_Your_Own_RTOS/Create_Your_Own_RTOS/MY_RTOS/HAL/KeyPad" -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit15_Create_Your_Own_RTOS/Create_Your_Own_RTOS/MY_RTOS/HAL/LCD" -I../Inc -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit15_Create_Your_Own_RTOS/Create_Your_Own_RTOS/MY_RTOS/HAL/EEPROM" -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/STM32CUBE_IDE_Diploma_Workspace/Unit15_Create_Your_Own_RTOS/Create_Your_Own_RTOS/MY_RTOS/CMSIS_V5" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MCAL-2f-Src

clean-MCAL-2f-Src:
	-$(RM) ./MCAL/Src/Stm32f103c6_EXTI_Driver.d ./MCAL/Src/Stm32f103c6_EXTI_Driver.o ./MCAL/Src/Stm32f103c6_EXTI_Driver.su ./MCAL/Src/Stm32f103c6_GPIO_Driver.d ./MCAL/Src/Stm32f103c6_GPIO_Driver.o ./MCAL/Src/Stm32f103c6_GPIO_Driver.su ./MCAL/Src/Stm32f103c6_I2C_Driver.d ./MCAL/Src/Stm32f103c6_I2C_Driver.o ./MCAL/Src/Stm32f103c6_I2C_Driver.su ./MCAL/Src/Stm32f103c6_RCC_Driver.d ./MCAL/Src/Stm32f103c6_RCC_Driver.o ./MCAL/Src/Stm32f103c6_RCC_Driver.su ./MCAL/Src/Stm32f103c6_SPI_Driver.d ./MCAL/Src/Stm32f103c6_SPI_Driver.o ./MCAL/Src/Stm32f103c6_SPI_Driver.su ./MCAL/Src/Stm32f103c6_USART_Driver.d ./MCAL/Src/Stm32f103c6_USART_Driver.o ./MCAL/Src/Stm32f103c6_USART_Driver.su

.PHONY: clean-MCAL-2f-Src

