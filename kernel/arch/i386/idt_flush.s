.intel_syntax noprefix
.section .text
.global idt_flush
.type idt_flush, @function
idt_flush:
    mov     eax, 4[esp]
    mov     2[idt_ptr], eax
    mov     ax, 8[esp]
    mov     [idt_ptr], ax
    lidt    [idt_ptr]
    ret

.section .data
idt_ptr:
    .word 0
    .long 0
