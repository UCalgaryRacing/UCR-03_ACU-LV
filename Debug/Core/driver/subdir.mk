################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/driver/acu_lv_drv_dfsdm.c 

OBJS += \
./Core/driver/acu_lv_drv_dfsdm.o 

C_DEPS += \
./Core/driver/acu_lv_drv_dfsdm.d 


# Each subdirectory must supply rules for building sources it contributes
Core/driver/%.o Core/driver/%.su Core/driver/%.cyclo: ../Core/driver/%.c Core/driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H753xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Core/application -I"C:/Users/clayd/OneDrive/Documents/UCR_03/UCR_03_ACU_LV/Core/config" -I../Core/data -I../Core/service -I../Core/types -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Core/driver -I../Core/config -I../Core/application/tasks -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-driver

clean-Core-2f-driver:
	-$(RM) ./Core/driver/acu_lv_drv_dfsdm.cyclo ./Core/driver/acu_lv_drv_dfsdm.d ./Core/driver/acu_lv_drv_dfsdm.o ./Core/driver/acu_lv_drv_dfsdm.su

.PHONY: clean-Core-2f-driver

