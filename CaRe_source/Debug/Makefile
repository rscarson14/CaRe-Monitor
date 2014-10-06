################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../App


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../App/ADC_HAL.c \
../App/Macros.c \
../App/ISR.c \
../App/Filt.c \
../App/Globals.c \
../App/main.c \
../App/Init.c \
../App/Pot_HAL.c \
../App/Serial_HAL.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
App/ADC_HAL.o \
App/Macros.o \
App/ISR.o \
App/Filt.o \
App/Globals.o \
App/main.o \
App/Init.o \
App/Pot_HAL.o \
App/Serial_HAL.o

OBJS_AS_ARGS +=  \
App/ADC_HAL.o \
App/Macros.o \
App/ISR.o \
App/Filt.o \
App/Globals.o \
App/main.o \
App/Init.o \
App/Pot_HAL.o \
App/Serial_HAL.o

C_DEPS +=  \
App/ADC_HAL.d \
App/Macros.d \
App/ISR.d \
App/Filt.d \
App/Globals.d \
App/main.d \
App/Init.d \
App/Pot_HAL.d \
App/Serial_HAL.d

C_DEPS_AS_ARGS +=  \
App/ADC_HAL.d \
App/Macros.d \
App/ISR.d \
App/Filt.d \
App/Globals.d \
App/main.d \
App/Init.d \
App/Pot_HAL.d \
App/Serial_HAL.d

OUTPUT_FILE_PATH +=CaRe.elf

OUTPUT_FILE_PATH_AS_ARGS +=CaRe.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

# AVR32/GNU C Compiler



















App/%.o: ../App/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.7.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -O0 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g3 -Wall -mmcu=atmega328p -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 4.7.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="CaRe.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=atmega328p  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "CaRe.elf" "CaRe.hex"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "CaRe.elf" "CaRe.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "CaRe.elf" > "CaRe.lss"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "CaRe.elf" "CaRe.srec"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-size.exe" "CaRe.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "CaRe.elf" "CaRe.a" "CaRe.hex" "CaRe.lss" "CaRe.eep" "CaRe.map" "CaRe.srec" "CaRe.usersignatures"
	