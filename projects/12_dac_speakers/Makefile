SUFFIX = arm-none-eabi-
CC      = $(SUFFIX)gcc
CXX     = $(SUFFIX)g++
LD      = $(SUFFIX)gcc
AS      = $(SUFFIX)gcc -x assembler-with-cpp
AR      = $(SUFFIX)ar
OBJCOPY = $(SUFFIX)objcopy
OBJDUMP = $(SUFFIX)objdump
SIZE    = $(SUFFIX)size

LINKER = ../../cmsis/MKL46Z4/linker/MKL46Z256xxx4_flash.ld
CPU    = cortex-m0plus
INSTRUCTION = thumb
CHIP_FAMILY = MKL46Z4

OBJS = main.o

CFLAGS  = -c
CFLAGS += -g
CFLAGS += -ggdb
CFLAGS += -Wall
CFLAGS += -ffunction-sections
CFLAGS += -fdata-sections
CFLAGS += -fno-builtin
CFLAGS += -Wno-unused-function
CFLAGS += -ffreestanding
CFLAGS += -MMD -MP
CFLAGS += -mcpu=$(CPU) -m$(INSTRUCTION)

ASFLAGS = $(CFLAGS)

LFLAGS = --specs=nosys.specs
LFLAGS += --specs=nano.specs
LFLAGS += -T$(LINKER)
LFLAGS += -Wl,-Map=main.map,--gc-sections
LFLAGS += -mcpu=$(CPU) -m$(INSTRUCTION)

BFLAGS  = -I binary
BFLAGS += -O elf32-littlearm
BFLAGS += -B arm

## main libraries
SYSTEM_SRC  = ../../cmsis/$(CHIP_FAMILY)
SYSTEM_SRC += ../utils

#Library headers
INC     = -I./
INC	   += -I../utils
INC    += -I../../cmsis/arm/
INC    += -I../../cmsis/$(CHIP_FAMILY)/
CFLAGS += $(INC)

VPATH	= $(SYSTEM_SRC)

#All source/object files

C_SRCS  = $(foreach dir,$(SYSTEM_SRC),$(wildcard $(dir)/*.c))
C_OBJS  = $(patsubst %.c, %.o, $(notdir $(C_SRCS)))
OBJS   += $(C_OBJS)

CPP_SRCS  = $(foreach dir,$(SYSTEM_SRC),$(wildcard $(dir)/*.cpp))
CPP_OBJS  = $(patsubst %.cpp, %.o, $(notdir $(CPP_SRCS)))
OBJS   += $(CPP_OBJS)

s_SRCS  = $(foreach dir,$(SYSTEM_SRC),$(wildcard $(dir)/*.s))
s_OBJS  = $(patsubst %.s, %.o, $(notdir $(s_SRCS)))
OBJS   += $(s_OBJS)

S_SRCS  = $(foreach dir,$(SYSTEM_SRC),$(wildcard $(dir)/*.S))
S_OBJS  = $(patsubst %.S, %.o, $(notdir $(S_SRCS)))
OBJS   += $(S_OBJS)

OBJS   += ./ring.o

##Rules

%.o : %.b
	$(OBJCOPY) $(BFLAGS)  $< $@

%.o : %.s
	$(AS) $(ASFLAGS) -o $@ $<

%.o : %.S
	$(AS) $(ASFLAGS) -o $@ $<

%.o : %.c
	$(CC) $(CFLAGS) -o $@ $<

%.o : %.cpp
	$(CC) $(CXXFLAGS) -o $@ $<

all: exec bin info
	$(LD) $(LFLAGS) -o main.elf $(OBJS)

exec: $(OBJS)
	$(LD) $(LFLAGS) -o main.elf $(OBJS)

bin:
	$(OBJCOPY) --strip-unneeded -O binary main.elf main.bin

info:
	$(SIZE) -A main.elf
	$(SIZE) -B main.elf

clean:
	rm -f $(OBJS) main.elf main.bin main.map *.d $(SYSTEM_LIB) main.o


.PHONY: all clean bin exec
