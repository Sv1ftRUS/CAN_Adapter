################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/User/MyFifoBuf.c 

C_DEPS += \
./Core/Src/User/MyFifoBuf.d 

OBJS += \
./Core/Src/User/MyFifoBuf.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/User/%.o Core/Src/User/%.su Core/Src/User/%.cyclo: ../Core/Src/User/%.c Core/Src/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F107xC -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-User

clean-Core-2f-Src-2f-User:
	-$(RM) ./Core/Src/User/MyFifoBuf.cyclo ./Core/Src/User/MyFifoBuf.d ./Core/Src/User/MyFifoBuf.o ./Core/Src/User/MyFifoBuf.su

.PHONY: clean-Core-2f-Src-2f-User

