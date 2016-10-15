#include <kernel/tty.h>

// THIS FUNCTION IS TEMPORARY
void delay(size_t x) {
    for(volatile size_t i = 0; i < x; i++) {
        for(volatile size_t j = 0; j < 1000000; j++)
            ;
    }
}

void kernel_main(void) {
    t_writestr("Hello kernel world!\n");
    t_writestr("blahblahblah\n");
    char* str = "abcdefghijklmnopqrstuvwxyz";
    char current[2];
    current[1] = 0;
    for (size_t i = 0;;i++) {
        current[0] = str[i % 26];
        t_writestr(current);
        delay(1);
    }
    /*for (int i = 1; i < 16; i++) {
        t_setcolor(vga_entry_color(i, VGA_BLACK));
        t_writestr("wheeeeeeeee");
    }*/
}
