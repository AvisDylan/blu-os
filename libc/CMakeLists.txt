cmake_minimum_required(VERSION 3.33)
project(blu_os_libc)

set(FREESTANDING_SOURCES
        src/stdlib/abort.c
        src/string/memmove.c
        src/string/strlen.c
        src/string/memcmp.c
        src/string/memset.c
        src/string/memcpy.c
        src/stdio/printf.c
        src/stdio/putchar.c
        src/stdio/puts.c
        src/stdio/vprintf.c
)

add_library(libc STATIC ${FREESTANDING_SOURCES})
target_include_directories(libc PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_compile_definitions(libc PRIVATE __is_libc)
set_target_properties(libc PROPERTIES OUTPUT_NAME c PREFIX lib)