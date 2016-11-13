#ifndef ARCH_I386_INTERRUPTS_H
#define ARCH_I386_INTERRUPTS_H

struct stack_frame {
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eas;
    unsigned int int_num, error_code;
    unsigned int eip, cs, eflags, uesp, ss;
};

void load_idt(void);
void install_isrs(void);
void install_irqs(void);
void install_interrupts(void);
void install_idt_entry(size_t, uint32_t, uint16_t, uint8_t);
//void interrupt_handler(struct stack_frame*);

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

#endif
