# Tools
CC = i686-elf-gcc
LD = i686-elf-ld

# Flags
CFLAGS  = -m32 -ffreestanding -O2 -Wall -Wextra -Iinclude -IAmitC -Icyclone -I..
LDFLAGS = -T boot/linker.ld -nostdlib

# Sources and objects
SRC_C = src/kernel.c src/screen.c src/io.c src/string.c src/interrupts.c src/time.c src/timer.c src/keyboard.c src/idt.c src/logo.c src/fs.c
SRC_AMITC = AmitC/amitc.c
SRC_CYCLONE = cyclone/cyclone.c cyclone/commands.c cyclone/utils.c
SRC_S = boot/boot.S src/isr_stub.S src/gdt.S
OBJS  = $(SRC_C:.c=.o) $(SRC_S:.S=.o) $(SRC_AMITC:.c=.o) $(SRC_CYCLONE:.c=.o)

# Default target
all: kernel.bin

# Compile C files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile assembly files
%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@


# Link kernel
kernel.bin: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

# Clean
clean:
	rm -f $(OBJS) kernel.bin
