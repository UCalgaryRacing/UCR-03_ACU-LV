################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/driver/acu_lv/acu_lv_drv_air.c \
../Core/driver/acu_lv/acu_lv_drv_analog.c \
../Core/driver/acu_lv/acu_lv_drv_debug_led.c \
../Core/driver/acu_lv/acu_lv_drv_dfsdm.c \
../Core/driver/acu_lv/acu_lv_drv_imd.c \
../Core/driver/acu_lv/acu_lv_drv_sdc.c 

OBJS += \
./Core/driver/acu_lv/acu_lv_drv_air.o \
./Core/driver/acu_lv/acu_lv_drv_analog.o \
./Core/driver/acu_lv/acu_lv_drv_debug_led.o \
./Core/driver/acu_lv/acu_lv_drv_dfsdm.o \
./Core/driver/acu_lv/acu_lv_drv_imd.o \
./Core/driver/acu_lv/acu_lv_drv_sdc.o 

C_DEPS += \
./Core/driver/acu_lv/acu_lv_drv_air.d \
./Core/driver/acu_lv/acu_lv_drv_analog.d \
./Core/driver/acu_lv/acu_lv_drv_debug_led.d \
./Core/driver/acu_lv/acu_lv_drv_dfsdm.d \
./Core/driver/acu_lv/acu_lv_drv_imd.d \
./Core/driver/acu_lv/acu_lv_drv_sdc.d 


# Each subdirectory must supply rules for building sources it contributes
Core/driver/acu_lv/%.o Core/driver/acu_lv/%.su Core/driver/acu_lv/%.cyclo: ../Core/driver/acu_lv/%.c Core/driver/acu_lv/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H753xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Core/application -I../Core/data -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Core/application/tasks -I../Core/config/acu_lv -I../Core/config/can -I../Core/service/acu_lv -I../Core/driver/acu_lv -I../Core/service/can -I../Core/driver/can -I../Core/common -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-driver-2f-acu_lv

clean-Core-2f-driver-2f-acu_lv:
	-$(RM) ./Core/driver/acu_lv/acu_lv_drv_air.cyclo ./Core/driver/acu_lv/acu_lv_drv_air.d ./Core/driver/acu_lv/acu_lv_drv_air.o ./Core/driver/acu_lv/acu_lv_drv_air.su ./Core/driver/acu_lv/acu_lv_drv_analog.cyclo ./Core/driver/acu_lv/acu_lv_drv_analog.d ./Core/driver/acu_lv/acu_lv_drv_analog.o ./Core/driver/acu_lv/acu_lv_drv_analog.su ./Core/driver/acu_lv/acu_lv_drv_debug_led.cyclo ./Core/driver/acu_lv/acu_lv_drv_debug_led.d ./Core/driver/acu_lv/acu_lv_drv_debug_led.o ./Core/driver/acu_lv/acu_lv_drv_debug_led.su ./Core/driver/acu_lv/acu_lv_drv_dfsdm.cyclo ./Core/driver/acu_lv/acu_lv_drv_dfsdm.d ./Core/driver/acu_lv/acu_lv_drv_dfsdm.o ./Core/driver/acu_lv/acu_lv_drv_dfsdm.su ./Core/driver/acu_lv/acu_lv_drv_imd.cyclo ./Core/driver/acu_lv/acu_lv_drv_imd.d ./Core/driver/acu_lv/acu_lv_drv_imd.o ./Core/driver/acu_lv/acu_lv_drv_imd.su ./Core/driver/acu_lv/acu_lv_drv_sdc.cyclo ./Core/driver/acu_lv/acu_lv_drv_sdc.d ./Core/driver/acu_lv/acu_lv_drv_sdc.o ./Core/driver/acu_lv/acu_lv_drv_sdc.su

.PHONY: clean-Core-2f-driver-2f-acu_lv

