#include <stdint.h>
#include <string.h>
#include <kernel/kernel.h>

#include "idt.h"

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
    void (*func)(void) = irq_funcs[frame->int_num - 32];
    if (func != 0) {
        func();
    }
}
