cmake_minimum_required(VERSION 3.33)

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
)

add_library(libk STATIC ${FREESTANDING_SOURCES})
target_include_directories(libk PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/kernel/include
)
target_compile_definitions(libk PRIVATE __is_libk __is_libc)
set_target_properties(libk PROPERTIES OUTPUT_NAME k PREFIX lib)

add_library(libc STATIC ${FREESTANDING_SOURCES})
target_include_directories(libc PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/kernel/include
)
target_compile_definitions(libc PRIVATE __is_libc)
set_target_properties(libc PROPERTIES OUTPUT_NAME c PREFIX lib)