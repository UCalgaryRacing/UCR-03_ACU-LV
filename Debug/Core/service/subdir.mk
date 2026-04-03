################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/service/acu_lv_src_pack_current.c 

OBJS += \
./Core/service/acu_lv_src_pack_current.o 

C_DEPS += \
./Core/service/acu_lv_src_pack_current.d 


# Each subdirectory must supply rules for building sources it contributes
Core/service/%.o Core/service/%.su Core/service/%.cyclo: ../Core/service/%.c Core/service/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H753xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Core/application -I"C:/Users/clayd/OneDrive/Documents/UCR_03/UCR_03_ACU_LV/Core/config" -I../Core/data -I../Core/service -I../Core/types -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Core/driver -I../Core/config -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-service

clean-Core-2f-service:
	-$(RM) ./Core/service/acu_lv_src_pack_current.cyclo ./Core/service/acu_lv_src_pack_current.d ./Core/service/acu_lv_src_pack_current.o ./Core/service/acu_lv_src_pack_current.su

.PHONY: clean-Core-2f-service

