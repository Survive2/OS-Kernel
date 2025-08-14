BUILD := ./build

CFLAGS = -m32
CFLAGS += -masm=intel
CFLAGS += -fno-builtin
CFLAGS += -nostdinc
CFLAGS += -fno-pic
CFLAGS += -fno-pie
CFLAGS += -nostdlib
CFLAGS += -fno-stack-protector
CFLAGS := $(strip $(CFLAGS))

DEBUG = -g

HD_IMG_NAME = hd.img

all: $(BUILD)/boot/boot.o $(BUILD)/boot/setup.o $(BUILD)/system.bin
	rm -f $(HD_IMG_NAME)
	bximage -q -hd=16 -func=create -sectsize=512 -imgmode=flat $(HD_IMG_NAME)
	dd if=$(BUILD)/boot/boot.o of=$(HD_IMG_NAME) bs=512 seek=0 count=1 conv=notrunc
	dd if=$(BUILD)/boot/setup.o of=$(HD_IMG_NAME) bs=512 seek=1 count=2 conv=notrunc
	dd if=$(BUILD)/system.bin of=$(HD_IMG_NAME) bs=512 seek=3 count=60 conv=notrunc

${BUILD}/system.bin: ${BUILD}/kernel.bin
	gobjcopy -O binary ${BUILD}/kernel.bin ${BUILD}/system.bin

$(BUILD)/kernel.bin: $(BUILD)/boot/head.o $(BUILD)/init/main.o \
	$(BUILD)/kernel/asm/io.o $(BUILD)/kernel/asm/interrupt_handler.o $(BUILD)/kernel/asm/clock_handler.o $(BUILD)/kernel/asm/sched.o \
	$(BUILD)/kernel/chr_drv/console.o $(BUILD)/kernel/chr_drv/keyboard.o $(BUILD)/kernel/chr_drv/clock.o \
    $(BUILD)/lib/string.o \
	${BUILD}/mm/memory.o ${BUILD}/mm/pages.o ${BUILD}/mm/kmalloc.o\
	$(BUILD)/kernel/vsprintf.o $(BUILD)/kernel/printk.o ${BUILD}/kernel/gdt.o ${BUILD}/kernel/idt.o ${BUILD}/kernel/traps.o ${BUILD}/kernel/exception.o ${BUILD}/kernel/kernel.o \
	${BUILD}/kernel/sched.o ${BUILD}/kernel/task.o
	x86_64-unknown-linux-gnu-ld -m elf_i386 $^ -o $@ -Ttext 0x1200
	nm $(BUILD)/kernel.bin | sort > $(BUILD)/system.map

$(BUILD)/init/%.o: ./init/%.c
	mkdir -p $(dir $@)
	x86_64-unknown-linux-gnu-gcc $(CFLAGS) $(DEBUG) -c $< -o $@

$(BUILD)/boot/head.o: ./boot/head.asm
	mkdir -p $(dir $@)
	nasm -f elf32 -g $< -o $@

$(BUILD)/kernel/%.o: ./kernel/%.c
	mkdir -p $(dir $@)
	x86_64-unknown-linux-gnu-gcc $(CFLAGS) $(DEBUG) -c $< -o $@

$(BUILD)/lib/%.o: ./lib/%.c
	mkdir -p $(dir $@)
	x86_64-unknown-linux-gnu-gcc $(CFLAGS) $(DEBUG) -c $< -o $@

$(BUILD)/kernel/chr_drv/%.o: ./kernel/chr_drv/%.c
	mkdir -p $(dir $@)
	x86_64-unknown-linux-gnu-gcc $(CFLAGS) $(DEBUG) -c $< -o $@

$(BUILD)/mm/%.o: ./mm/%.c
	mkdir -p $(dir $@)
	x86_64-unknown-linux-gnu-gcc $(CFLAGS) $(DEBUG) -c $< -o $@

$(BUILD)/kernel/asm/%.o: ./kernel/asm/%.asm
	mkdir -p $(dir $@)
	nasm -f elf32 -g $< -o $@

$(BUILD)/boot/%.o: ./boot/%.asm
	mkdir -p $(dir $@)
	nasm $< -o $@

clean:
	rm -rf $(BUILD)

qemu: all
	qemu-system-i386 \
	-hda hd.img


debug: all
	qemu-system-x86_64 -m 32M -S -s -hda hd.img
