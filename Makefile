C := $(wildcard msc/drivers/*.c msc/kernel/*.c msc/mistlibc/*.c)
O := $(C:.c=.o)

all: Mist.img

mbin/Minit/BootLoader.bin: msc/Minit/BootLoader.asm
	nasm -f bin $< -o $@

mbin/kernel/Kernel.elf: $(O)
	ld.lld -m elf_x86_64 -T linker.ld -nostdlib -o $@ $^

mbin/kernel/Kernel.bin: mbin/kernel/Kernel.elf
	llvm-objcopy -O binary $< $@

Mist.img: mbin/Minit/BootLoader.bin mbin/kernel/Kernel.bin
	cat $^ > $@

%.o: %.c
	clang --target=x86_64-elf -ffreestanding -fno-stack-protector -mno-red-zone -mno-sse -mno-sse2 -fno-pie -fno-builtin -nostdlib -O2 -Wall -Wextra -Imsc/headers -c $< -o $@

run: Mist.img
	qemu-system-x86_64 -drive format=raw,file=mbin/Mist.img -no-reboot

clean:
	rm -f mbin/Minit/* mbin/drivers/* mbin/kernel/* mbin/mistlibs/* Mist.img

.PHONY: all run clean
