.intel_syntax noprefix
.section .text
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
    #sti            # this instruction is officially the offender! there is nothing wrong with the GDT! (at least I hope there isn't)
                    # if I enable interrupts without even loading GDT, behavior will be the same
                    # so much debugging for nothing.... looks like I need an IDT...
    ret

.section .data
gdt_ptr:
    .word 0
    .long 0
