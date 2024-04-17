################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
OBJS += \
./User/MyFIFOBuf.o 

CPP_DEPS += \
./User/MyFIFOBuf.d 


# Each subdirectory must supply rules for building sources it contributes
User/MyFIFOBuf.o: D:/Slava/programming/STM32_Projects/CAN_Adapter/Core/Inc/User/MyFIFOBuf.cpp User/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F107xC -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/Slava/programming/STM32_Projects/CAN_Adapter/Core/Inc/User" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-User

clean-User:
	-$(RM) ./User/MyFIFOBuf.cyclo ./User/MyFIFOBuf.d ./User/MyFIFOBuf.o ./User/MyFIFOBuf.su

.PHONY: clean-User

