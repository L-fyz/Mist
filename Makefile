# Toolchain
CC = gcc
LD = ld
NASM = nasm
OBJCOPY = objcopy

# Flags
CFLAGS = -m64 -ffreestanding -fno-stack-protector -mno-red-zone -fno-pie -fno-builtin -nostdlib -O2 -Wall -Wextra \
         -Ikernel/standard -Ikernel/drivers
LDFLAGS = -m elf_x86_64 -T kernel/linker.ld -nostdlib
NASMFLAGS = -f bin

# Автоматический поиск всех .c файлов
KERNEL_C := $(wildcard kernel/*.c kernel/standard/*.c kernel/drivers/*.c)
KERNEL_O := $(KERNEL_C:.c=.o)

all: Mist.img

# 1. Сборка загрузчика
boot/BootLoader.bin: boot/BootLoader.asm
	$(NASM) $(NASMFLAGS) $< -o $@

# 2. Линковка ядра в ELF (собирает все .o автоматически)
kernel/Kernel.elf: $(KERNEL_O)
	$(LD) $(LDFLAGS) -o $@ $^

# 3. Превращаем ELF в сырой бинарник (убираем заголовки, оставляем только код/данные)
kernel/Kernel.bin: kernel/Kernel.elf
	$(OBJCOPY) -O binary $< $@

# 4. Склейка образа диска
Mist.img: boot/BootLoader.bin kernel/Kernel.bin
	cat $^ > $@

# Правило компиляции любого .c -> .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Запуск в QEMU
run: Mist.img
	qemu-system-x86_64 -drive format=raw,file=Mist.img -no-reboot

# Очистка
clean:
	rm -f boot/*.bin kernel/*.bin kernel/*.elf $(KERNEL_O) Mist.img

.PHONY: all run clean
