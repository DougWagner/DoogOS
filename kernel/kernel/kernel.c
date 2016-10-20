#include <kernel/tty.h>
#include <string.h>

// THIS FUNCTION IS TEMPORARY
void delay(size_t x) {
    for(volatile size_t i = 0; i < x; i++) {
        for(volatile size_t j = 0; j < 1000000; j++)
            ;
    }
}



void kernel_main(void) {
    t_writestr("Welcome to DoogOS! Have fun doing nothing!\n");
    char* alpha = "abcdefghijklmnopqrstuvwxyz";
    char current[2];
    current[1] = 0;
    for (size_t i = 0;;i++) {
        current[0] = alpha[i % 26];
        t_writestr(current);
        //delay(1);
    }
}
