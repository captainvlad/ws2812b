################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/gpio.c \
../Src/i2c.c \
../Src/i2s.c \
../Src/main.c \
../Src/spi.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_it.c \
../Src/sys.c \
../Src/syscalls.c \
../Src/system_stm32f4xx.c \
../Src/usb_host.c \
../Src/usbh_conf.c \
../Src/usbh_platform.c \
../Src/ws2812.c 

OBJS += \
./Src/gpio.o \
./Src/i2c.o \
./Src/i2s.o \
./Src/main.o \
./Src/spi.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_it.o \
./Src/sys.o \
./Src/syscalls.o \
./Src/system_stm32f4xx.o \
./Src/usb_host.o \
./Src/usbh_conf.o \
./Src/usbh_platform.o \
./Src/ws2812.o 

C_DEPS += \
./Src/gpio.d \
./Src/i2c.d \
./Src/i2s.d \
./Src/main.d \
./Src/spi.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_it.d \
./Src/sys.d \
./Src/syscalls.d \
./Src/system_stm32f4xx.d \
./Src/usb_host.d \
./Src/usbh_conf.d \
./Src/usbh_platform.d \
./Src/ws2812.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F411xE -I"/home/vlad/Desktop/2_year/POK/project/ws2812/Inc" -I"/home/vlad/Desktop/2_year/POK/project/ws2812/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/home/vlad/Desktop/2_year/POK/project/ws2812/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/home/vlad/Desktop/2_year/POK/project/ws2812/Middlewares/ST/STM32_USB_Host_Library/Core/Inc" -I"/home/vlad/Desktop/2_year/POK/project/ws2812/Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc" -I"/home/vlad/Desktop/2_year/POK/project/ws2812/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/home/vlad/Desktop/2_year/POK/project/ws2812/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


