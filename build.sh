#!/bin/bash

mkdir -p sysroot/usr/include
cp -R --preserve=timestamps libc/include/. sysroot/usr/include

# make libc
./makelib.sh

cp -R --preserve=timestamps kernel/include/. sysroot/usr/include

i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c kernel/arch/i386/crti.s -o kernel/arch/i386/crti.o -O2 -g -ffreestanding -Wall -Wextra
OBJ=`i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -O2 -g -ffreestanding -Wall -Wextra -print-file-name=crtbegin.o` && cp "$OBJ" kernel/arch/i386/crtbegin.o
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c kernel/arch/i386/boot.s -o kernel/arch/i386/boot.o -O2 -g -ffreestanding -Wall -Wextra
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c kernel/arch/i386/gdt_flush.s -o kernel/arch/i386/gdt_flush.o -O2 -g -ffreestanding -Wall -Wextra
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c kernel/arch/i386/mov_cursor.s -o kernel/arch/i386/mov_cursor.o -O2 -g -ffreestanding -Wall -Wextra
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c kernel/arch/i386/gdt.c -o kernel/arch/i386/gdt.o -O2 -g -ffreestanding -Wall -Wextra
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c kernel/arch/i386/tty.c -o kernel/arch/i386/tty.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c kernel/arch/i386/cursor.c -o kernel/arch/i386/cursor.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c kernel/kernel/printk.c -o kernel/kernel/printk.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c kernel/kernel/kernel.c -o kernel/kernel/kernel.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
OBJ=`i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -O2 -g -ffreestanding -Wall -Wextra -print-file-name=crtend.o` && cp "$OBJ" kernel/arch/i386/crtend.o
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c kernel/arch/i386/crtn.s -o kernel/arch/i386/crtn.o -O2 -g -ffreestanding -Wall -Wextra
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -T kernel/arch/i386/linker.ld -o DoogOS.kernel -O2 -g -ffreestanding -Wall -Wextra kernel/arch/i386/crti.o kernel/arch/i386/crtbegin.o kernel/arch/i386/boot.o kernel/arch/i386/gdt_flush.o kernel/arch/i386/mov_cursor.o kernel/arch/i386/gdt.o kernel/arch/i386/tty.o kernel/arch/i386/cursor.o kernel/kernel/printk.o kernel/kernel/kernel.o -nostdlib -lc -lgcc kernel/arch/i386/crtend.o kernel/arch/i386/crtn.o
echo "compilation done"
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

# time to clean up
echo "cleaning up our mess"
./clean.sh
