echo "nav to current directory and open gdb in separate terminal to debug"
echo "enter \"target remote localhost:1234\" in gdb"
echo "then enter \"symbol-file DoogOS.kernel\" in gdb"
if [[ "$1" == "-k" ]]; then
    qemu-system-i386 -kernel DoogOS.kernel -s -S
else
    qemu-system-i386 -cdrom DoogOS.iso -s -S
fi
