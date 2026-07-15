//
// Created by dylan on 15/07/2026.
//

#ifndef BLU_OS_MATH_H
#define BLU_OS_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file math.h
 * @brief Math functions and constants
 */

//TODO finish math.h
#if FLT_EVAL_METHOD == 0
typedef float float_t;
typedef double double_t;
#elif FLT_EVAL_METHOD == 1
typedef double float_t;
typedef double double_t;
#elif FLT_EVAL_METHOD == 2
typedef long double float_t;
typedef long double double_t;
#else
typedef long double float_t;
typedef long double double_t;
#endif

#ifdef __cplusplus
}
#endif

#endif //BLU_OS_MATH_H
