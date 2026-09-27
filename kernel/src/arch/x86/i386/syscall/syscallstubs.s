.intel_syntax noprefix

.global syscallHandler

syscallHandler:
    pushad
    push esp

    call syscallDispatch

    add esp, 4
    popad
    iret
