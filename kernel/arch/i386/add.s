.intel_syntax noprefix
.section .text
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

