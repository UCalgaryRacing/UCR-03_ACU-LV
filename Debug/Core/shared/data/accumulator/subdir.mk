################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/shared/data/accumulator/acu_data.c 

OBJS += \
./Core/shared/data/accumulator/acu_data.o 

C_DEPS += \
./Core/shared/data/accumulator/acu_data.d 


# Each subdirectory must supply rules for building sources it contributes
Core/shared/data/accumulator/%.o Core/shared/data/accumulator/%.su Core/shared/data/accumulator/%.cyclo: ../Core/shared/data/accumulator/%.c Core/shared/data/accumulator/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H753xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Core/application -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Core/application/tasks -I../Core/config/acu_lv -I../Core/config/can -I../Core/service/acu_lv -I../Core/driver/acu_lv -I../Core/common -I../Core/service/bms -I../Core/shared/application/tasks -I../Core/shared/driver/can -I../Core/shared/service/can -I../Core/shared/config/can -I../Core/shared/data/accumulator -I../Core/shared/service/accumulator -I../Core/shared/data/rco -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-shared-2f-data-2f-accumulator

clean-Core-2f-shared-2f-data-2f-accumulator:
	-$(RM) ./Core/shared/data/accumulator/acu_data.cyclo ./Core/shared/data/accumulator/acu_data.d ./Core/shared/data/accumulator/acu_data.o ./Core/shared/data/accumulator/acu_data.su

.PHONY: clean-Core-2f-shared-2f-data-2f-accumulator

