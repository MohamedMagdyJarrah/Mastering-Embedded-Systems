################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/RCC\ Driver/RCC_program.c 

OBJS += \
./Src/MCAL/RCC\ Driver/RCC_program.o 

C_DEPS += \
./Src/MCAL/RCC\ Driver/RCC_program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/RCC\ Driver/RCC_program.o: ../Src/MCAL/RCC\ Driver/RCC_program.c Src/MCAL/RCC\ Driver/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Src/MCAL/RCC Driver/RCC_program.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-RCC-20-Driver

clean-Src-2f-MCAL-2f-RCC-20-Driver:
	-$(RM) ./Src/MCAL/RCC\ Driver/RCC_program.cyclo ./Src/MCAL/RCC\ Driver/RCC_program.d ./Src/MCAL/RCC\ Driver/RCC_program.o ./Src/MCAL/RCC\ Driver/RCC_program.su

.PHONY: clean-Src-2f-MCAL-2f-RCC-20-Driver

