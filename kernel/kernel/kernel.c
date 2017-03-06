#include <kernel/tty.h>
#include <kernel/kernel.h>
#include <kernel/mem.h>
#include <string.h>

// THIS FUNCTION IS TEMPORARY
void delay(size_t x) {
    for(volatile size_t i = 0; i < x; i++) {
        for(volatile size_t j = 0; j < 1000000; j++)
            ;
    }
}



void kernel_main(void) {
    init_heap();

    printk("testing kmalloc\n");
    volatile int* int_arr = kmalloc(sizeof(*int_arr) * 32);
    for (int i = 0; i < 32; i++) {
        int_arr[i] = i;
    }
    volatile char* heap_str = kmalloc(sizeof(*heap_str) * 16);
    char* conststr = "hello world";
    for (int i = 0; i < strlen(conststr); i++) {
        heap_str[i] = conststr[i];
    }
    heap_str[11] = 0;
    volatile int* another_int_arr = kmalloc(sizeof(*another_int_arr) * 200);
    for (int i = 0; i < 500; i++) {
        another_int_arr[i] = i;
    }
    for(int i = 0; i < 32; i++) {
        printk("%d ", int_arr[i]);
    }
    printk("\n");
    printk("%s\n", heap_str);
    for(int i = 0; i < 200; i++) {
        printk("%d ", another_int_arr[i]);
    }
    printk("\n");
    printk("int_arr: %p\n", int_arr);
    printk("heap_str: %p\n", heap_str);
    printk("another_int_arr: %p\n", another_int_arr);
    //printk("Welcome to DoogOS! Have fun doing nothing!\n");

    for (;;);
}
