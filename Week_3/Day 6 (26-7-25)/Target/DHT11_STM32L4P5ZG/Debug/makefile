################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
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

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := DHT11_STM32L4P5ZG
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
DHT11_STM32L4P5ZG.elf \

MAP_FILES += \
DHT11_STM32L4P5ZG.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
DHT11_STM32L4P5ZG.list \


# All Target
all: main-build

# Main-build Target
main-build: DHT11_STM32L4P5ZG.elf secondary-outputs

# Tool invocations
DHT11_STM32L4P5ZG.elf DHT11_STM32L4P5ZG.map: $(OBJS) $(USER_OBJS) C:\Users\prath\OneDrive\Desktop\MINI\ PROJECT\Sem\ 5\ Project\Week_3\Day\ 6\ (26-7-25)\Target\DHT11_STM32L4P5ZG\STM32L4P5ZGTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "DHT11_STM32L4P5ZG.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\prath\OneDrive\Desktop\MINI PROJECT\Sem 5 Project\Week_3\Day 6 (26-7-25)\Target\DHT11_STM32L4P5ZG\STM32L4P5ZGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="DHT11_STM32L4P5ZG.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

DHT11_STM32L4P5ZG.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "DHT11_STM32L4P5ZG.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) DHT11_STM32L4P5ZG.elf DHT11_STM32L4P5ZG.list DHT11_STM32L4P5ZG.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
