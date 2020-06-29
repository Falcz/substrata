C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h)
OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o}

CC = gcc
GDB = gdb
# -g: Use debugging symbols in gcc
CFLAGS = -g

# First rule is run by default
os-image.bin: boot/boot_sect.bin kernel.bin
	cat $^ > os-image.bin

kernel.bin: boot/kernel_entry.o ${OBJ}
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf: boot/kernel_entry.o ${OBJ}
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^

run: os-image.bin
	qemu-system-x86_64 -fda os-image.bin -curses

debug: os-image.bin kernel.elf
	qemu-system-x86_64 -s -S -fda os-image.bin &
	sleep 1
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -fno-stack-protector -ffreestanding -march=i386 -m32 -fno-pie -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o *.elf
	rm -rf kernel/*.o boot/*.bin cpu/*.bin drivers/*.o boot/*.o cpu/*.o
