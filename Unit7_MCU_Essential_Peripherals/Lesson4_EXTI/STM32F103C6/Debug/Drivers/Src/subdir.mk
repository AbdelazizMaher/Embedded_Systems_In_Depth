################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Src/Stm32f103c6_EXTI_Driver.c \
../Drivers/Src/Stm32f103c6_GPIO_Driver.c 

OBJS += \
./Drivers/Src/Stm32f103c6_EXTI_Driver.o \
./Drivers/Src/Stm32f103c6_GPIO_Driver.o 

C_DEPS += \
./Drivers/Src/Stm32f103c6_EXTI_Driver.d \
./Drivers/Src/Stm32f103c6_GPIO_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Src/%.o Drivers/Src/%.su: ../Drivers/Src/%.c Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I"C:/Users/Abdel/OneDrive/Documents/EmbeddedSystemsInDepth/Drivers/Stm32f103xx/STM32F103C6/Drivers/Inc" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-Src

clean-Drivers-2f-Src:
	-$(RM) ./Drivers/Src/Stm32f103c6_EXTI_Driver.d ./Drivers/Src/Stm32f103c6_EXTI_Driver.o ./Drivers/Src/Stm32f103c6_EXTI_Driver.su ./Drivers/Src/Stm32f103c6_GPIO_Driver.d ./Drivers/Src/Stm32f103c6_GPIO_Driver.o ./Drivers/Src/Stm32f103c6_GPIO_Driver.su

.PHONY: clean-Drivers-2f-Src

