# $@ = target file
# $< = first dependency
# $^ = all dependencies
#
#
C_SOURCES = $(wildcard kernel/*.c kernel/drivers/*.c kernel/cpu/*.c kernel/memory/*.c ./cathesimc/*.c)
HEADERS = $(wildcard kernel/*.h kernel/drivers/*.h kernel/cpu/*.h kernel/memory/*.h ./cathesimc/*.h)

OBJ = ${C_SOURCES:.c=.o kernel/cpu/interrupt.o}


CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
GDB = gdb-multiarch

CFLAGS = -g

os.bin: bootloader/bootloader.bin kernel.bin
		cat $^ > os.bin

kernel.bin: bootloader/libs/kernel_entry.o ${OBJ}
		i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf: bootloader/libs/kernel_entry.o ${OBJ}
		i386-elf-ld -o $@ -Ttext 0x1000 $^ 

run: os.bin
		qemu-system-x86_64 -fda os.bin

# Open the connection to qemu and load our kernel-object file with symbols
debug: os.bin kernel.elf
		qemu-system-x86_64 -s -fda os.bin &
		${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

%.o: %.c ${HEADERS}
		${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
		nasm $< -f elf -o $@

%.bin: %.asm
		nasm $< -f bin -o $@

clean:
		rm -rf *.bin *.dis *.o os-image.bin *.elf cpu/*.o kernel/cpu/*.o kernel/memory/*.o
		rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o kernel/cpu/*.o
