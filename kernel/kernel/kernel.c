#include <kernel/tty.h>
#include <kernel/kernel.h>
#include <string.h>

// THIS FUNCTION IS TEMPORARY
void delay(size_t x) {
    for(volatile size_t i = 0; i < x; i++) {
        for(volatile size_t j = 0; j < 1000000; j++)
            ;
    }
}



void kernel_main(void) {
    printk("Welcome to DoogOS! Have fun doing nothing!\n");
    
    for (;;);
}
