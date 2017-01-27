.intel_syntax noprefix

.section .text
.global load_page_directory
.type load_page_directory, @function
load_page_directory:
    push    ebp
    mov     ebp, esp
    mov     eax, 8[esp]
    mov     cr3, eax
    mov     esp, ebp
    pop     ebp
    ret


.section .text
.global enable_paging
.type enable_paging, @function
enable_paging:
    push    ebp
    mov     ebp, esp
    mov     eax, cr0
    or      eax, 0x80000000
    mov     cr0, eax
    mov     esp, ebp
    pop     ebp
    ret
