#ifndef ARCH_I386_GDT_H
#define ARCH_I386_GDT_H

// if shit goes bad, return this number
#define GDT_ENTRY_ERROR 0xFFFFFFFFFFFFFFFF

// Define flag types - if flags variable is not equal to any of these, throw error
// bits 0 and 1 should always be 0, bit 2 is Granularity, bit 3 is Size
// Define naming convention - FLAGS_GRAN_SIZE
// GRAN types - BYTE | PAGE
// SIZE types - 16 | 32
#define FLAGS_BYTE_16 0x0
#define FLAGS_BYTE_32 0x4
#define FLAGS_PAGE_16 0x8
#define FLAGS_PAGE_32 0xc

// Define access types - if access is not equal to any of these, throw error
// bit 0 should always be 0, bit 4 and 7 should always be 1
// bit 1 is Read/Write, bit 2 is Direction, bit 3 is Executability, bits 5 and 6 are Privledge level
// Define naming convention - ACC_PRIV_EXE_DIR_RW
// PRIV types - HIGH | LOW || 0 | 3 - other priv types unused
// EXE types - DAT | EXE || 0 | 1
// DIR types - UP | DN || 0 | 1
// RW types - RO | RW || 0 | 1 - if EXE type is DAT
// RW types - XO | RX || 0 | 1 - if EXE type is EXE
#define ACC_HIGH_DAT_UP_RO 0x90
#define ACC_HIGH_DAT_UP_RW 0x92
#define ACC_HIGH_DAT_DN_RO 0x94
#define ACC_HIGH_DAT_DN_RW 0x96
#define ACC_HIGH_EXE_UP_XO 0x98
#define ACC_HIGH_EXE_UP_RX 0x9a
#define ACC_HIGH_EXE_DN_XO 0x9c
#define ACC_HIGH_EXE_DN_RX 0x9e
#define ACC_LOW_DAT_UP_RO 0xf0
#define ACC_LOW_DAT_UP_RW 0xf2
#define ACC_LOW_DAT_DN_RO 0xf4
#define ACC_LOW_DAT_DN_RW 0xf6
#define ACC_LOW_EXE_UP_XO 0xf8
#define ACC_LOW_EXE_UP_RX 0xfa
#define ACC_LOW_EXE_DN_XO 0xfc
#define ACC_LOW_EXE_DN_RX 0xfe

int load_gdt(void);

struct tss_data {
    uint16_t link;          // 0x00
    uint16_t reserved0;     // 0x02
    uint32_t esp0;          // 0x04
    uint16_t ss0;           // 0x08
    uint16_t reserved1;     // 0x0a
    uint32_t esp1;          // 0x0c
    uint16_t ss1;           // 0x10
    uint16_t reserved2;     // 0x12
    uint32_t esp2;          // 0x14
    uint16_t ss2;           // 0x18
    uint16_t reserved3;     // 0x1a
    uint32_t cr3;           // 0x1c
    uint32_t eip;           // 0x20
    uint32_t eflags;        // 0x24
    uint32_t eax;           // 0x28
    uint32_t ecx;           // 0x2c
    uint32_t edx;           // 0x30
    uint32_t ebx;           // 0x34
    uint32_t esp;           // 0x38
    uint32_t ebp;           // 0x3c
    uint32_t esi;           // 0x40
    uint32_t edi;           // 0x44
    uint16_t es;            // 0x48
    uint16_t reserved4;     // 0x4a
    uint16_t cs;            // 0x4c
    uint16_t reserved5;     // 0x4e
    uint16_t ss;            // 0x50
    uint16_t reserved6;     // 0x52
    uint16_t ds;            // 0x54
    uint16_t reserved7;     // 0x56
    uint16_t fs;            // 0x58
    uint16_t reserved8;     // 0x5a
    uint16_t gs;            // 0x5c
    uint16_t reserved9;     // 0x5e
    uint16_t ldtr;          // 0x60
    uint16_t reserved10;    // 0x62
    uint16_t reserved11;    // 0x64
    uint16_t iobmap;        // 0x66
};

#endif
