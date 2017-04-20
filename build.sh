#!/bin/bash
# this only exists because i don't know makefiles

function cleanup
{
    if [ $NOCLEAN = false ]; then
        echo "cleaning up our mess"
        rm $I386DIR/*.o
        rm $KERNELDIR/*.o
        rm libc/*/*.o
        rm libc.a
        rm -rf sysroot
        rm -rf iso
    fi
}

function testcomp
{
    if [ $? -ne 0 ]; then
        echo "Compilation failed - terminating"
        cleanup
        exit 1
    fi
}

NOCLEAN=false
if [ $# -gt 1 ]; then
    echo "too many arguments"
    exit 1
fi
if [ $# -eq 1 ]; then
    if [ $1 == "-noclean" ]; then
        NOCLEAN=true
    else
        echo "Usage: ./build.sh -noclean"
        exit 1
    fi
fi

PWD=$(pwd)
SYSROOT=$PWD/sysroot

I386DIR=kernel/arch/i386
KERNELDIR=kernel/kernel
I386SFILES=("boot" "gdt_flush" "idt_flush" "paging" "mov_cursor" "isr" "irq") # add any i386 .s filenames here
I386CFILES=("gdt" "idt" "isr" "irq" "paging" "mem" "tty" "cursor") # add any i386 .c filenames here
KERNELFILES=("printk" "kernel") # add any kernel .c filenames here
SOBJEX="_s"
COBJEX="_c"

PREARGS="--sysroot=$SYSROOT -isystem=/usr/include"
CARGS="-std=gnu11"
ARGS="-O2 -g -ffreestanding -Wall -Wextra -fdiagnostics-color=always -DARCH_I386 -DSRAND=$RANDOM"

# copy include directories into sysroot
echo "copying headers to sysroot/usr/include"
mkdir -p sysroot/usr/include
cp -R --preserve=timestamps libc/include/. sysroot/usr/include
cp -R --preserve=timestamps kernel/include/. sysroot/usr/include

# build libc.a
echo
echo "building libc.a"
LIBCOBJ=""
for FILE in libc/*/*.c; do
    echo "i686-elf-gcc $PREARGS -c ${FILE} -o ${FILE%c}libc.o $CARGS $ARGS"
    i686-elf-gcc $PREARGS -c ${FILE} -o ${FILE%c}libc.o $CARGS $ARGS
    testcomp
    LIBCOBJ="$LIBCOBJ ${FILE%c}libc.o"
done
echo "i686-elf-ar rcs libc.a $LIBCOBJ"
i686-elf-ar rcs libc.a $LIBCOBJ
testcomp

# copy libc.a into sysroot
echo
echo "copying libc.a to sysroot/usr/lib"
mkdir -p sysroot/usr/lib
cp libc.a sysroot/usr/lib

# build kernel
echo
echo "building DoogOS.kernel"

# build crti and crtbegin
echo "i686-elf-gcc $PREARGS -c $I386DIR/crti.s -o $I386DIR/crti.o $ARGS"
i686-elf-gcc $PREARGS -c $I386DIR/crti.s -o $I386DIR/crti.o $ARGS
testcomp
OBJ=`i686-elf-gcc $PREARGS $ARGS -print-file-name=crtbegin.o` && cp "$OBJ" $I386DIR/crtbegin.o
testcomp
echo "OBJ='i686-elf-gcc $PREARGS $ARGS -print-file-name=crtbegin.o' && cp "$OBJ" $I386DIR/crtbegin.o"
LINKSTR="$I386DIR/crti.o $I386DIR/crtbegin.o"

# i don't use *.c for the following loops because (i think) they need to be linked in a specific order
# compile i386 .s files
for FILE in ${I386SFILES[@]}; do
    echo "i686-elf-gcc $PREARGS -c $I386DIR/$FILE.s -o $I386DIR/$FILE$SOBJEX.o $ARGS"
    i686-elf-gcc $PREARGS -c $I386DIR/$FILE.s -o $I386DIR/$FILE$SOBJEX.o $ARGS
    testcomp
    LINKSTR="$LINKSTR $I386DIR/$FILE$SOBJEX.o"
done

# compile i386 .c files
for FILE in ${I386CFILES[@]}; do
    echo "i686-elf-gcc $PREARGS -c $I386DIR/$FILE.c -o $I386DIR/$FILE$COBJEX.o $CARGS $ARGS"
    i686-elf-gcc $PREARGS -c $I386DIR/$FILE.c -o $I386DIR/$FILE$COBJEX.o $CARGS $ARGS
    testcomp
    LINKSTR="$LINKSTR $I386DIR/$FILE$COBJEX.o"
done

# compile kernel .c files
for FILE in ${KERNELFILES[@]}; do
    echo "i686-elf-gcc $PREARGS -c $KERNELDIR/$FILE.c -o $KERNELDIR/$FILE$COBJEX.o $CARGS $ARGS"
    i686-elf-gcc $PREARGS -c $KERNELDIR/$FILE.c -o $KERNELDIR/$FILE$COBJEX.o $CARGS $ARGS
    testcomp
    LINKSTR="$LINKSTR $KERNELDIR/$FILE$COBJEX.o"
done

# build crtend and crtn
OBJ=`i686-elf-gcc $PREARGS $ARGS -print-file-name=crtend.o` && cp "$OBJ" $I386DIR/crtend.o
testcomp
echo "OBJ='i686-elf-gcc $PREARGS $ARGS -print-file-name=crtend.o' && cp "$OBJ" $I386DIR/crtend.o"
echo "i686-elf-gcc $PREARGS -c $I386DIR/crtn.s -o $I386DIR/crtn.o $ARGS"
i686-elf-gcc $PREARGS -c $I386DIR/crtn.s -o $I386DIR/crtn.o $ARGS
testcomp
LINKSTR="$LINKSTR -nostdlib -lc -lgcc $I386DIR/crtend.o $I386DIR/crtn.o"

# link everything
echo "i686-elf-gcc $PREARGS -T $I386DIR/linker.ld -o DoogOS.kernel $ARGS $LINKSTR"
i686-elf-gcc $PREARGS -T $I386DIR/linker.ld -o DoogOS.kernel $ARGS $LINKSTR
testcomp

# we have our kernel binary! (if there were no errors)
echo
echo "compilation done"

# copy kernel into sysroot boot directory
echo
echo "copying DoogOS.kernel into sysroot/boot"
mkdir -p sysroot/boot
cp DoogOS.kernel sysroot/boot

# create bootable .iso from sysroot
echo
echo "making .iso image"
mkdir -p iso/boot/grub
cp sysroot/boot/DoogOS.kernel iso/boot
cat > iso/boot/grub/grub.cfg << EOF
menuentry "DoogOS" {
    multiboot /boot/DoogOS.kernel
}
EOF
grub-mkrescue -o DoogOS.iso iso

# time to clean up
cleanup
