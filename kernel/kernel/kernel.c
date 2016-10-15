#include <kernel/tty.h>

void delay() {
    for(volatile size_t i = 0; i < 1000000; i++);
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
        delay();
    }
    /*for (int i = 1; i < 16; i++) {
        t_setcolor(vga_entry_color(i, VGA_BLACK));
        t_writestr("wheeeeeeeee");
    }*/
}
