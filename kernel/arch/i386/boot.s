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
    call    load_gdt
    call    t_init
    call    kernel_main
    cli
Hang:  
    hlt
    jmp     Hang

.size _start, . - _start

# TODO: Load GDT
.global gdt_flush
.type gdt_flush, @function
gdt_flush:
    cli
    mov     eax, 4[esp]
    mov     2[gdt_ptr], eax
    mov     ax, 8[esp]
    mov     [gdt_ptr], ax
    lgdt    [gdt_ptr]
    jmp     0x08:complete_flush
complete_flush:
    mov     ax, 0x10
    mov     ds, ax
    mov     es, ax
    mov     fs, ax
    mov     gs, ax
    mov     ss, ax
    #sti            # for some reason it works if i comment this out
                    # i probably need an IDT or something if i want to reenable interrupts
    ret

# TODO: Implement ISRs

.section .data
gdt_ptr:
    .word 0
    .long 0
