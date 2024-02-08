CC=arm-none-eabi-gcc 
CFLAGS=-mcpu=cortex-m4 -mthumb --specs=nano.specs
CPPFLAGS=-DSTM32F302Rx -Iexternal/CMSIS/CMSIS/Core/Include -Iexternal/CMSIS/Device/ST/STM32F3/Include -I./inc
LINKER_FILE=linker_script.ld
LD_FLAGS=-T $(LINKER_FILE) 

SRCDIR=./src
OBJDIR=./obj
SRC=$(wildcard $(SRCDIR)/*.c)
OBJ=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

PROGRAMMER=openocd
PROGRAMMER_FLAGS=-f interface/stlink.cfg -f target/stm32f3x.cfg

flash: blink.elf
	$(PROGRAMMER) $(PROGRAMMER_FLAGS) -c "program blink.elf verify reset exit"

all: blink.elf

blink.elf:$(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LD_FLAGS) $^ -o blink.elf

$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -c -o $@


.PHONY: clean
clean:
	rm -f $(OBJ) *.elf
