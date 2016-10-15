#include <kernel/tty.h>

extern void mov_cursor(int);

void update_cursor(size_t y, size_t x) {
    size_t pos = y * 80 + x;
    mov_cursor(pos);
}
