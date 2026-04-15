################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/service/can/can_svc.c \
../Core/service/can/ucr_03.c 

OBJS += \
./Core/service/can/can_svc.o \
./Core/service/can/ucr_03.o 

C_DEPS += \
./Core/service/can/can_svc.d \
./Core/service/can/ucr_03.d 


# Each subdirectory must supply rules for building sources it contributes
Core/service/can/%.o Core/service/can/%.su Core/service/can/%.cyclo: ../Core/service/can/%.c Core/service/can/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H753xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Core/application -I../Core/data -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Core/application/tasks -I../Core/config/acu_lv -I../Core/config/can -I../Core/service/acu_lv -I../Core/driver/acu_lv -I../Core/service/can -I../Core/driver/can -I../Core/common -I../Core/service/bms -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-service-2f-can

clean-Core-2f-service-2f-can:
	-$(RM) ./Core/service/can/can_svc.cyclo ./Core/service/can/can_svc.d ./Core/service/can/can_svc.o ./Core/service/can/can_svc.su ./Core/service/can/ucr_03.cyclo ./Core/service/can/ucr_03.d ./Core/service/can/ucr_03.o ./Core/service/can/ucr_03.su

.PHONY: clean-Core-2f-service-2f-can

