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

size_t t_row;
size_t t_column;
static uint8_t t_color;
static uint16_t* t_buffer;

// u16memset prototype
static void* u16memset(void*, int, size_t);

void t_init(void) {
    t_row = 0;
    t_column = 0;
    t_color = DEFAULT_COLOR; //vga_entry_color(VGA_LIGHT_GREY, VGA_BLACK);
    t_buffer = T_MEMORY;
    u16memset(t_buffer, vga_entry(' ', DEFAULT_COLOR), T_WIDTH * T_HEIGHT);
}

static void t_putentry(size_t idx, char c) {
    t_buffer[idx] = vga_entry(c, t_color);
}

static void t_defaultcolor_putentry(size_t idx, char c) {
    t_buffer[idx] = vga_entry(c, DEFAULT_COLOR);
}

// this is ugly but whatever
static void t_scroll(void) {
    memmove(t_buffer, t_buffer + T_WIDTH, (T_WIDTH * (T_HEIGHT - 1)) * 2);
    u16memset(t_buffer + ((T_WIDTH * (T_HEIGHT - 1))), vga_entry(' ', DEFAULT_COLOR), T_WIDTH);
    t_row--;
}

void t_putchar(char c) {
    const size_t idx = t_row * T_WIDTH + t_column;
    switch (c) {
    case '\n':
        t_setcolor(vga_entry_color(VGA_BLACK, VGA_BLACK));
        t_putentry(idx, '\n'); // place newline character with complete black color
        t_defaultcolor(); // reset terminal color
        t_column = 0;
        t_row++;
        break;
    case '\t':
        t_column += 8 - (t_column % 8);
        break;
    case '\b':
        if (idx == 0)
            break;
        else if (t_column == 0) { // locate newline character on previous line
            void* rowstart = t_buffer + ((t_row - 1) * T_WIDTH);
            void* nextrowstart = t_buffer + (t_row * T_WIDTH);
            void* loc = memchr(rowstart, '\n', nextrowstart - rowstart);
            // the following 3 lines don't work because they are probably completely wrong
            //while (loc != NULL && (uint32_t) loc % 2 == 0) {
            //    loc = memchr(loc + 1, '\n', nextrowstart - loc);
            //}
            if (loc != NULL) {
                t_column = (loc - rowstart) / 2;
                t_row--;
                t_defaultcolor_putentry(t_row * T_WIDTH + t_column, ' ');
            }
            else {
                t_column = T_WIDTH - 1;
                t_row--;
                t_defaultcolor_putentry(idx - 1, ' ');
            }
        }
        else {
            t_defaultcolor_putentry(idx - 1, ' ');
            t_column--;
        }
        break;
    default:
        t_putentry(idx, c);
        t_column++;
        break;
    }
    if (t_column == T_WIDTH) {
        t_column = 0;
        t_row++;
    }
    if (t_row == T_HEIGHT)
        t_scroll();
    update_cursor();
}

void t_write(const char* str, size_t size) {
    for (size_t i = 0; i < size; i++)
        t_putchar(str[i]);
}

void t_writestr(const char* str) {
    t_write(str, strlen(str));
}

void t_setcolor(uint8_t color) {
    t_color = color;
}

void t_defaultcolor(void) {
    t_color = DEFAULT_COLOR;
}

// 16 bit memset - this might move somewhere else in the future
static void* u16memset(void* s, int c, size_t n) {
    uint16_t* dst = (uint16_t*) s;
    for (size_t i = 0; i < n; i++) {
        *(dst++) = (uint16_t) c;
    }
    return s;
}
