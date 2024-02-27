################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/USART\ Driver/USART_program.c 

OBJS += \
./Src/MCAL/USART\ Driver/USART_program.o 

C_DEPS += \
./Src/MCAL/USART\ Driver/USART_program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/USART\ Driver/USART_program.o: ../Src/MCAL/USART\ Driver/USART_program.c Src/MCAL/USART\ Driver/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Src/MCAL/USART Driver/USART_program.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-USART-20-Driver

clean-Src-2f-MCAL-2f-USART-20-Driver:
	-$(RM) ./Src/MCAL/USART\ Driver/USART_program.cyclo ./Src/MCAL/USART\ Driver/USART_program.d ./Src/MCAL/USART\ Driver/USART_program.o ./Src/MCAL/USART\ Driver/USART_program.su

.PHONY: clean-Src-2f-MCAL-2f-USART-20-Driver

