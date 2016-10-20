#include <kernel/tty.h>

extern void mov_cursor(int);
extern size_t t_row;
extern size_t t_column;

void update_cursor(void) {
    size_t pos = t_row * 80 + t_column;
    mov_cursor(pos);
}
