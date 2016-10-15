.intel_syntax noprefix
# multiboot header constants
.set ALIGN,     1<<0
.set MEMINFO,   1<<1
.set FLAGS,     ALIGN | MEMINFO
.set MAGICNUM,  0x1BADB002
.set CHECKSUM,  -(MAGICNUM + FLAGS)

# multiboot headers
.section .multiboot
.align 4
.long MAGICNUM
.long FLAGS
.long CHECKSUM

# stack space
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB stack space
stack_top:

# boot entry point
.section .text
.global _start
.type _start, @function
_start:
    mov     esp, offset stack_top
    call    t_init
    call    kernel_main
    cli
Hang:  
    hlt
    jmp     Hang

# TODO: Load GDT

# TODO: Implement ISRs

.size _start, . - _start
