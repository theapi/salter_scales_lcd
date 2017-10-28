################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/gpio.c \
../Src/lcd.c \
../Src/main.c \
../Src/screen.c \
../Src/stm32l0xx_hal_msp.c \
../Src/stm32l0xx_it.c \
../Src/system_stm32l0xx.c \
../Src/usart.c 

OBJS += \
./Src/gpio.o \
./Src/lcd.o \
./Src/main.o \
./Src/screen.o \
./Src/stm32l0xx_hal_msp.o \
./Src/stm32l0xx_it.o \
./Src/system_stm32l0xx.o \
./Src/usart.o 

C_DEPS += \
./Src/gpio.d \
./Src/lcd.d \
./Src/main.d \
./Src/screen.d \
./Src/stm32l0xx_hal_msp.d \
./Src/stm32l0xx_it.d \
./Src/system_stm32l0xx.d \
./Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L053xx -I"/home/peter/repos/salter_scales_lcd/scales/Inc" -I"/home/peter/repos/salter_scales_lcd/scales/Drivers/STM32L0xx_HAL_Driver/Inc" -I"/home/peter/repos/salter_scales_lcd/scales/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"/home/peter/repos/salter_scales_lcd/scales/Drivers/CMSIS/Device/ST/STM32L0xx/Include" -I"/home/peter/repos/salter_scales_lcd/scales/Drivers/CMSIS/Include" -I"/home/peter/repos/salter_scales_lcd/scales/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


