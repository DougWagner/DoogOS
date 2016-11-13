#include <stdint.h>
#include <string.h>
#include <kernel/kernel.h>

#include "idt.h"

uint64_t IDT[256];

static void idt_init(void) {
    memset(IDT, 0, sizeof(IDT));
}

static int check_type(uint8_t type) {
    uint8_t int_type = type & 0xf;
    uint8_t int_attr = (type >> 4) & 0xf;
    switch (int_type) {
    case TASK_GATE_32:
    case INT_GATE_16:
    case TRAP_GATE_16:
    case INT_GATE_32:
    case TRAP_GATE_32:
        break;
    default:
        return 0;
    }
    switch (int_attr) {
    case INTGATE_HIGH:
    case INTGATE_LOW:
    case REGGATE_HIGH:
    case REGGATE_LOW:
        break;
    default:
        return 0;
    }
    return 1;
}

static uint64_t generate_idt_entry(uint32_t offset, uint16_t selector, uint8_t type) {
    if (!check_type(type)) {
        return 0;
    }
    uint64_t entry;
    uint8_t* entry_buffer = (uint8_t*) &entry;
    // load offset
    entry_buffer[0] = offset & 0xff;
    entry_buffer[1] = (offset >> 8) & 0xff;
    entry_buffer[6] = (offset >> 16) & 0xff;
    entry_buffer[7] = (offset >> 24) & 0xff;
    // load selector
    entry_buffer[2] = selector & 0xff;
    entry_buffer[3] = (selector >> 8) & 0xff;
    // load type
    entry_buffer[5] = type;
    // index 4 is always 0
    entry_buffer[4] = 0;
    return entry;
}

void install_idt_entry(size_t idt_idx, uint32_t offset, uint16_t selector, uint8_t type) {
    uint64_t entry = generate_idt_entry(offset, selector, type);
    if (entry != 0) {
        IDT[idt_idx] = generate_idt_entry(offset, selector, type);
    }
}

/*
static void set_interrupts(void) {
    IDT[0] = generate_idt_entry((uint32_t)&ISR0, 0x8, 0x8e);
    IDT[1] = generate_idt_entry((uint32_t)&ISR1, 0x8, 0x8e);
    IDT[2] = generate_idt_entry((uint32_t)&ISR2, 0x8, 0x8e);
    IDT[3] = generate_idt_entry((uint32_t)&ISR3, 0x8, 0x8e);
    IDT[4] = generate_idt_entry((uint32_t)&ISR4, 0x8, 0x8e);
    IDT[5] = generate_idt_entry((uint32_t)&ISR5, 0x8, 0x8e);
    IDT[6] = generate_idt_entry((uint32_t)&ISR6, 0x8, 0x8e);
    IDT[7] = generate_idt_entry((uint32_t)&ISR7, 0x8, 0x8e);
    IDT[8] = generate_idt_entry((uint32_t)&ISR8, 0x8, 0x8e);
    IDT[9] = generate_idt_entry((uint32_t)&ISR9, 0x8, 0x8e);
    IDT[10] = generate_idt_entry((uint32_t)&ISR10, 0x8, 0x8e);
    IDT[11] = generate_idt_entry((uint32_t)&ISR11, 0x8, 0x8e);
    IDT[12] = generate_idt_entry((uint32_t)&ISR12, 0x8, 0x8e);
    IDT[13] = generate_idt_entry((uint32_t)&ISR13, 0x8, 0x8e);
    IDT[14] = generate_idt_entry((uint32_t)&ISR14, 0x8, 0x8e);
    IDT[15] = generate_idt_entry((uint32_t)&ISR15, 0x8, 0x8e);
    IDT[16] = generate_idt_entry((uint32_t)&ISR16, 0x8, 0x8e);
    IDT[17] = generate_idt_entry((uint32_t)&ISR17, 0x8, 0x8e);
    IDT[18] = generate_idt_entry((uint32_t)&ISR18, 0x8, 0x8e);
    IDT[19] = generate_idt_entry((uint32_t)&ISR19, 0x8, 0x8e);
    IDT[20] = generate_idt_entry((uint32_t)&ISR20, 0x8, 0x8e);
    IDT[21] = generate_idt_entry((uint32_t)&ISR21, 0x8, 0x8e);
    IDT[22] = generate_idt_entry((uint32_t)&ISR22, 0x8, 0x8e);
    IDT[23] = generate_idt_entry((uint32_t)&ISR23, 0x8, 0x8e);
    IDT[24] = generate_idt_entry((uint32_t)&ISR24, 0x8, 0x8e);
    IDT[25] = generate_idt_entry((uint32_t)&ISR25, 0x8, 0x8e);
    IDT[26] = generate_idt_entry((uint32_t)&ISR26, 0x8, 0x8e);
    IDT[27] = generate_idt_entry((uint32_t)&ISR27, 0x8, 0x8e);
    IDT[28] = generate_idt_entry((uint32_t)&ISR28, 0x8, 0x8e);
    IDT[29] = generate_idt_entry((uint32_t)&ISR29, 0x8, 0x8e);
    IDT[30] = generate_idt_entry((uint32_t)&ISR30, 0x8, 0x8e);
    IDT[31] = generate_idt_entry((uint32_t)&ISR31, 0x8, 0x8e);
    IDT[32] = generate_idt_entry((uint32_t)&IRQ0, 0x8, 0x8e);
    IDT[33] = generate_idt_entry((uint32_t)&IRQ1, 0x8, 0x8e);
    IDT[34] = generate_idt_entry((uint32_t)&IRQ2, 0x8, 0x8e);
    IDT[35] = generate_idt_entry((uint32_t)&IRQ3, 0x8, 0x8e);
    IDT[36] = generate_idt_entry((uint32_t)&IRQ4, 0x8, 0x8e);
    IDT[37] = generate_idt_entry((uint32_t)&IRQ5, 0x8, 0x8e);
    IDT[38] = generate_idt_entry((uint32_t)&IRQ6, 0x8, 0x8e);
    IDT[39] = generate_idt_entry((uint32_t)&IRQ7, 0x8, 0x8e);
    IDT[40] = generate_idt_entry((uint32_t)&IRQ8, 0x8, 0x8e);
    IDT[41] = generate_idt_entry((uint32_t)&IRQ9, 0x8, 0x8e);
    IDT[42] = generate_idt_entry((uint32_t)&IRQ10, 0x8, 0x8e);
    IDT[43] = generate_idt_entry((uint32_t)&IRQ11, 0x8, 0x8e);
    IDT[44] = generate_idt_entry((uint32_t)&IRQ12, 0x8, 0x8e);
    IDT[45] = generate_idt_entry((uint32_t)&IRQ13, 0x8, 0x8e);
    IDT[46] = generate_idt_entry((uint32_t)&IRQ14, 0x8, 0x8e);
    IDT[47] = generate_idt_entry((uint32_t)&IRQ15, 0x8, 0x8e);
}
*/

extern void idt_flush(uint64_t*, uint16_t);
extern void remap_irq();

void load_idt(void) {
    idt_init();
    remap_irq();
    //set_interrupts();
    install_isrs();
    install_irqs();
    idt_flush(IDT, sizeof(IDT));
}

//void request_handler(struct stack_frame* frame) {

