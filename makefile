DIRECTORIES = boot kernel drivers HAL dataman physmm virtualmm console

C_SOURCES = $(wildcard drivers/x86/*.c HAL/x86/*.c dataman/*.c physmm/*.c virtualmm/*.c console/*.c)
ASM_SOURCES = $(wildcard HAL/x86/*.asm)

CC = gcc
CFLAGS = -DDEBUG -m32 -ffreestanding -c -nostdlib -lgcc

KERNEL = kernel/kernel_start.o kernel/kernel.o

ASM = nasm
AOFLAGS = -f elf32 -o
ABINFLAGS = -f bin -o

OBJ = ${C_SOURCES:.c=.o}
ASMOBJ = ${ASM_SOURCES:.asm=.o}

all: os-image.img

os-image.img: boot/x86/boot_sector.bin boot/x86/boot_stage2.bin kernel/kernel.bin res/zero2048.bin
	cat $^ > $@

kernel/kernel.bin: ${KERNEL} ${ASMOBJ} ${OBJ}
	ld -melf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

%.o : %.c
	$(CC) $(CFLAGS) $< -o $@
 
%.o : %.asm
	$(ASM) $< $(AOFLAGS) $@

%.bin : %.asm 
	nasm $< $(ABINFLAGS) $@

clean:
	rm -fr kernel/*.o
	rm -fr drivers/x86/*.o
	rm -fr HAL/x86/*.o
	rm -fr dataman/*.o
	rm -fr physmm/*.o
	rm -fr boot/x86/*.bin
	rm -fr console/*.o
	rm -fr virtualmm/*.o
	rm -fr os-image.img *.bin *.o

rebuild:
	make clean
	make

backup:
	make clean
	zip -r backups/BACKUP_DATE-`date +%d-%m-%Y_%H-%M-%S`.zip $(DIRECTORIES) README.txt makefile
	make