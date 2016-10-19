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

#endif
