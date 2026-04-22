################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/application/acu_lv_app_state_manager.c 

OBJS += \
./Core/application/acu_lv_app_state_manager.o 

C_DEPS += \
./Core/application/acu_lv_app_state_manager.d 


# Each subdirectory must supply rules for building sources it contributes
Core/application/%.o Core/application/%.su Core/application/%.cyclo: ../Core/application/%.c Core/application/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H753xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Core/application -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Core/application/tasks -I../Core/config/acu_lv -I../Core/config/can -I../Core/service/acu_lv -I../Core/driver/acu_lv -I../Core/common -I../Core/service/bms -I../Core/shared/application/tasks -I../Core/shared/driver/can -I../Core/shared/service/can -I../Core/shared/config/can -I../Core/shared/data/accumulator -I../Core/shared/service/accumulator -I../Core/shared/data/rco -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-application

clean-Core-2f-application:
	-$(RM) ./Core/application/acu_lv_app_state_manager.cyclo ./Core/application/acu_lv_app_state_manager.d ./Core/application/acu_lv_app_state_manager.o ./Core/application/acu_lv_app_state_manager.su

.PHONY: clean-Core-2f-application

