.intel_syntax noprefix

.global threadSwitch

threadSwitch:
    push ebp
    mov ebp, esp

    push ebx
    push esi
    push edi

    mov eax, [ebp + 8]

    mov [eax + 12], esp

    mov eax, [ebp + 12]

    mov esp, [eax + 12]

    pop edi
    pop esi
    pop ebx

    pop ebp

    ret