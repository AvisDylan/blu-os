//
// Created by dylan on 15/07/2026.
//

#ifndef BLU_OS_MATH_H
#define BLU_OS_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file float.h
 * @brief Floating point constants
 */

#define FLT_RADIX 2
#define FLT_MANT_DIG 24
#define DBL_MANT_DIG 53

//TODO finish float.h
#if defined(__LDBL_MANT_DIG__)
    #define LDBL_MANT_DIG __LDBL_MANT_DIG__
#else
    #if defined(__aarch64__) || defined(__arm64__)
        #define LDBL_MANT_DIG 53
    #elif defined(__x86_64__) || defined(_M_X64)
        #define LDBL_MANT_DIG 64
    #else
        #define LDBL_MANT_DIG 53
    #endif
#endif

#if LDBL_MANT_DIG >= 64
    #define DECIMAL_DIG 21
#elif LDBL_MANT_DIG >= 53
    #define DECIMAL_DIG 17
#elif LDBL_MANT_DIG >= 24
    #define DECIMAL_DIG 9
#else
    #define DECIMAL_DIG 21
#endif

#ifdef __cplusplus
}
#endif

#endif //BLU_OS_MATH_H
