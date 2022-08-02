################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Led_Toggle.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Led_Toggle.list \

OBJCOPY_HEX += \
Led_Toggle.hex \

OBJCOPY_BIN += \
Led_Toggle.bin \


# All Target
all: Led_Toggle.elf secondary-outputs

# Tool invocations
Led_Toggle.elf: $(OBJS) $(USER_OBJS) C:\Users\Abdel\OneDrive\Documents\EmbeddedSystemsInDepth\STM32CUBE_IDE_Diploma_Workspace\Lesson1\Led_Toggle\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -o "Led_Toggle.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\Abdel\OneDrive\Documents\EmbeddedSystemsInDepth\STM32CUBE_IDE_Diploma_Workspace\Lesson1\Led_Toggle\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Led_Toggle.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Led_Toggle.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Led_Toggle.list"
	@echo 'Finished building: $@'
	@echo ' '

Led_Toggle.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "Led_Toggle.hex"
	@echo 'Finished building: $@'
	@echo ' '

Led_Toggle.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Led_Toggle.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
