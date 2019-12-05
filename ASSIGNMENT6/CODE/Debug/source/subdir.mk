################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/adc_dac.c \
../source/circularbuff.c \
../source/dma.c \
../source/logger.c \
../source/main.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/task1.c \
../source/time_stamp.c \
../source/wave.c 

OBJS += \
./source/adc_dac.o \
./source/circularbuff.o \
./source/dma.o \
./source/logger.o \
./source/main.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/task1.o \
./source/time_stamp.o \
./source/wave.o 

C_DEPS += \
./source/adc_dac.d \
./source/circularbuff.d \
./source/dma.d \
./source/logger.d \
./source/main.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/task1.d \
./source/time_stamp.d \
./source/wave.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I../board -I../source -I../ -I../freertos -I../drivers -I../CMSIS -I../utilities -I../startup -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


