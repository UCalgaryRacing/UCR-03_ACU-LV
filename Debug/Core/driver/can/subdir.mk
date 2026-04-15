################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/driver/can/can_drv.c 

OBJS += \
./Core/driver/can/can_drv.o 

C_DEPS += \
./Core/driver/can/can_drv.d 


# Each subdirectory must supply rules for building sources it contributes
Core/driver/can/%.o Core/driver/can/%.su Core/driver/can/%.cyclo: ../Core/driver/can/%.c Core/driver/can/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H753xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Core/application -I../Core/data -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Core/application/tasks -I../Core/config/acu_lv -I../Core/config/can -I../Core/service/acu_lv -I../Core/driver/acu_lv -I../Core/service/can -I../Core/driver/can -I../Core/common -I../Core/service/bms -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-driver-2f-can

clean-Core-2f-driver-2f-can:
	-$(RM) ./Core/driver/can/can_drv.cyclo ./Core/driver/can/can_drv.d ./Core/driver/can/can_drv.o ./Core/driver/can/can_drv.su

.PHONY: clean-Core-2f-driver-2f-can

