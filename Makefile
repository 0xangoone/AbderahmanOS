ASSEMBLER = nasm
CC=/usr/local/i386elfgcc/bin/i386-elf-gcc
LD=/usr/local/i386elfgcc/bin/i386-elf-ld
VM = qemu-system-x86_64
build: build/boot.bin build/kernel.bin build/OS.bin

build/boot.bin: bootloader/boot.asm
	$(ASSEMBLER) -f bin bootloader/boot.asm -o build/boot.bin

build/kernel_init.o: kernel/init.cpp
	$(CC) -ffreestanding -m32 -g -c kernel/init.cpp -o build/kernel_init.o

build/kernel_entry.o: kernel/kernel_entry.asm
	$(ASSEMBLER) -f elf kernel/kernel_entry.asm -o build/kernel_entry.o

build/tty.o: kernel/drivers/tty.cpp
	$(CC) -ffreestanding -m32 -g -c kernel/drivers/tty.cpp -o build/tty.o

build/ports.o: kernel/drivers/ports.cpp
	$(CC) -ffreestanding -m32 -g -c kernel/drivers/ports.cpp -o build/ports.o
build/sound.o: kernel/drivers/sound.cpp
	$(CC) -ffreestanding -m32 -g -c kernel/drivers/sound.cpp -o build/sound.o
build/cpu.o: kernel/drivers/cpu.cpp
	$(CC) -ffreestanding -m32 -g -c kernel/drivers/cpu.cpp -o build/cpu.o
build/ps2keyboard.o: kernel/drivers/ps2keyboard.cpp
	$(CC) -ffreestanding -m32 -g -c kernel/drivers/ps2keyboard.cpp -o build/ps2keyboard.o
build/kernel.bin: build/kernel_entry.o build/kernel_init.o build/tty.o build/ports.o build/sound.o  build/cpu.o build/ps2keyboard.o
	$(LD) -o build/kernel.bin -Ttext 0x1000 build/kernel_entry.o build/kernel_init.o build/tty.o build/ports.o build/ps2keyboard.o build/sound.o  build/cpu.o --oformat binary

build/OS.bin: build/boot.bin build/kernel.bin
	touch build/OS.bin
	dd if=build/boot.bin of=build/OS.bin bs=512 count=1
	dd if=build/kernel.bin of=build/OS.bin bs=512 seek=1 conv=notrunc
	dd if=zero.bin of=build/OS.bin bs=512 seek=1024 conv=notrunc

run: build
	$(VM) -device intel-hda -device hda-duplex -drive format=raw,file=build/OS.bin,index=0,if=floppy, -m 128M

clean:
	@echo "cleaning..."
	rm -rf build
	mkdir build

