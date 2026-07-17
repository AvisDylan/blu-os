.intel_syntax noprefix

.set ALIGN, 1<<0
.set MEMINFO, 1<<1
.set FLAGS, ALIGN | MEMINFO
.set MAGIC, 0x1badb002
.set CHECKSUM, -(MAGIC + FLAGS)

.set KERNEL_VIRTUAL_BASE, 0xFFFFFFFF80000000

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .data
.align 8
gdt64:
    .quad 0x0000000000000000
.code_desc:
    .quad 0x00209a0000000000
.data_desc:
    .quad 0x0000920000000000
gdt64_ptr:
    .word . - gdt64 - 1
    .quad gdt64 - KERNEL_VIRTUAL_BASE

.section .bss
.align 4096
p4_table:
    .skip 4096
p3_table_low:
    .skip 4096
p3_table_high:
    .skip 4096
p2_table_low:
    .skip 4096
p2_table_high:
    .skip 4096

.align 16
stack_bottom:
    .skip 16384
stack_top:

.section .text
.global _start
.type _start, @function
.code32
_start:
    lea edi, [p4_table - KERNEL_VIRTUAL_BASE]
    xor eax, eax
    mov ecx, 5120
    rep stosd

    lea edi, [p4_table - KERNEL_VIRTUAL_BASE]
    lea eax, [p3_table_low - KERNEL_VIRTUAL_BASE]
    or eax, 3
    mov [edi], eax

    lea eax, [p3_table_high - KERNEL_VIRTUAL_BASE]
    or eax, 3
    mov [edi + 511 * 8], eax

    lea edi, [p3_table_low - KERNEL_VIRTUAL_BASE]
    lea eax, [p2_table_low - KERNEL_VIRTUAL_BASE]
    or eax, 3
    mov [edi], eax

    lea edi, [p3_table_high - KERNEL_VIRTUAL_BASE]
    lea eax, [p2_table_high - KERNEL_VIRTUAL_BASE]
    or eax, 3
    mov [edi + 510 * 8], eax

    lea edi, [p2_table_low - KERNEL_VIRTUAL_BASE]
    mov eax, 0x83
    mov ecx, 512
.loop_low_pdt:
    mov [edi], eax
    mov dword ptr [edi + 4], 0
    add edi, 8
    add eax, 0x200000
    loop .loop_low_pdt

    lea edi, [p2_table_high - KERNEL_VIRTUAL_BASE]
    mov eax, 0x83
    mov ecx, 512
.loop_high_pdt:
    mov [edi], eax
    mov dword ptr [edi + 4], 0
    add edi, 8
    add eax, 0x200000
    loop .loop_high_pdt

    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    lea eax, [p4_table - KERNEL_VIRTUAL_BASE]
    mov cr3, eax

    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    lgdt [gdt64_ptr - KERNEL_VIRTUAL_BASE]

    push 0x08
    lea eax, [.entry64 - KERNEL_VIRTUAL_BASE]
    push eax
    retf

.code64
.entry64:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov rax, offset .higher_half
    jmp rax

.higher_half:
    mov rax, 0
    mov [p4_table], rax

    mov rax, cr3
    mov cr3, rax

    mov rsp, offset stack_top

    call _init
    call kernelMain

1:  cli
    hlt
    jmp 1b

.size _start, . - _start