cmake_minimum_required(VERSION 3.33)
project(blu_os_kernel)

enable_language(ASM)

set(KERNEL_COMMON_SOURCES
        src/drivers/vga.c
        src/kernel/kernel.c
        src/kernel/tty/tty.c
        src/kernel/libk/stdio/kprintf.c
        src/kernel/libk/panic.c
        src/kernel/libk/stdio/kputchar.c
        src/kernel/libk/string/strlen.c
        src/kernel/libk/stdlib/kfree.c
        src/kernel/libk/stdlib/kmalloc.c
        src/kernel/mm/heap.c
        src/kernel/mm/slab.c
)

set(KERNEL_I386_SOURCES
        src/arch/x86/i386/boot/boot.s
        src/arch/x86/i386/gdt/gdt.c
        src/arch/x86/i386/gdt/gdtflush.s
        src/arch/x86/i386/idt/idt.c
        src/arch/x86/i386/idt/idtstubs.s
        src/arch/x86/i386/io/io.c
        src/arch/x86/i386/pic/irqstubs.s
        src/arch/x86/i386/pic/pic.c
        src/arch/x86/i386/mmu/paging.s
        src/arch/x86/i386/mmu/physicalmemorymanager.c
        src/arch/x86/i386/mmu/virtualmemorymanager.c
        src/arch/x86/i386/kal.c
)

set(KERNEL_AMD64_SOURCES
        src/arch/x86/amd64/boot/boot.s
        src/arch/x86/amd64/kal.c
        src/arch/x86/amd64/gdt/gdtflush.s
        src/arch/x86/amd64/gdt/gdt.c
        src/arch/x86/amd64/idt/idtstubs.s
        src/arch/x86/amd64/idt/idt.c
)

if (ARCH_BITS EQUAL 64)
    add_compile_options(-mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2)

    add_library(crti_amd64 OBJECT src/arch/x86/amd64/boot/crti.s)
    add_library(crtn_amd64 OBJECT src/arch/x86/amd64/boot/crtn.s)
    set_target_properties(crti_amd64 PROPERTIES LANGUAGE ASM)
    set_target_properties(crtn_amd64 PROPERTIES LANGUAGE ASM)

    add_executable(blu_os.kernel64 ${KERNEL_COMMON_SOURCES} ${KERNEL_AMD64_SOURCES})
    add_dependencies(blu_os.kernel64 crti_amd64 crtn_amd64)

    target_include_directories(blu_os.kernel64 PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

    target_link_options(blu_os.kernel64 PRIVATE
            -Wl,-T${CMAKE_CURRENT_SOURCE_DIR}/src/arch/x86/amd64/boot/linker.ld
            $<TARGET_OBJECTS:crti_amd64>
            $<TARGET_OBJECTS:crtn_amd64>
    )

    target_link_libraries(blu_os.kernel64 PRIVATE gcc)
else ()
    add_library(crti_i386 OBJECT src/arch/x86/i386/boot/crti.s)
    add_library(crtn_i386 OBJECT src/arch/x86/i386/boot/crtn.s)
    set_target_properties(crti_i386 PROPERTIES LANGUAGE ASM)
    set_target_properties(crtn_i386 PROPERTIES LANGUAGE ASM)

    add_executable(blu_os.kernel32 ${KERNEL_COMMON_SOURCES} ${KERNEL_I386_SOURCES})
    add_dependencies(blu_os.kernel32 crti_i386 crtn_i386)

    target_include_directories(blu_os.kernel32 PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

    target_link_options(blu_os.kernel32 PRIVATE
            -Wl,-T${CMAKE_CURRENT_SOURCE_DIR}/src/arch/x86/i386/boot/linker.ld
            $<TARGET_OBJECTS:crti_i386>
            $<TARGET_OBJECTS:crtn_i386>
    )

    target_link_libraries(blu_os.kernel32 PRIVATE gcc)
endif ()