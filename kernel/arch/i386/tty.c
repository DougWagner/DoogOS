#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>

#include "vga.h"

// Terminal constants
static const size_t T_WIDTH = 80;
static const size_t T_HEIGHT = 25;
static const uint8_t DEFAULT_COLOR = VGA_LIGHT_GREY | VGA_BLACK << 4; // fg is light grey, bg is black (this does the same thing as vga_entry_color for default color)
static uint16_t* const T_MEMORY = (uint16_t*) 0xB8000;

// Terminal location variables

static size_t t_row;
static size_t t_column;
static uint8_t t_color;
static uint16_t* t_buffer;

// u16memset prototype
void* u16memset(void*, int, size_t);

void t_init(void) {
    t_row = 0;
    t_column = 0;
    t_color = DEFAULT_COLOR; //vga_entry_color(VGA_LIGHT_GREY, VGA_BLACK);
    t_buffer = T_MEMORY;
    u16memset(t_buffer, vga_entry(' ', DEFAULT_COLOR), T_WIDTH * T_HEIGHT);
    //for (size_t i = 0; i < T_WIDTH * T_HEIGHT; i++)
    //    t_buffer[i] = vga_entry(' ', t_color);
}

void t_putchar(char c) {
    if (c != '\n') {
        const size_t idx = t_row * T_WIDTH + t_column++;
        t_buffer[idx] = vga_entry(c, t_color);
    }
    else {
        t_column = 0;
        t_row++;
    }
    if (t_column == T_WIDTH) {
        t_column = 0;
        t_row++;
    }
    if (t_row == T_HEIGHT)
        t_scroll();
    update_cursor(t_row, t_column);
    // TODO: make case for '\r'
}

void t_write(const char* str, size_t size) {
    for (size_t i = 0; i < size; i++)
        t_putchar(str[i]);
}

void t_writestr(const char* str) {
    t_write(str, strlen(str));
}

// this is ugly but whatever
void t_scroll(void) {
    memmove(t_buffer, t_buffer + T_WIDTH, (T_WIDTH * (T_HEIGHT - 1)) * 2);
    u16memset(t_buffer + ((T_WIDTH * (T_HEIGHT - 1))), vga_entry(' ', DEFAULT_COLOR), T_WIDTH);
    t_row--;
}

void t_setcolor(uint8_t color) {
    t_color = color;
}

void t_defaultcolor(void) {
    t_color = DEFAULT_COLOR;
}

// 16 bit memset - this will probably move somewhere else in the future
void* u16memset(void* s, int c, size_t n) {
    uint16_t* dst = (uint16_t*) s;
    for (size_t i = 0; i < n; i++) {
        *(dst++) = (uint16_t) c;
    }
    return s;
}
