.intel_syntax noprefix

.section .text

.global remap_irq
.type remap_irq, @function
remap_irq:
        mov     al, 0x11
        out     0x20, al
        mov     al, 0x11
        out     0xa0, al
        mov     al, 0x20
        out     0x21, al
        mov     al, 0x28
        out     0xa1, al
        mov     al, 0x04
        out     0x21, al
        mov     al, 0x02
        out     0xa1, al
        mov     al, 0x01
        out     0x21, al
        mov     al, 0x01
        out     0xa1, al
        mov     al, 0x0
        out     0x21, al
        mov     al, 0x0
        out     0xa1, al
        ret
        
.global IRQ0
.type IRQ0, @function
IRQ0:   
        jmp IRQ_COMMON

.global IRQ1
.type IRQ1, @function
IRQ1:
        jmp IRQ_COMMON

.global IRQ2
.type IRQ2, @function
IRQ2:
        jmp IRQ_COMMON

.global IRQ3
.type IRQ3, @function
IRQ3:
        jmp IRQ_COMMON

.global IRQ4
.type IRQ4, @function
IRQ4:
        jmp IRQ_COMMON

.global IRQ5
.type IRQ5, @function
IRQ5:
        jmp IRQ_COMMON

.global IRQ6
.type IRQ6, @function
IRQ6:
        jmp IRQ_COMMON

.global IRQ7
.type IRQ7, @function
IRQ7:   
        jmp IRQ_COMMON

.global IRQ8
.type IRQ8, @function
IRQ8:
        mov     ax, 0x20
        mov     dx, 0xa0
        out     dx, ax
        jmp IRQ_COMMON

.global IRQ9
.type IRQ9, @function
IRQ9:
        mov     ax, 0x20
        mov     dx, 0xa0
        out     dx, ax
        jmp IRQ_COMMON

.global IRQ10
.type IRQ10, @function
IRQ10:
        mov     ax, 0x20
        mov     dx, 0xa0
        out     dx, ax
        jmp IRQ_COMMON

.global IRQ11
.type IRQ11, @function
IRQ11:
        mov     ax, 0x20
        mov     dx, 0xa0
        out     dx, ax
        jmp IRQ_COMMON

.global IRQ12
.type IRQ12, @function
IRQ12:
        mov     ax, 0x20
        mov     dx, 0xa0
        out     dx, ax
        jmp IRQ_COMMON

.global IRQ13
.type IRQ13, @function
IRQ13:
        mov     ax, 0x20
        mov     dx, 0xa0
        out     dx, ax
        jmp IRQ_COMMON

.global IRQ14
.type IRQ14, @function
IRQ14:
        mov     ax, 0x20
        mov     dx, 0xa0
        out     dx, ax
        jmp IRQ_COMMON

.global IRQ15
.type IRQ15, @function
IRQ15:
        mov     ax, 0x20
        mov     dx, 0xa0
        out     dx, ax
        jmp IRQ_COMMON


# IRQs currently do nothing. This will change very soon.
.global IRQ_COMMON
.type IRQ_COMMON, @function
IRQ_COMMON:                 # THIS WILL CHANGE
        mov     ax, 0x20
        mov     dx, 0x20
        out     dx, ax
        iret
