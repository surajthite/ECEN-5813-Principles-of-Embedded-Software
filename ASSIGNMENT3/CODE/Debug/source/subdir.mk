################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/RGBled.c \
../source/System.c \
../source/logger.c \
../source/main.c \
../source/memory.c \
../source/mtb.c \
../source/pattern.c \
../source/semihost_hardfault.c \
../source/unitTest.c 

OBJS += \
./source/RGBled.o \
./source/System.o \
./source/logger.o \
./source/main.o \
./source/memory.o \
./source/mtb.o \
./source/pattern.o \
./source/semihost_hardfault.o \
./source/unitTest.o 

C_DEPS += \
./source/RGBled.d \
./source/System.d \
./source/logger.d \
./source/main.d \
./source/memory.d \
./source/mtb.d \
./source/pattern.d \
./source/semihost_hardfault.d \
./source/unitTest.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I../board -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../startup -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


