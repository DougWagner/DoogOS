#!/bin/bash

# <string.h>
# copying functions
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c libc/string/memcpy.c -o libc/string/memcpy.libc.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c libc/string/memmove.c -o libc/string/memmove.libc.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c libc/string/strcpy.c -o libc/string/strcpy.libc.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c libc/string/strncpy.c -o libc/string/strncpy.libc.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
# concatenation functions
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c libc/string/strcat.c -o libc/string/strcat.libc.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c libc/string/strncat.c -o libc/string/strncat.libc.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
# comparison functions
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c libc/string/memcmp.c -o libc/string/memcmp.libc.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c libc/string/strcmp.c -o libc/string/strcmp.libc.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
# search functions
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c libc/string/memchr.c -o libc/string/memchr.libc.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
# miscellaneous functions
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c libc/string/memset.c -o libc/string/memset.libc.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c libc/string/strlen.c -o libc/string/strlen.libc.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra

# archive libc
i686-elf-ar rcs libc.a libc/string/memcpy.libc.o libc/string/memmove.libc.o libc/string/strcpy.libc.o libc/string/strncpy.libc.o libc/string/strlen.libc.o

mkdir -p sysroot/usr/lib
cp libc.a sysroot/usr/lib

rm libc/string/memcpy.libc.o
rm libc/string/memmove.libc.o
rm libc/string/strcpy.libc.o
rm libc/string/strncpy.libc.o
rm libc/string/strcat.libc.o
rm libc/string/strncat.libc.o
rm libc/string/memcmp.libc.o
rm libc/string/strcmp.libc.o
rm libc/string/memchr.libc.o
rm libc/string/memset.libc.o
rm libc/string/strlen.libc.o
