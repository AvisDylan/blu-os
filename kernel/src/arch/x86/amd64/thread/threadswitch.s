.intel_syntax noprefix

.global threadSwitch

threadSwitch:
    push rbp
    push rbx
    push r12
    push r13
    push r14
    push r15

    mov [rdi + 24], rsp

    mov rsp, [rdi + 24]

    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx
    pop rbp

    ret