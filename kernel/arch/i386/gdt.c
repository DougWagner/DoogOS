#include <stdint.h>
#include <kernel/kernel.h>
#include "gdt.h"

uint64_t GDT[6];

tss_t TSS;

static uint64_t generate_gdt_entry(uint32_t base, uint32_t limit, uint8_t flags, uint8_t access) {
    if (limit > 0xfffff) {
        printk("limit too large\n");
        return GDT_ENTRY_ERROR;
    }
    uint64_t entry = 0;
    uint8_t* entry_buffer = (uint8_t*) &entry;
    // load base
    entry_buffer[2] = base & 0xff;
    entry_buffer[3] = (base >> 8) & 0xff;
    entry_buffer[4] = (base >> 16) & 0xff;
    entry_buffer[7] = (base >> 24) & 0xff;
    // load limit
    entry_buffer[0] = limit & 0xff;
    entry_buffer[1] = (limit >> 8) & 0xff;
    entry_buffer[6] = (limit >> 16) & 0xf; // lower 4 bits of index 6
    // load access and flags
    entry_buffer[5] = access;
    entry_buffer[6] |= (flags << 4); // upper 4 bits of index 6
    return entry;
}

extern void gdt_flush(uint64_t*, uint16_t);
extern void tss_flush(uint16_t);
// aaaaaaand here we go!
int load_gdt(void) {
    GDT[0] = 0; // null descriptor
    if ((GDT[1] = generate_gdt_entry(0, 0xfffff, 0xc, 0x9a)) == GDT_ENTRY_ERROR) {
        return 0;
    }
    if ((GDT[2] = generate_gdt_entry(0, 0xfffff, 0xc, 0x92)) == GDT_ENTRY_ERROR) {
        return 0;
    }
    if ((GDT[3] = generate_gdt_entry(0, 0xfffff, 0xc, 0xfa)) == GDT_ENTRY_ERROR) {
        return 0;
    }
    if ((GDT[4] = generate_gdt_entry(0, 0xfffff, 0xc, 0xf2)) == GDT_ENTRY_ERROR) {
        return 0;
    }
    if ((GDT[5] = generate_gdt_entry((uint32_t)&TSS, sizeof(TSS), 0x4, 0x89)) == GDT_ENTRY_ERROR) { // TSS segment
        return 0;
    }
    gdt_flush(GDT, sizeof(GDT));
    tss_flush(0x28);
    return 1;
}
