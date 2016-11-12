#ifndef ARCH_I386_INTERRUPTS_H
#define ARCH_I386_INTERRUPTS_H

struct stack_frame {
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eas;
    unsigned int int_num, error_code;
    unsigned int eip, cs, eflags, uesp, ss;
};

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


void load_idt(void);
void interrupt_handler(struct stack_frame*);

// Define interrupt types - if interrupt type is none of these, throw error
#define TASK_GATE_32 0x5
#define INT_GATE_16 0x6
#define TRAP_GATE_16 0x7
#define INT_GATE_32 0xe
#define TRAP_GATE_32 0xf

// Define interrupt attributes - if interrupt attributes don't match these, throw error
// bit 0 is for storage segment
// bits 1-2 are for descriptor privlege - 0 for high privelege, 3 for low privelege
// bit 3 is for present - will always be 1. unused interrupts are ignored
// INTGATE means interrupt gate - bit 0 will be 0
// REGGATE means non interrupt gate - bit 0 will be 1
#define INTGATE_HIGH 0x8
#define INTGATE_LOW 0xe
#define REGGATE_HIGH 0x9
#define REGGATE_LOW 0xf

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

#endif
