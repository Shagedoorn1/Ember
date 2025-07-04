# Tools
CC = i686-elf-gcc
LD = i686-elf-ld

# Flags
CFLAGS  = -m32 -ffreestanding -O2 -Wall -Wextra -Iinclude
LDFLAGS = -T boot/linker.ld -nostdlib

# Sources and objects
SRC_C = src/kernel.c src/screen.c
SRC_S = boot/boot.S
OBJS  = $(SRC_C:.c=.o) $(SRC_S:.S=.o)

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
