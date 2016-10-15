#!/bin/bash

i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c libc/string/memcpy.c -o libc/string/memcpy.libc.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c libc/string/memmove.c -o libc/string/memmove.libc.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c libc/string/strcpy.c -o libc/string/strcpy.libc.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c libc/string/strncpy.c -o libc/string/strncpy.libc.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c libc/string/strlen.c -o libc/string/strlen.libc.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
i686-elf-ar rcs libc.a libc/string/memcpy.libc.o libc/string/memmove.libc.o libc/string/strcpy.libc.o libc/string/strncpy.libc.o libc/string/strlen.libc.o

mkdir -p sysroot/usr/lib
cp libc.a sysroot/usr/lib
