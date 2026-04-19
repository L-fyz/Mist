C_SRCS   := $(wildcard msc/drivers/*.c msc/kernel/*.c msc/mistd/*.c)
ASM_SRCS := $(wildcard msc/kernel/*.asm)

C_OBJS   := $(C_SRCS:msc/%.c=mbin/%.o)
ASM_OBJS := $(ASM_SRCS:msc/%.asm=mbin/%.o)
ALL_OBJS := $(C_OBJS) $(ASM_OBJS)

BUILD_DIR := mbin

all: $(BUILD_DIR)/Mist.img

$(BUILD_DIR)/Minit/BootLoader.bin: msc/Minit/BootLoader.asm
	@mkdir -p $(dir $@)
	nasm -f bin $< -o $@

$(BUILD_DIR)/kernel/Kernel.elf: $(ALL_OBJS)
	@mkdir -p $(dir $@)
	ld.lld -m elf_x86_64 -T linker.ld -nostdlib -o $@ $^

$(BUILD_DIR)/kernel/Kernel.bin: $(BUILD_DIR)/kernel/Kernel.elf
	@mkdir -p $(dir $@)
	llvm-objcopy -O binary $< $@

$(BUILD_DIR)/Mist.img: $(BUILD_DIR)/Minit/BootLoader.bin $(BUILD_DIR)/kernel/Kernel.bin
	cat $^ > $@

mbin/%.o: msc/%.c
	@mkdir -p $(dir $@)
	clang --target=x86_64-elf -ffreestanding -fno-stack-protector -mno-red-zone -mno-sse -mno-sse2 -fno-pie -fno-builtin -nostdlib -O2 -Wall -Wextra -Imsc/headers -c $< -o $@

mbin/%.o: msc/%.asm
	@mkdir -p $(dir $@)
	nasm -f elf64 $< -o $@

run: $(BUILD_DIR)/Mist.img
	qemu-system-x86_64 -drive format=raw,file=$< -no-reboot

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run clean
