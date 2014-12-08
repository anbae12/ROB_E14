################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Image.cpp \
../src/Ransac.cpp \
../src/convert.cpp \
../src/laser_range_scanner.cpp \
../src/linear_regression.cpp \
../src/main.cpp \
../src/pixel.cpp 

OBJS += \
./src/Image.o \
./src/Ransac.o \
./src/convert.o \
./src/laser_range_scanner.o \
./src/linear_regression.o \
./src/main.o \
./src/pixel.o 

CPP_DEPS += \
./src/Image.d \
./src/Ransac.d \
./src/convert.d \
./src/laser_range_scanner.d \
./src/linear_regression.d \
./src/main.d \
./src/pixel.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


