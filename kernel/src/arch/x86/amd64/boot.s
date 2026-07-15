.intel_syntax noprefix

.set ALIGN, 1<<0
.set MEMINFO, 1<<1
.set FLAGS, ALIGN | MEMINFO
.set MAGIC, 0x1badb002
.set CHECKSUM, -(MAGIC + FLAGS)
.set KERNEL_VMA, 0xFFFFFFFF80000000

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 4096
p4_table:
    .skip 4096
p3_table:
    .skip 4096
p2_table:
    .skip 4096
stack_bottom:
    .skip 16384
stack_top:

.section .rodata
gdt64:
    .quad 0x0000000000000000
    .quad 0x00209A0000000000
    .quad 0x0000920000000000
gdt64_pointer:
    .word . - gdt64 - 1
    .quad gdt64

.section .text
.code32
.global _start
.type _start, @function

_start:
    lea esp, [stack_top - KERNEL_VMA]

    # TODO add CPUID and Long mode check

    lea edi, [p4_table - KERNEL_VMA]
    lea eax, [p3_table - KERNEL_VMA]
    or eax, 0x3

    mov [edi], eax
    mov [edi + 511 * 8], eax

    lea edi, [p3_table - KERNEL_VMA]
    lea eax, [p2_table - KERNEL_VMA]
    or eax, 0x3
    mov [edi + 510 * 8], eax
    mov [edi], eax

    lea edi, [p2_table - KERNEL_VMA]
    mov eax, 0x83
    mov [edi], eax

    lea eax, [p4_table - KERNEL_VMA]
    mov cr3, eax

    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    mov eax, offset gdt64_pointer - KERNEL_VMA
    lgdt [eax]

    push 0x08
    lea eax, [realm64 - KERNEL_VMA]
    push eax
    retf

.size _start, . - _start

.code64
realm64:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov rsp, offset stack_top

    mov rax, offset higher_half
    jmp rax

higher_half:
    mov rax, 0
    mov qword ptr [p4_table], rax

    mov rax, cr3
    mov cr3, rax

    call _init
    call kernelMain

1:  cli
    hlt
    jmp 1b

.size realm64, . - realm64