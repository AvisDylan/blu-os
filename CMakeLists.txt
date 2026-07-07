cmake_minimum_required(VERSION 3.33)
project(blu_os LANGUAGES C CXX ASM)

set(CMAKE_CXX_STANDARD_REQUIRED 23)
set(CMAKE_C_STANDARD_REQUIRED 23)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_ASM_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(
    -m32
    -ffreestanding
    -Wall
    -Wextra
    -fno-exceptions
)

add_library(crti OBJECT src/kernel/crti.s)
add_library(crtn OBJECT src/kernel/crtn.s)

add_executable(
    blu_os
    src/arch/i386/boot.s
    src/drivers/vga.c
    src/kernel/kernel.c
)

add_dependencies(blu_os crti crtn)

target_include_directories(blu_os PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

execute_process(COMMAND ${CMAKE_C_COMPILER} -m32 -print-file-name=crtbegin.o OUTPUT_VARIABLE CRTBEGIN_PATH OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${CMAKE_C_COMPILER} -m32 -print-file-name=crtend.o OUTPUT_VARIABLE CRTEND_PATH OUTPUT_STRIP_TRAILING_WHITESPACE)

target_link_options(blu_os PRIVATE
    -m32
    -T ${CMAKE_SOURCE_DIR}/src/arch/i386/linker.ld
    -ffreestanding
    -nostdlib
    $<TARGET_OBJECTS:crti>
    ${CRTBEGIN_PATH}
    ${CRTEND_PATH}
    $<TARGET_OBJECTS:crtn>
    -lgcc
)
