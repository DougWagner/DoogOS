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
        push    0x00
        push    0x00
        jmp     IRQ_COMMON

.global IRQ1
.type IRQ1, @function
IRQ1:
        push    0x00
        push    0x01
        jmp     IRQ_COMMON

.global IRQ2
.type IRQ2, @function
IRQ2:
        push    0x00
        push    0x02
        jmp     IRQ_COMMON

.global IRQ3
.type IRQ3, @function
IRQ3:
        push    0x00
        push    0x03
        jmp     IRQ_COMMON

.global IRQ4
.type IRQ4, @function
IRQ4:
        push    0x00
        push    0x04
        jmp     IRQ_COMMON

.global IRQ5
.type IRQ5, @function
IRQ5:
        push    0x00
        push    0x05
        jmp     IRQ_COMMON

.global IRQ6
.type IRQ6, @function
IRQ6:
        push    0x00
        push    0x06
        jmp     IRQ_COMMON

.global IRQ7
.type IRQ7, @function
IRQ7:
        push    0x00
        push    0x07
        jmp     IRQ_COMMON

.global IRQ8
.type IRQ8, @function
IRQ8:
        push    0x00
        push    0x08
        mov     ax, 0x20
        mov     dx, 0xa0
        out     dx, ax
        jmp     IRQ_COMMON

.global IRQ9
.type IRQ9, @function
IRQ9:
        push    0x00
        push    0x09
        mov     ax, 0x20
        mov     dx, 0xa0
        out     dx, ax
        jmp     IRQ_COMMON

.global IRQ10
.type IRQ10, @function
IRQ10:
        push    0x00
        push    0x0a
        mov     ax, 0x20
        mov     dx, 0xa0
        out     dx, ax
        jmp     IRQ_COMMON

.global IRQ11
.type IRQ11, @function
IRQ11:
        push    0x00
        push    0x0b
        mov     ax, 0x20
        mov     dx, 0xa0
        out     dx, ax
        jmp     IRQ_COMMON

.global IRQ12
.type IRQ12, @function
IRQ12:
        push    0x00
        push    0x0c
        mov     ax, 0x20
        mov     dx, 0xa0
        out     dx, ax
        jmp     IRQ_COMMON

.global IRQ13
.type IRQ13, @function
IRQ13:
        push    0x00
        push    0x0d
        mov     ax, 0x20
        mov     dx, 0xa0
        out     dx, ax
        jmp     IRQ_COMMON

.global IRQ14
.type IRQ14, @function
IRQ14:
        push    0x00
        push    0x0e
        mov     ax, 0x20
        mov     dx, 0xa0
        out     dx, ax
        jmp     IRQ_COMMON

.global IRQ15
.type IRQ15, @function
IRQ15:
        push    0x00
        push    0x0f
        mov     ax, 0x20
        mov     dx, 0xa0
        out     dx, ax
        jmp     IRQ_COMMON


# IRQs currently do nothing. This will change very soon.
.global IRQ_COMMON
.type IRQ_COMMON, @function
IRQ_COMMON:
        pushad
        push    ds
        push    es
        push    fs
        push    gs
        mov     ax, 0x10
        mov     ds, ax
        mov     es, ax
        mov     fs, ax
        mov     gs, ax
        push    esp
        call    irq_handler
        mov     ax, 0x20
        mov     dx, 0x20
        out     dx, ax
        pop     eax
        pop     gs
        pop     fs
        pop     es
        pop     ds
        popad
        add     esp, 8
        iret

.global get_scancode
.type get_scancode, @function
get_scancode:
        in     al, 0x60
        ret
