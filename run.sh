if [[ "$1" == "-k" ]]; then
    qemu-system-i386 -kernel DoogOS.kernel
else
    qemu-system-i386 -cdrom DoogOS.iso
fi
