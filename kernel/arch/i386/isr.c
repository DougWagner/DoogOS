#include <stdint.h>
#include <string.h>
#include <kernel/kernel.h>

#include "idt.h"

char* exceptions[] = {
    "Divide-by-zero",               // ISR0
    "Debug",                        // ISR1
    "Non-Maskable Interrupt",       // ISR2
    "Breakpoint",                   // ISR3
    "Overflow",                     // ISR4
    "Bound Range Exceeded",         // ISR5
    "Invalid Opcode",               // ISR6
    "Device Not Available",         // ISR7
    "Double Fault",                 // ISR8
    "Coprocessor Segment Overrun",  // ISR9
    "Invalid TSS",                  // ISR10
    "Segment Not Present",          // ISR11
    "Stack-Segment Fault",          // ISR12
    "General Protection Fault",     // ISR13
    "Page Fault",                   // ISR14
    "Reserved15",                   // ISR15
    "x87 Floating Point",           // ISR16
    "Alignment Check",              // ISR17
    "Machine Check",                // ISR18
    "SIMD Floating Point",          // ISR19
    "Reserved20",                   // ISR20
    "Reserved21",                   // ISR21
    "Reserved22",                   // ISR22
    "Reserved23",                   // ISR23
    "Reserved24",                   // ISR24
    "Reserved25",                   // ISR25
    "Reserved26",                   // ISR26
    "Reserved27",                   // ISR27
    "Reserved28",                   // ISR28
    "Reserved29",                   // ISR29
    "Reserved30",                   // ISR30
    "Reserved31"                    // ISR31
};

void* isr_funcs[32] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

// ISR Function Pointers
extern void ISR0();
extern void ISR1();
extern void ISR2();
extern void ISR3();
extern void ISR4();
extern void ISR5();
extern void ISR6();
extern void ISR7();
extern void ISR8();
extern void ISR9();
extern void ISR10();
extern void ISR11();
extern void ISR12();
extern void ISR13();
extern void ISR14();
extern void ISR15();
extern void ISR16();
extern void ISR17();
extern void ISR18();
extern void ISR19();
extern void ISR20();
extern void ISR21();
extern void ISR22();
extern void ISR23();
extern void ISR24();
extern void ISR25();
extern void ISR26();
extern void ISR27();
extern void ISR28();
extern void ISR29();
extern void ISR30();
extern void ISR31();

void install_isrs(void) {
    install_idt_entry(0, (uint32_t)&ISR0, 0x8, 0x8e);
    install_idt_entry(1, (uint32_t)&ISR1, 0x8, 0x8e);
    install_idt_entry(2, (uint32_t)&ISR2, 0x8, 0x8e);
    install_idt_entry(3, (uint32_t)&ISR3, 0x8, 0x8e);
    install_idt_entry(4, (uint32_t)&ISR4, 0x8, 0x8e);
    install_idt_entry(5, (uint32_t)&ISR5, 0x8, 0x8e);
    install_idt_entry(6, (uint32_t)&ISR6, 0x8, 0x8e);
    install_idt_entry(7, (uint32_t)&ISR7, 0x8, 0x8e);
    install_idt_entry(8, (uint32_t)&ISR8, 0x8, 0x8e);
    install_idt_entry(9, (uint32_t)&ISR9, 0x8, 0x8e);
    install_idt_entry(10, (uint32_t)&ISR10, 0x8, 0x8e);
    install_idt_entry(11, (uint32_t)&ISR11, 0x8, 0x8e);
    install_idt_entry(12, (uint32_t)&ISR12, 0x8, 0x8e);
    install_idt_entry(13, (uint32_t)&ISR13, 0x8, 0x8e);
    install_idt_entry(14, (uint32_t)&ISR14, 0x8, 0x8e);
    install_idt_entry(15, (uint32_t)&ISR15, 0x8, 0x8e);
    install_idt_entry(16, (uint32_t)&ISR16, 0x8, 0x8e);
    install_idt_entry(17, (uint32_t)&ISR17, 0x8, 0x8e);
    install_idt_entry(18, (uint32_t)&ISR18, 0x8, 0x8e);
    install_idt_entry(19, (uint32_t)&ISR19, 0x8, 0x8e);
    install_idt_entry(20, (uint32_t)&ISR20, 0x8, 0x8e);
    install_idt_entry(21, (uint32_t)&ISR21, 0x8, 0x8e);
    install_idt_entry(22, (uint32_t)&ISR22, 0x8, 0x8e);
    install_idt_entry(23, (uint32_t)&ISR23, 0x8, 0x8e);
    install_idt_entry(24, (uint32_t)&ISR24, 0x8, 0x8e);
    install_idt_entry(25, (uint32_t)&ISR25, 0x8, 0x8e);
    install_idt_entry(26, (uint32_t)&ISR26, 0x8, 0x8e);
    install_idt_entry(27, (uint32_t)&ISR27, 0x8, 0x8e);
    install_idt_entry(28, (uint32_t)&ISR28, 0x8, 0x8e);
    install_idt_entry(29, (uint32_t)&ISR29, 0x8, 0x8e);
    install_idt_entry(30, (uint32_t)&ISR30, 0x8, 0x8e);
    install_idt_entry(31, (uint32_t)&ISR31, 0x8, 0x8e);
}

void isr_handler(struct stack_frame* frame) {
    printk("ISR %d triggered: %s. error code: %d\n"/*System halted\n"*/, frame->int_num, exceptions[frame->int_num], frame->error_code);
    void (*func)(void) = isr_funcs[frame->int_num];
    if (func != 0) {
        func();
    }
    else {
        printk("System halted");
        for (;;);
    }
}

