ROOT=/home/henryrovner/Repos/arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi/
CC=$(ROOT)/bin/arm-none-eabi-gcc
AS=$(ROOT)/bin/arm-none-eabi-as
LD=$(ROOT)/bin/arm-none-eabi-ld
CCFLAGS=-mcpu=cortex-m0 -mthumb -g -lgcc
PORTN=/dev/ttyUSB0
OBJS=init.o main.o serial.o serial1.o

# Search for the path of libraries.
LIBPATH1=$(shell find $(ROOT)/ -name libgcc.a | grep "v6-m" | sed -e "s/libgcc.a//g")
LIBPATH2=$(shell find $(ROOT) -name libc_nano.a | grep "v6-m" | sed -e "s/libc_nano.a//g")
LIBSPEC=-L"$(LIBPATH1)" -L"$(LIBPATH2)"

main.elf : $(OBJS)
	$(LD) $(OBJS) $(LIBSPEC) -lgcc -T lpc824_linker_script.ld --cref -Map main.map -o main.elf
	$(ROOT)/bin/arm-none-eabi-objcopy -O ihex main.elf main.hex
	@echo Success!

main.o: main.c lpc824.h serial.h
	$(CC) -c $(CCFLAGS) main.c -o main.o

init.o: init.c lpc824.h serial.h
	$(CC) -c $(CCFLAGS) init.c -o init.o

serial.o: serial.c lpc824.h serial.h
	$(CC) -c $(CCFLAGS) serial.c -o serial.o

serial1.o: serial1.c lpc824.h serial1.h
	$(CC) -c $(CCFLAGS) serial1.c -o serial1.o

clean: 
	rm -f $(OBJS) main.elf main.hex main.map

LoadFlash:
	../../lpc21isp/lpc21isp main.hex $(PORTN) 115200 12000000

