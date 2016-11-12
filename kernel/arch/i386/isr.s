.intel_syntax noprefix

.section .text

.global ISR0
.type ISR0, @function
ISR0:                   # Divide-by-zero exception
        push    0x00
        push    0x00
        jmp     ISR_COMMON

.global ISR1
.type ISR1, @function
ISR1:                   # Debug exception
        push    0x00
        push    0x01
        jmp     ISR_COMMON

.global ISR2
.type ISR2, @function
ISR2:                   # Non-maskable Interrupt exception
        push    0x00
        push    0x02
        jmp     ISR_COMMON

.global ISR3
.type ISR3, @function
ISR3:                   # Breakpoint exception
        push    0x00
        push    0x03
        jmp     ISR_COMMON

.global ISR4
.type ISR4, @function
ISR4:                   # Overflow exception
        push    0x00
        push    0x04
        jmp     ISR_COMMON

.global ISR5
.type ISR5, @function
ISR5:                   # Bound Range Exceeded exception
        push    0x00
        push    0x05
        jmp     ISR_COMMON

.global ISR6
.type ISR6, @function
ISR6:                   # Invalid Opcode exception
        push    0x00
        push    0x06
        jmp     ISR_COMMON

.global ISR7
.type ISR7, @function
ISR7:                   # Device Not Available exception
        push    0x00
        push    0x07
        jmp     ISR_COMMON

.global ISR8
.type ISR8, @function
ISR8:                   # Double Fault exception (With Error Code)
        push    0x08
        jmp     ISR_COMMON

.global ISR9
.type ISR9, @function
ISR9:                   # Coprocessor Segment Overrun exception - should not be used anymore
        push    0x00
        push    0x09
        jmp     ISR_COMMON

.global ISR10
.type ISR10, @function
ISR10:                  # Invalid TSS exception (With Error Code)
        push    0x0a
        jmp     ISR_COMMON

.global ISR11
.type ISR11, @function
ISR11:                  # Segment Not Present exception (With Error Code)
        push    0x0b
        jmp     ISR_COMMON

.global ISR12
.type ISR12, @function
ISR12:                  # Stack-Segment Fault exception (With Error Code)
        push    0x0c
        jmp     ISR_COMMON

.global ISR13
.type ISR13, @function
ISR13:                  # General Protection Fault exception (With Error Code
        push    0x0d
        jmp     ISR_COMMON

.global ISR14
.type ISR14, @function
ISR14:                  # Page Fault exception (With Error Code)
        push    0x0e
        jmp     ISR_COMMON

.global ISR15
.type ISR15, @function
ISR15:                  # Reserved
        push    0x00
        push    0x0f
        jmp     ISR_COMMON

.global ISR16
.type ISR16, @function
ISR16:                  # x87 Floating-Point exception
        push    0x00
        push    0x10
        jmp     ISR_COMMON

.global ISR17
.type ISR17, @function
ISR17:                  # Alignment Check exception (With Error Code)
        push    0x11
        jmp     ISR_COMMON

.global ISR18
.type ISR18, @function
ISR18:                  # Machine Check Exception
        push    0x00
        push    0x12
        jmp     ISR_COMMON

.global ISR19
.type ISR19, @function
ISR19:                  # SIMD Floating-Point Exception
        push    0x00
        push    0x13
        jmp     ISR_COMMON

.global ISR20
.type ISR20, @function
ISR20:                  # Reserved
        push    0x00
        push    0x14
        jmp     ISR_COMMON

.global ISR21
.type ISR21, @function
ISR21:                  # Reserved
        push    0x00
        push    0x15
        jmp     ISR_COMMON

.global ISR22
.type ISR22, @function
ISR22:                  # Reserved
        push    0x00
        push    0x16
        jmp     ISR_COMMON

.global ISR23
.type ISR23, @function
ISR23:                  # Reserved
        push    0x00
        push    0x17
        jmp     ISR_COMMON

.global ISR24
.type ISR24, @function
ISR24:                  # Reserved
        push    0x00
        push    0x18
        jmp     ISR_COMMON

.global ISR25
.type ISR25, @function
ISR25:                  # Reserved
        push    0x00
        push    0x19
        jmp     ISR_COMMON

.global ISR26
.type ISR26, @function
ISR26:                  # Reserved
        push    0x00
        push    0x1a
        jmp     ISR_COMMON

.global ISR27
.type ISR27, @function
ISR27:                  # Reserved
        push    0x00
        push    0x1b
        jmp     ISR_COMMON

.global ISR28
.type ISR28, @function
ISR28:                  # Reserved
        push    0x00
        push    0x1c
        jmp     ISR_COMMON

.global ISR29
.type ISR29, @function
ISR29:                  # Reserved
        push    0x00
        push    0x1d
        jmp     ISR_COMMON

.global ISR30
.type ISR30, @function
ISR30:                  # Security Exception (With Error Code)
        push    0x00
        push    0x1e
        jmp     ISR_COMMON

.global ISR31
.type ISR31, @function
ISR31:                  # Reserved
        push    0x00
        push    0x1f
        jmp     ISR_COMMON

.global ISR_COMMON
.type ISR_COMMON, @function
ISR_COMMON:
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
        call    interrupt_handler
        pop     eax
        pop     gs
        pop     fs
        pop     es
        pop     ds
        popad
        add     esp, 8
        iret
