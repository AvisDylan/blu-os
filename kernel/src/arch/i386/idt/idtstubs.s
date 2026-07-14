.intel_syntax noprefix

.global isrStubTable
.extern exceptionHandler

.section .text
.align 4

.macro ISR_NO_ERR index
isr_stub_\index:
    push 0
    push \index
    jmp isr_common
.endm

.macro ISR_ERR index
isr_stub_\index:
    push \index
    jmp isr_common
.endm

ISR_NO_ERR 0
ISR_NO_ERR 1
ISR_NO_ERR 2
ISR_NO_ERR 3
ISR_NO_ERR 4
ISR_NO_ERR 5
ISR_NO_ERR 6
ISR_NO_ERR 7
ISR_ERR 8
ISR_NO_ERR 9
ISR_ERR 10
ISR_ERR 11
ISR_ERR 12
ISR_ERR 13
ISR_ERR 14
ISR_NO_ERR 15
ISR_NO_ERR 16
ISR_ERR 17
ISR_NO_ERR 18
ISR_NO_ERR 19
ISR_NO_ERR 20
ISR_NO_ERR 21
ISR_NO_ERR 22
ISR_NO_ERR 23
ISR_NO_ERR 24
ISR_NO_ERR 25
ISR_NO_ERR 26
ISR_NO_ERR 27
ISR_NO_ERR 28
ISR_NO_ERR 29
ISR_ERR 30
ISR_NO_ERR 31

isr_common:
    pusha

    mov eax, [esp + 32]
    push eax

    mov eax, [esp + 36]
    push eax

    call exceptionHandler

    add esp, 8

    popa
    add esp, 8
    iret

.section .data
.align 4
isrStubTable:
    .long isr_stub_0, isr_stub_1, isr_stub_2, isr_stub_3
    .long isr_stub_4, isr_stub_5, isr_stub_6, isr_stub_7
    .long isr_stub_8, isr_stub_9, isr_stub_10, isr_stub_11
    .long isr_stub_12, isr_stub_13, isr_stub_14, isr_stub_15
    .long isr_stub_16, isr_stub_17, isr_stub_18, isr_stub_19
    .long isr_stub_20, isr_stub_21, isr_stub_22, isr_stub_23
    .long isr_stub_24, isr_stub_25, isr_stub_26, isr_stub_27
    .long isr_stub_28, isr_stub_29, isr_stub_30, isr_stub_31