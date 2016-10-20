#!/bin/bash

# clean up libc
rm libc/string/memcpy.libc.o
rm libc/string/memmove.libc.o
rm libc/string/strcpy.libc.o
rm libc/string/strncpy.libc.o
rm libc/string/strcat.libc.o
rm libc/string/strncat.libc.o
rm libc/string/memcmp.libc.o
rm libc/string/strcmp.libc.o
rm libc/string/strncmp.libc.o
rm libc/string/memchr.libc.o
rm libc/string/strchr.libc.o
rm libc/string/strcspn.libc.o
rm libc/string/strpbrk.libc.o
rm libc/string/strrchr.libc.o
rm libc/string/strspn.libc.o
rm libc/string/strstr.libc.o
rm libc/string/memset.libc.o
rm libc/string/strlen.libc.o

# clean up everything else
#rm DoogOS.kernel
#rm libc.a
rm kernel/arch/i386/boot.o
rm kernel/arch/i386/crtbegin.o
rm kernel/arch/i386/crtend.o
rm kernel/arch/i386/crti.o
rm kernel/arch/i386/crtn.o
rm kernel/arch/i386/cursor.o
rm kernel/arch/i386/gdt.o
rm kernel/arch/i386/mov_cursor.o
rm kernel/arch/i386/tty.o
rm kernel/kernel/kernel.o
rm -rf sysroot
rm -rf iso
