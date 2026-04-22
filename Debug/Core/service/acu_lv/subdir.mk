################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/service/acu_lv/acu_lv_svc_accu.c \
../Core/service/acu_lv/acu_lv_svc_adbms6830.c \
../Core/service/acu_lv/acu_lv_svc_air.c \
../Core/service/acu_lv/acu_lv_svc_cell_voltage.c \
../Core/service/acu_lv/acu_lv_svc_imd.c \
../Core/service/acu_lv/acu_lv_svc_precharge.c \
../Core/service/acu_lv/acu_lv_svc_sdc.c \
../Core/service/acu_lv/acu_lv_svc_shunt.c \
../Core/service/acu_lv/acu_lv_svc_ts.c 

OBJS += \
./Core/service/acu_lv/acu_lv_svc_accu.o \
./Core/service/acu_lv/acu_lv_svc_adbms6830.o \
./Core/service/acu_lv/acu_lv_svc_air.o \
./Core/service/acu_lv/acu_lv_svc_cell_voltage.o \
./Core/service/acu_lv/acu_lv_svc_imd.o \
./Core/service/acu_lv/acu_lv_svc_precharge.o \
./Core/service/acu_lv/acu_lv_svc_sdc.o \
./Core/service/acu_lv/acu_lv_svc_shunt.o \
./Core/service/acu_lv/acu_lv_svc_ts.o 

C_DEPS += \
./Core/service/acu_lv/acu_lv_svc_accu.d \
./Core/service/acu_lv/acu_lv_svc_adbms6830.d \
./Core/service/acu_lv/acu_lv_svc_air.d \
./Core/service/acu_lv/acu_lv_svc_cell_voltage.d \
./Core/service/acu_lv/acu_lv_svc_imd.d \
./Core/service/acu_lv/acu_lv_svc_precharge.d \
./Core/service/acu_lv/acu_lv_svc_sdc.d \
./Core/service/acu_lv/acu_lv_svc_shunt.d \
./Core/service/acu_lv/acu_lv_svc_ts.d 


# Each subdirectory must supply rules for building sources it contributes
Core/service/acu_lv/%.o Core/service/acu_lv/%.su Core/service/acu_lv/%.cyclo: ../Core/service/acu_lv/%.c Core/service/acu_lv/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H753xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Core/application -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Core/application/tasks -I../Core/config/acu_lv -I../Core/config/can -I../Core/service/acu_lv -I../Core/driver/acu_lv -I../Core/common -I../Core/service/bms -I../Core/shared/application/tasks -I../Core/shared/driver/can -I../Core/shared/service/can -I../Core/shared/config/can -I../Core/shared/data/accumulator -I../Core/shared/service/accumulator -I../Core/shared/data/rco -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-service-2f-acu_lv

clean-Core-2f-service-2f-acu_lv:
	-$(RM) ./Core/service/acu_lv/acu_lv_svc_accu.cyclo ./Core/service/acu_lv/acu_lv_svc_accu.d ./Core/service/acu_lv/acu_lv_svc_accu.o ./Core/service/acu_lv/acu_lv_svc_accu.su ./Core/service/acu_lv/acu_lv_svc_adbms6830.cyclo ./Core/service/acu_lv/acu_lv_svc_adbms6830.d ./Core/service/acu_lv/acu_lv_svc_adbms6830.o ./Core/service/acu_lv/acu_lv_svc_adbms6830.su ./Core/service/acu_lv/acu_lv_svc_air.cyclo ./Core/service/acu_lv/acu_lv_svc_air.d ./Core/service/acu_lv/acu_lv_svc_air.o ./Core/service/acu_lv/acu_lv_svc_air.su ./Core/service/acu_lv/acu_lv_svc_cell_voltage.cyclo ./Core/service/acu_lv/acu_lv_svc_cell_voltage.d ./Core/service/acu_lv/acu_lv_svc_cell_voltage.o ./Core/service/acu_lv/acu_lv_svc_cell_voltage.su ./Core/service/acu_lv/acu_lv_svc_imd.cyclo ./Core/service/acu_lv/acu_lv_svc_imd.d ./Core/service/acu_lv/acu_lv_svc_imd.o ./Core/service/acu_lv/acu_lv_svc_imd.su ./Core/service/acu_lv/acu_lv_svc_precharge.cyclo ./Core/service/acu_lv/acu_lv_svc_precharge.d ./Core/service/acu_lv/acu_lv_svc_precharge.o ./Core/service/acu_lv/acu_lv_svc_precharge.su ./Core/service/acu_lv/acu_lv_svc_sdc.cyclo ./Core/service/acu_lv/acu_lv_svc_sdc.d ./Core/service/acu_lv/acu_lv_svc_sdc.o ./Core/service/acu_lv/acu_lv_svc_sdc.su ./Core/service/acu_lv/acu_lv_svc_shunt.cyclo ./Core/service/acu_lv/acu_lv_svc_shunt.d ./Core/service/acu_lv/acu_lv_svc_shunt.o ./Core/service/acu_lv/acu_lv_svc_shunt.su ./Core/service/acu_lv/acu_lv_svc_ts.cyclo ./Core/service/acu_lv/acu_lv_svc_ts.d ./Core/service/acu_lv/acu_lv_svc_ts.o ./Core/service/acu_lv/acu_lv_svc_ts.su

.PHONY: clean-Core-2f-service-2f-acu_lv

