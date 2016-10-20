#DoogOS

##About

A work-in-progress operating system for x86 architecture.

Currently all it does is prints some text to the terminal.

The build script is horrible and I plan on changing that in the future.

Code is inspired by tutorials at wiki.osdev.org, but not identical (I TRIED to do my own thing based on the principles there)

##Compiling and running DoogOS

###Compiling

In order to compile DoogOS, you will need a gcc ix86 cross-compiler with binutils. 
To get a cross compiler, [follow these steps](http://wiki.osdev.org/GCC_Cross-Compiler) on the osdev wiki.
The target architecture that I am using for building is i686, so you should probably use the same target.
If the cross compiler is not in your PATH environment variable, you may want to add it or modify the (terrible) build script.

In addition to a cross-compiler, DoogOS requires GRUB in order to make a bootable iso/disk.
The build script `build.sh` will execute the command `grub-mkrescue` which also requires an installation of xorriso in order to make the .iso file.
If there are any error/warning messages from gcc during the build script, the script will continue and attempt to make the .iso (because it's absolutely terrible), so if that happens, you probably should not run the iso in QEMU, and especially not on actual hardware.

###Running

In order to run DoogOS, the easiest way is to use QEMU.
I have not tested DoogOS with any other emulator/virtualizers.
The command to run DoogOS is `qemu-system-i386 -cdrom DoogOS.iso`.
QEMU will load the GRUB boot menu, so just select DoogOS and see the wonderful text printed to the screen.

###To summarize, compiling and running DoogOS requires the following:

* gcc i686 cross compiler
* i686 binutils
* GRUB
* xorriso
* QEMU ix86 emulator
