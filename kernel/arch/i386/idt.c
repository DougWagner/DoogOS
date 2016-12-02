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

extern void idt_flush(uint64_t*, uint16_t);
extern void remap_irq();

void load_idt(void) {
    idt_init();
    remap_irq();
    install_isrs();
    install_irqs();
    idt_flush(IDT, sizeof(IDT));
}
