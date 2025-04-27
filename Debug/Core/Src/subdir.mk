################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/AdcVoltageSensor.cpp \
../Core/Src/ShellTask.cpp \
../Core/Src/SolarPanel.cpp \
../Core/Src/UartRxStream.cpp \
../Core/Src/VirtualDeviceTask.cpp \
../Core/Src/VirtualHumiditySensor.cpp \
../Core/Src/VirtualTemperatureSensor.cpp \
../Core/Src/dht11.cpp \
../Core/Src/main.cpp 

C_SRCS += \
../Core/Src/dwt_delay.c \
../Core/Src/freertos.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c 

C_DEPS += \
./Core/Src/dwt_delay.d \
./Core/Src/freertos.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d 

OBJS += \
./Core/Src/AdcVoltageSensor.o \
./Core/Src/ShellTask.o \
./Core/Src/SolarPanel.o \
./Core/Src/UartRxStream.o \
./Core/Src/VirtualDeviceTask.o \
./Core/Src/VirtualHumiditySensor.o \
./Core/Src/VirtualTemperatureSensor.o \
./Core/Src/dht11.o \
./Core/Src/dwt_delay.o \
./Core/Src/freertos.o \
./Core/Src/main.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o 

CPP_DEPS += \
./Core/Src/AdcVoltageSensor.d \
./Core/Src/ShellTask.d \
./Core/Src/SolarPanel.d \
./Core/Src/UartRxStream.d \
./Core/Src/VirtualDeviceTask.d \
./Core/Src/VirtualHumiditySensor.d \
./Core/Src/VirtualTemperatureSensor.d \
./Core/Src/dht11.d \
./Core/Src/main.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.cpp Core/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++17 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -O0 -ffunction-sections -fdata-sections -Wall -Wno-register -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/AdcVoltageSensor.cyclo ./Core/Src/AdcVoltageSensor.d ./Core/Src/AdcVoltageSensor.o ./Core/Src/AdcVoltageSensor.su ./Core/Src/ShellTask.cyclo ./Core/Src/ShellTask.d ./Core/Src/ShellTask.o ./Core/Src/ShellTask.su ./Core/Src/SolarPanel.cyclo ./Core/Src/SolarPanel.d ./Core/Src/SolarPanel.o ./Core/Src/SolarPanel.su ./Core/Src/UartRxStream.cyclo ./Core/Src/UartRxStream.d ./Core/Src/UartRxStream.o ./Core/Src/UartRxStream.su ./Core/Src/VirtualDeviceTask.cyclo ./Core/Src/VirtualDeviceTask.d ./Core/Src/VirtualDeviceTask.o ./Core/Src/VirtualDeviceTask.su ./Core/Src/VirtualHumiditySensor.cyclo ./Core/Src/VirtualHumiditySensor.d ./Core/Src/VirtualHumiditySensor.o ./Core/Src/VirtualHumiditySensor.su ./Core/Src/VirtualTemperatureSensor.cyclo ./Core/Src/VirtualTemperatureSensor.d ./Core/Src/VirtualTemperatureSensor.o ./Core/Src/VirtualTemperatureSensor.su ./Core/Src/dht11.cyclo ./Core/Src/dht11.d ./Core/Src/dht11.o ./Core/Src/dht11.su ./Core/Src/dwt_delay.cyclo ./Core/Src/dwt_delay.d ./Core/Src/dwt_delay.o ./Core/Src/dwt_delay.su ./Core/Src/freertos.cyclo ./Core/Src/freertos.d ./Core/Src/freertos.o ./Core/Src/freertos.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su

.PHONY: clean-Core-2f-Src

