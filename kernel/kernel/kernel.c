#include <kernel/tty.h>

void kernel_main(void) {
    t_writestr("Hello kernel world!\n");
    t_writestr("blahblahblah\n");
    int x = asm_add(25, 50);
    t_writeint(x);
    /*for (int i = 1; i < 16; i++) {
        t_setcolor(vga_entry_color(i, VGA_BLACK));
        t_writestr("wheeeeeeeee");
    }*/
}
