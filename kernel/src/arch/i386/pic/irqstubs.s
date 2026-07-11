.intel_syntax noprefix

.global irqStubTable
.extern irqHandler

.macro IRQ_STUB index
irq_stub_\index:
    push 0
    push \index
    jmp irq_common
.endm

IRQ_STUB 32
IRQ_STUB 33
IRQ_STUB 34
IRQ_STUB 35
IRQ_STUB 36
IRQ_STUB 37
IRQ_STUB 38
IRQ_STUB 39
IRQ_STUB 40
IRQ_STUB 41
IRQ_STUB 42
IRQ_STUB 43
IRQ_STUB 44
IRQ_STUB 45
IRQ_STUB 46
IRQ_STUB 47

irq_common:
    pusha
    call irqHandler
    popa
    add esp, 8
    iret

.section .data
irqStubTable:
    .long irq_stub_32, irq_stub_33, irq_stub_34, irq_stub_35
    .long irq_stub_36, irq_stub_37, irq_stub_38, irq_stub_39
    .long irq_stub_40, irq_stub_41, irq_stub_42, irq_stub_43
    .long irq_stub_44, irq_stub_45, irq_stub_46, irq_stub_47