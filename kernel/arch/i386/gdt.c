#include <stdint.h>
#include <kernel/tty.h>
#include "gdt.h"

uint64_t GDT[3];

static int checkFlagBits(uint8_t flags) {
    // this is probably a really stupid way to do this
    switch(flags) {
    case FLAGS_BYTE_16:
    case FLAGS_BYTE_32:
    case FLAGS_PAGE_16:
    case FLAGS_PAGE_32:
        return 1;
    default:
        return 0;
    }
}

static int checkAccessBits(uint8_t access) {
    // this is also probably a really stupid way to do this
    switch(access) {
    case ACC_HIGH_DAT_UP_RO:
    case ACC_HIGH_DAT_UP_RW:
    case ACC_HIGH_DAT_DN_RO:
    case ACC_HIGH_DAT_DN_RW:
    case ACC_HIGH_EXE_UP_XO:
    case ACC_HIGH_EXE_UP_RX:
    case ACC_HIGH_EXE_DN_XO:
    case ACC_HIGH_EXE_DN_RX:
    case ACC_LOW_DAT_UP_RO:
    case ACC_LOW_DAT_UP_RW:
    case ACC_LOW_DAT_DN_RO:
    case ACC_LOW_DAT_DN_RW:
    case ACC_LOW_EXE_UP_XO:
    case ACC_LOW_EXE_UP_RX:
    case ACC_LOW_EXE_DN_XO:
    case ACC_LOW_EXE_DN_RX:
        return 1;
    default:
        return 0;
    }
}

static uint64_t generate_gdt_entry(uint32_t base, uint32_t limit, uint8_t flags, uint8_t access) {
    // check flags to ensure validity
    if (!checkFlagBits(flags)) {
        t_writestr("Invalid flag bits\n");
        return GDT_ENTRY_ERROR;
    }
    // check access to ensure validity
    if (!checkAccessBits(access)) {
        t_writestr("Invalid access bits\n");
        return GDT_ENTRY_ERROR;
    }
    if (limit > 0xfffff) {
        t_writestr("limit too large\n");
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
// aaaaaaand here we go!
int load_gdt(void) {
    GDT[0] = 0; // null descriptor
    if ((GDT[1] = generate_gdt_entry(0, 0xfffff, 0xc, 0x9a)) == GDT_ENTRY_ERROR) {
        return 0;
    }
    if ((GDT[2] = generate_gdt_entry(0, 0xfffff, 0xc, 0x92)) == GDT_ENTRY_ERROR) {
        return 0;
    }
    //GDT[3] = 0;
    gdt_flush(GDT, sizeof(GDT));
    return 1;
}
