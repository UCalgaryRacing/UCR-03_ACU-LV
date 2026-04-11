################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/application/tasks/can_task.c \
../Core/application/tasks/fast_task.c \
../Core/application/tasks/medium_task.c \
../Core/application/tasks/slow_task.c \
../Core/application/tasks/task_manager.c 

OBJS += \
./Core/application/tasks/can_task.o \
./Core/application/tasks/fast_task.o \
./Core/application/tasks/medium_task.o \
./Core/application/tasks/slow_task.o \
./Core/application/tasks/task_manager.o 

C_DEPS += \
./Core/application/tasks/can_task.d \
./Core/application/tasks/fast_task.d \
./Core/application/tasks/medium_task.d \
./Core/application/tasks/slow_task.d \
./Core/application/tasks/task_manager.d 


# Each subdirectory must supply rules for building sources it contributes
Core/application/tasks/%.o Core/application/tasks/%.su Core/application/tasks/%.cyclo: ../Core/application/tasks/%.c Core/application/tasks/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H753xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Core/application -I../Core/data -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Core/application/tasks -I../Core/config/acu_lv -I../Core/config/can -I../Core/service/acu_lv -I../Core/driver/acu_lv -I../Core/service/can -I../Core/driver/can -I../Core/common -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-application-2f-tasks

clean-Core-2f-application-2f-tasks:
	-$(RM) ./Core/application/tasks/can_task.cyclo ./Core/application/tasks/can_task.d ./Core/application/tasks/can_task.o ./Core/application/tasks/can_task.su ./Core/application/tasks/fast_task.cyclo ./Core/application/tasks/fast_task.d ./Core/application/tasks/fast_task.o ./Core/application/tasks/fast_task.su ./Core/application/tasks/medium_task.cyclo ./Core/application/tasks/medium_task.d ./Core/application/tasks/medium_task.o ./Core/application/tasks/medium_task.su ./Core/application/tasks/slow_task.cyclo ./Core/application/tasks/slow_task.d ./Core/application/tasks/slow_task.o ./Core/application/tasks/slow_task.su ./Core/application/tasks/task_manager.cyclo ./Core/application/tasks/task_manager.d ./Core/application/tasks/task_manager.o ./Core/application/tasks/task_manager.su

.PHONY: clean-Core-2f-application-2f-tasks

