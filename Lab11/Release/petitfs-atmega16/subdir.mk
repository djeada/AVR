################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../petitfs-atmega16/mmc.c \
../petitfs-atmega16/pff.c \
../petitfs-atmega16/spi.c 

OBJS += \
./petitfs-atmega16/mmc.o \
./petitfs-atmega16/pff.o \
./petitfs-atmega16/spi.o 

C_DEPS += \
./petitfs-atmega16/mmc.d \
./petitfs-atmega16/pff.d \
./petitfs-atmega16/spi.d 


# Each subdirectory must supply rules for building sources it contributes
petitfs-atmega16/%.o: ../petitfs-atmega16/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=11059200UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


