// include guard
// #pragma once
// also works
#ifndef A_H
#define A_H

// disable mangling in C++
// mandatory for a C library that is wanted to be used in C++
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief increase internal counter `a`
 */
void increment_a();

/**
 * @brief Get the value of internal counter `a`
 * @return int value of internal counter `a`
 */
int get_a();

#endif // A_H

#ifdef __cplusplus
}
#endif
