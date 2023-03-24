################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/Src/Stm32f103c6_EXTI_Driver.c \
../MCAL/Src/Stm32f103c6_GPIO_Driver.c 

OBJS += \
./MCAL/Src/Stm32f103c6_EXTI_Driver.o \
./MCAL/Src/Stm32f103c6_GPIO_Driver.o 

C_DEPS += \
./MCAL/Src/Stm32f103c6_EXTI_Driver.d \
./MCAL/Src/Stm32f103c6_GPIO_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/Src/%.o MCAL/Src/%.su: ../MCAL/Src/%.c MCAL/Src/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/Drivers/Stm32f103xx/STM32F103C6/MCAL/Inc" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MCAL-2f-Src

clean-MCAL-2f-Src:
	-$(RM) ./MCAL/Src/Stm32f103c6_EXTI_Driver.d ./MCAL/Src/Stm32f103c6_EXTI_Driver.o ./MCAL/Src/Stm32f103c6_EXTI_Driver.su ./MCAL/Src/Stm32f103c6_GPIO_Driver.d ./MCAL/Src/Stm32f103c6_GPIO_Driver.o ./MCAL/Src/Stm32f103c6_GPIO_Driver.su

.PHONY: clean-MCAL-2f-Src

