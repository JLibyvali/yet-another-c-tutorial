#ifndef B_INTERFACE_H
#define B_INTERFACE_H

/**
 * @brief  It serves as a C interface to the C++ library b.
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Add `num` to internal counter `b`
 * 
 * @param num number to add
 */
void add_b_int(int num);

/**
 * @brief Add `num` to internal counter `b`
 * 
 * @param num 
 */
void add_b_float(float num);

/**
 * @brief Add `num` to internal counter `b`
 * 
 * @param num 
 */
void add_b_double(double num);

/**
 * @brief Get the value of internal counter `b`
 * @return value of internal counter `b`
 */
double get_b();

#ifdef __cplusplus
}
#endif

#endif // B_INTERFACE_H
