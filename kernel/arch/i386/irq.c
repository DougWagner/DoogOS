#include <stdint.h>
#include <string.h>
#include <kernel/kernel.h>
#include <kernel/tty.h>

#include "idt.h"

void keyboard_handler();

// IRQ function Pointers
extern void IRQ0();
extern void IRQ1();
extern void IRQ2();
extern void IRQ3();
extern void IRQ4();
extern void IRQ5();
extern void IRQ6();
extern void IRQ7();
extern void IRQ8();
extern void IRQ9();
extern void IRQ10();
extern void IRQ11();
extern void IRQ12();
extern void IRQ13();
extern void IRQ14();
extern void IRQ15();

void* irq_funcs[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

void install_irqs(void) {
    install_idt_entry(32, (uint32_t)&IRQ0, 0x8, 0x8e);
    install_idt_entry(33, (uint32_t)&IRQ1, 0x8, 0x8e);
    irq_funcs[1] = &keyboard_handler;
    install_idt_entry(34, (uint32_t)&IRQ2, 0x8, 0x8e);
    install_idt_entry(35, (uint32_t)&IRQ3, 0x8, 0x8e);
    install_idt_entry(36, (uint32_t)&IRQ4, 0x8, 0x8e);
    install_idt_entry(37, (uint32_t)&IRQ5, 0x8, 0x8e);
    install_idt_entry(38, (uint32_t)&IRQ6, 0x8, 0x8e);
    install_idt_entry(39, (uint32_t)&IRQ7, 0x8, 0x8e);
    install_idt_entry(40, (uint32_t)&IRQ8, 0x8, 0x8e);
    install_idt_entry(41, (uint32_t)&IRQ9, 0x8, 0x8e);
    install_idt_entry(42, (uint32_t)&IRQ10, 0x8, 0x8e);
    install_idt_entry(43, (uint32_t)&IRQ11, 0x8, 0x8e);
    install_idt_entry(44, (uint32_t)&IRQ12, 0x8, 0x8e);
    install_idt_entry(45, (uint32_t)&IRQ13, 0x8, 0x8e);
    install_idt_entry(46, (uint32_t)&IRQ14, 0x8, 0x8e);
    install_idt_entry(47, (uint32_t)&IRQ15, 0x8, 0x8e);
}

void irq_handler(struct stack_frame* frame) {
    //printk("irq %d triggered\n", frame->int_num);
    void (*func)(void) = irq_funcs[frame->int_num];
    if (func != 0) {
        func();
    }
}

// PS/2 scancode set 1 - index = pressed, index + 0x80 = released
char scancode_list[128] = {
    0, 27, '1', '2',        // 0x00 - 0x03 -> 0x01: escape (27)
    '3', '4', '5', '6',     // 0x04 - 0x07
    '7', '8', '9', '0',     // 0x08 - 0x0b
    '-', '=', 8, 9,         // 0x0c - 0x0f -> 0x0e: backspace (8), 0x0f: tab (9)
    'q', 'w', 'e', 'r',     // 0x10 - 0x13
    't', 'y', 'u', 'i',     // 0x14 - 0x17
    'o', 'p', '[', ']',     // 0x18 - 0x1b
    0, 0, 'a', 's',         // 0x1c - 0x1f -> 0x1c: enter, 0x1d: left ctrl
    'd', 'f', 'g', 'h',     // 0x20 - 0x23
    'j', 'k', 'l', ';',     // 0x24 - 0x27
    '\'', '`', 0, '\\',     // 0x28 - 0x2b -> 0x2a: left shift
    'z', 'x', 'c', 'v',     // 0x2c - 0x2f
    'b', 'n', 'm', ',',     // 0x30 - 0x33
    '.', '/', 0, 0,         // 0x34 - 0x37 -> 0x36: right shift, 0x37: keypad * (not implemented here yet)
    0, ' ', 0, 0,           // 0x38 - 0x3b -> 0x38: left alt, 0x3a: capslock, 0x3b: F1
    0, 0, 0, 0,             // 0x3c - 0x3f -> 0x3c: F2, 0x3d: F3, 0x3e: F4, 0x3f: F5
    0, 0, 0, 0,             // 0x40 - 0x43 -> 0x40: F6, 0x41: F7, 0x42: F8, 0x43: F9
    0, 0, 0, 0,             // 0x44 - 0x47 -> 0x44: F10, 0x45: Num Lock, 0x46: Scroll Lock, 0x47: keypad 7
    0, 0, 0, 0,             // 0x48 - 0x4b -> 0x48: keypad 8, 0x49: keypad 9, 0x4a: keypad -, 0x4b: keypad 4
    0, 0, 0, 0,             // 0x4c - 0x4f -> 0x4c: keypad 5, 0x4d: keypad 6, 0x4e: keypad +, 0x4f: keypad 1
    0, 0, 0, 0,             // 0x50 - 0x53 -> 0x50: keypad 2, 0x51: keypad 3, 0x52: keypad 0, 0x53: keypad .
    0, 0, 0, 0,             // 0x54 - 0x57 -> 0x57: F11
    0, 0, 0, 0,             // 0x58 - 0x5b -> 0x58: F12
    0, 0, 0, 0,             // 0x5c - 0x5f -> unused
    0, 0, 0, 0,             // 0x60 - 0x63 -> unused
    0, 0, 0, 0,             // 0x64 - 0x67 -> unused
    0, 0, 0, 0,             // 0x68 - 0x6b -> unused
    0, 0, 0, 0,             // 0x6c - 0x6f -> unused
    0, 0, 0, 0,             // 0x70 - 0x73 -> unused
    0, 0, 0, 0,             // 0x74 - 0x77 -> unused
    0, 0, 0, 0,             // 0x78 - 0x7b -> unused
    0, 0, 0, 0              // 0x7c - 0x7f -> unused
};

extern unsigned char get_scancode();

static unsigned char e0_code = 0;
static unsigned char lshift = 0;
static unsigned char rshift = 0;
static unsigned char lalt = 0;
static unsigned char ralt = 0;
static unsigned char lctrl = 0;
static unsigned char rctrl = 0;
static unsigned char capslock = 0;

static char shift_key(char c) {
    if (c <= 'z' && c >= 'a') {
        return c - 32;
    }
    else if (c <= 'Z' && c >= 'A') {
        return c + 32;
    }
    switch (c) {
    case '1':
        return '!';
    case '2':
        return '@';
    case '3':
        return '#';
    case '4':
        return '$';
    case '5':
        return '%';
    case '6':
        return '^';
    case '7':
        return '&';
    case '8':
        return '*';
    case '9':
        return '(';
    case '0':
        return ')';
    case '-':
        return '_';
    case '=':
        return '+';
    case '[':
        return '{';
    case ']':
        return '}';
    case '`':
        return '~';
    case '\\':
        return '|';
    case ';':
        return ':';
    case '\'':
        return '\"';
    case ',':
        return '<';
    case '.':
        return '>';
    case '/':
        return '?';
    default:
        return c;
    }
}

static char capslock_toggled(char c) {
    if (c <= 'z' && c >= 'a') {
        return c - 32;
    }
    else if (c <= 'Z' && c >= 'A') {
        return c + 32;
    }
    return c;
}

static void e0_nextcode(unsigned char sc) {
    switch (sc) {
    case 0x1c: // keypad enter
        break;
    case 0x1d: // right ctrl
        rctrl = 1;
        break;
    case 0x35: // keypad /
        break;
    case 0x38: // right alt
        ralt = 1;
        break;
    case 0x47: // home
        break;
    case 0x48: // cursor up
        break;
    case 0x49: // page up
        break;
    case 0x4b: // cursor left
        break;
    case 0x4d: // cursor right
        break;
    case 0x4f: // end
        break;
    case 0x50: // cursor down
        break;
    case 0x51: // page down
        break;
    case 0x52: // insert
        break;
    case 0x53: // delete
        break;
    case 0x5b: // left GUI
        break;
    case 0x5c: // right GUI
        break;
    case 0x5d: // "apps"
        break;
    case 0x9c: // keypad enter released
        break;
    case 0x9d: // right ctrl released
        rctrl = 0;
        break;
    case 0xb5: // keypad / released
        break;
    case 0xb8: // right alt released
        ralt = 0;
        break;
    case 0xc7: // home released
        break;
    case 0xc8: // cursor up released
        break;
    case 0xc9: // page up released
        break;
    case 0xcb: // cursor left released
        break;
    case 0xcd: // cursor right released
        break;
    case 0xcf: // end released
        break;
    case 0xd0: // cursor down released
        break;
    case 0xd1: // page down released
        break;
    case 0xd2: // insert released
        break;
    case 0xd3: // delete released
        break;
    case 0xdb: // right GUI released
        break;
    case 0xdc: // left GUI released
        break;
    case 0xdd: // "apps released
        break;
    default: // probably shouldn't be triggered.
        break;
    }
}

void keyboard_handler(void) {
    unsigned char sc = get_scancode();
    if (e0_code) {
        e0_nextcode(sc);
        e0_code = 0;
        return;
    }
    if (sc < 128) {
        char c = scancode_list[sc];
        switch (sc) {
        case 0x01: // escape button
            break;
        case 0x0e: // backspace
            t_putchar('\b');
            break;
        case 0x0f: // tab
            t_putchar('\t');
            break;
        case 0x1c: // enter
            t_putchar('\n');
            break;
        case 0x1d: // left ctrl
            lctrl = 1;
            break;
        case 0x2a: // left shift
            lshift = 1;
            break;
        case 0x36: // right shift
            rshift = 1;
            break;
        case 0x37: // keypad *
            break;
        case 0x38: // left alt
            lalt = 1;
            break;
        case 0x3a: // capslock
            if (capslock)
                capslock = 0;
            else
                capslock = 1;
            break;
        case 0x3b: // F1
            break;
        case 0x3c: // F2
            break;
        case 0x3d: // F3
            break;
        case 0x3e: // F4
            break;
        case 0x3f: // F5
            break;
        case 0x40: // F6
            break;
        case 0x41: // F7
            break;
        case 0x42: // F8
            break;
        case 0x43: // F9
            break;
        case 0x44: // F10
            break;
        case 0x45: // Num Lock
            break;
        case 0x46: // Scroll Lock
            break;
        case 0x47: // keypad 7
            break;
        case 0x48: // keypad 8
            break;
        case 0x49: // keypad 9
            break;
        case 0x4a: // keypad -
            break;
        case 0x4b: // keypad 4
            break;
        case 0x4c: // keypad 5
            break;
        case 0x4d: // keypad 6
            break;
        case 0x4e: // keypad +
            break;
        case 0x4f: // keypad 1
            break;
        case 0x50: // keypad 2
            break;
        case 0x51: // keypad 3
            break;
        case 0x52: // keypad 0
            break;
        case 0x53: // keypad .
            break;
        case 0x57: // F11
            break;
        case 0x58: // F12
            break;
        default:
            if (c == 0) {
                break;
            }
            if (capslock) {
                c = capslock_toggled(c);
            }
            if (lshift || rshift) {
                c = shift_key(c);
            }
            t_putchar(c);
            break;
        }
    }
    else {
        switch (sc) {
        case 0x9d: // left ctrl released
            lctrl = 0;
            break;
        case 0xaa: // left shift released
            lshift = 0;
            break;
        case 0xb6: // right shift released
            rshift = 0;
            break;
        case 0xb8: // left alt released
            lalt = 0;
            break;
        case 0xe0: // special scancode - 2nd interrupt should immediately trigger and return key pressed
            e0_code = 1;
            break;
        }
    }
    //printk("%x ", sc);
}

