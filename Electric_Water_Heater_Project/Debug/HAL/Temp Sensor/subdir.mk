################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/Temp\ Sensor/LM35.c 

OBJS += \
./HAL/Temp\ Sensor/LM35.o 

C_DEPS += \
./HAL/Temp\ Sensor/LM35.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/Temp\ Sensor/LM35.o: ../HAL/Temp\ Sensor/LM35.c HAL/Temp\ Sensor/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"HAL/Temp Sensor/LM35.d" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


