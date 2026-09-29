.intel_syntax noprefix

.global threadRestoreContext

threadRestoreContext:
    popad
    iret
