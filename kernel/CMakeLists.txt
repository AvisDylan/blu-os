cmake_minimum_required(VERSION 3.33)

add_library(crti OBJECT src/arch/i386/crti.s)
add_library(crtn OBJECT src/arch/i386/crtn.s)

execute_process(
    COMMAND ${CMAKE_C_COMPILER} -m32 -print-file-name=crtbegin.o
    OUTPUT_VARIABLE CRTBEGIN_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
    COMMAND ${CMAKE_C_COMPILER} -m32 -print-file-name=crtend.o
    OUTPUT_VARIABLE CRTEND_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(KERNEL_SOURCES
    src/arch/i386/boot.s
    src/drivers/vga.c
    src/kernel/kernel.c
    src/kernel/tty/tty.c
)

add_executable(blu_os.kernel ${KERNEL_SOURCES})
add_dependencies(blu_os.kernel crti crtn)

target_include_directories(blu_os.kernel PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/libc/include
)

target_link_options(blu_os.kernel PRIVATE
    -m32
    -T ${CMAKE_CURRENT_SOURCE_DIR}/src/arch/i386/linker.ld
    -ffreestanding
    -nostdlib
    $<TARGET_OBJECTS:crti>
    ${CRTBEGIN_PATH}
    ${CRTEND_PATH}
    $<TARGET_OBJECTS:crtn>
)

target_link_libraries(blu_os.kernel PRIVATE libk gcc)