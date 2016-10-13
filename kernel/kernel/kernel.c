#include <kernel/tty.h>

void kernel_main(void) {
    t_writestr("Hello kernel world!\n");
    t_writestr("blahblahblah\n");
    t_writestr("l\no\nl\no\nl\no\nl\n");
}
