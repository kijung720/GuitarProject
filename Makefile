NAME = main
OBJECTS = LSM6DS33.o guitar.o

# Edit to point to CS107E folder (needed for .h files)
CS107E=../../cs107e.github.io
CFLAGS = -I$(CS107E)/libpi/include -g -Wall -Werror -Og -std=c99 -ffreestanding
LDFLAGS = -nostdlib -T memmap -L.
LDLIBS = -lmypi -lgcc

all : $(NAME).bin

%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

%.elf: %.o $(OBJECTS) start.o cstart.o
	arm-none-eabi-gcc $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

%.o: %.s
	arm-none-eabi-as $< -o $@

%.list: %.o
	arm-none-eabi-objdump -d $< > $@

install: $(NAME).bin
	rpi-install.py $<

clean:
	rm -f *.o *.bin *.elf *.list *~

.PHONY: all clean install

.PRECIOUS: %.o %.elf
