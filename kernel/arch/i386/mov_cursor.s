.intel_syntax noprefix
.text
.global mov_cursor
.type mov_cursor, @function
mov_cursor:
    push    ebp             # save base pointer
    mov     ebp, esp        # load function stack to base pointer

    mov     cx, 8[ebp]
    mov     al, 0x0F
    mov     dx, 0x3D4
    out     dx, al          # VGA port 0x3D4
    
    mov     ax, cx
    mov     dx, 0x3D5
    out     dx, al          # send lower part to VGA register

    mov     cx, ax
    mov     al, 0x0E
    mov     dx, 0x3D4
    out     dx, al          # VGA port 0x3D4

    mov     ax, cx
    shr     ax, 8
    mov     dx, 0x3D5
    out     dx, al          # send upper part to VGA register

    pop     ebp             # restore base pointer from stack
    ret

