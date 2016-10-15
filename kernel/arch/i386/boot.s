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

# Commented lines were for testing something stupid. Please ignore.
    #mov     ax, 5
#Loop:
    #push    ax
    call    kernel_main
    #pop     ax
    #dec     ax
    #jnz     Loop
    cli
Hang:  
    hlt
    jmp     Hang

# TODO: Load GDT

# TODO: Implement ISRs

#.global _mcursor
#.type _mcursor, @function
#_mcursor:
#    push    ebp
#    mov     ebp, esp

.global asm_add
.type asm_add, @function
asm_add:
    push    ebp             # save base pointer on stack
    mov     ebp, esp        # set base pointer for function
    mov     eax, 8[ebp]     # move arg1 into eax
    mov     edx, 12[ebp]    # move arg2 into edx
    add     eax, edx        # add edx into eax
    pop     ebp             # restore base pointer from stack
    ret                     # return

.size _start, . - _start
