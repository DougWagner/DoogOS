#!/bin/bash

mkdir -p sysroot/usr/include
cp -R --preserve=timestamps libc/include/. sysroot/usr/include

#compile standard library
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c libc/string/strlen.c -o libc/string/strlen.libk.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
i686-elf-ar rcs libk.a libc/string/strlen.libk.o

mkdir -p sysroot/usr/lib
cp libk.a sysroot/usr/lib

cp -R --preserve=timestamps kernel/include/. sysroot/usr/include

i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c kernel/arch/i386/boot.s -o kernel/arch/i386/boot.o -O2 -g -ffreestanding -Wall -Wextra
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c kernel/arch/i386/add.s -o kernel/arch/i386/add.o -O2 -g -ffreestanding -Wall -Wextra
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c kernel/arch/i386/tty.c -o kernel/arch/i386/tty.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c kernel/kernel/kernel.c -o kernel/kernel/kernel.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -T kernel/arch/i386/linker.ld -o DoogOS.kernel -O2 -g -ffreestanding -Wall -Wextra kernel/arch/i386/boot.o kernel/arch/i386/add.o kernel/arch/i386/tty.o kernel/kernel/kernel.o -nostdlib -lk -lgcc
mkdir -p sysroot/boot
cp DoogOS.kernel sysroot/boot

mkdir -p iso/boot/grub
cp sysroot/boot/DoogOS.kernel iso/boot
cat > iso/boot/grub/grub.cfg << EOF
menuentry "DoogOS" {
    multiboot /boot/DoogOS.kernel
}
EOF
grub-mkrescue -o DoogOS.iso iso
