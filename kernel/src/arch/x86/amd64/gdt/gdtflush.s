.intel_syntax noprefix

.global setGdt
.type setGdt, @function

.section .bss
.align 8
gdtr:
    .word 0
    .long 0

.section .text
.align 4

setGdt:
    mov [gdtr], di
    mov [gdtr + 2], rsi

    lgdt [gdtr]

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    push 0x08
    lea rax, [rip + .reload_cs]
    push rax
    lretq


.reload_cs:
    ret

.size setGdt, . - setGdt