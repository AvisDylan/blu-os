.intel_syntax noprefix

.global setGdt
.type setGdt, @function

.section .text
.align 4
gdtr:
    .word 0
    .long 0

setGdt:
    mov ax, [esp + 4]
    mov [gdtr], ax

    mov eax, [esp + 8]
    mov [gdtr + 2], eax

    lgdt [gdtr]

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ljmp 0x08, offset .reload_cs

.reload_cs:
    ret

.size setGdt, . - setGdt