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
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c libc/string/strncmp.c -o libc/string/strncmp.libc.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
# search functions
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c libc/string/memchr.c -o libc/string/memchr.libc.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c libc/string/strchr.c -o libc/string/strchr.libc.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c libc/string/strcspn.c -o libc/string/strcspn.libc.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c libc/string/strpbrk.c -o libc/string/strpbrk.libc.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c libc/string/strrchr.c -o libc/string/strrchr.libc.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c libc/string/strspn.c -o libc/string/strspn.libc.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
i686-elf-gcc --sysroot=/home/doug/os_project/DoogOS/sysroot -isystem=/usr/include -c libc/string/strstr.c -o libc/string/strstr.libc.o -std=gnu11 -O2 -g -ffreestanding -Wall -Wextra
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
