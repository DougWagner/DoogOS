#ifndef KERNEL_TTY_H
#define KERNEL_TTY_H

#include <stddef.h>
#include <stdint.h>

void t_init(void);
void t_putchar(char);
void t_write(const char*, size_t);
void t_writestr(const char*);
void t_writeint(int); // TEMPORARY
void t_scroll(void);
void t_setcolor(uint8_t);
void t_defaultcolor(void);
void update_cursor(size_t, size_t);

extern int asm_add(int, int);

#endif
