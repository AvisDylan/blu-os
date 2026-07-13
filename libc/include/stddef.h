//
// Created by dylan on 13/07/2026.
//

#ifndef BLU_OS_STDDEF_H
#define BLU_OS_STDDEF_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file stddef.h
 * @brief Common definitions for C programs
 *
 * Provides fundamental types and macros required by C including NULL, size_t, ptrdiff_t, wchar_t and their limits.
 */

#include <stdint.h>

#ifdef __x86_64__
typedef uint64_t size_t;
#define SIZE_MAX UINT64_MAX
#else
typedef uint32_t size_t;
#define SIZE_MAX UINT32_MAX
#endif

#ifdef __x86_64__
typedef long ptrdiff_t;
#define PTRDIFF_MIN (-9223372036854775807L - 1)
#define PTRDIFF_MAX 9223372036854775807L
#else
typedef int ptrdiff_t;
#define PTRDIFF_MIN (-2147483648)
#define PTRDIFF_MAX 2147483647
#endif

typedef int wchar_t;
#define WCHAR_MIN (-2147483648)
#define WCHAR_MAX 2147483647

#ifndef NULL
#define NULL ((void*) 0)
#endif

#ifdef __cplusplus
}
#endif

#endif //BLU_OS_STDDEF_H
