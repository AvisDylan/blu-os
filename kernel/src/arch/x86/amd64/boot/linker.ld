ENTRY(_start)

SECTIONS
{
    . = 0xFFFFFFFF80100000;

    .text ALIGN(4K) : AT(ADDR(.text) - 0xFFFFFFFF80000000){
        *(.multiboot)
        *(.text*)
    }

    .rodata ALIGN(4K) : AT(ADDR(.rodata) - 0xFFFFFFFF80000000){
        *(.rodata*)
    }

    .data ALIGN(4K) : AT(ADDR(.data) - 0xFFFFFFFF80000000){
        *(.data*)
    }

    .bss ALIGN(4K) : AT(ADDR(.bss) - 0xFFFFFFFF80000000){
        *(COMMON)
        *(.bss*)
    }

    endKernel = .;
}