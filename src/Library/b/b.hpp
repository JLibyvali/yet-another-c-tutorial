#ifndef B_HPP
#define B_HPP

namespace b{
/**
 * @brief Add `num` to internal counter `b`
 * 
 * @param num number to add
 */
void add(int num);

/**
 * @brief Add `num` to internal counter `b`
 * 
 * @param num number to add
 */
void add(float num);

/**
 * @brief Add `num` to internal counter `b`
 * 
 * @param num number to add
 */
void add(double num);

/**
 * @brief Add 1 if `num` is true, 0 otherwise
 * 
 * @param num true is 1, false is 0
 */
void add(bool num);

/**
 * @brief Get the value of internal counter `b`
 * 
 * @return double value of internal counter `b`
 */
double get();
}

// conditional compilation
// define could supplied by compiler or by standalone header file
#ifdef BB_ENABLE
// implementation directly in the header file
// https://en.wikipedia.org/wiki/One_Definition_Rule
// sometimes it's mandatory to do so, especially when using templates
#include <vector>
#include <functional>

namespace bb {
template <typename T>
std::vector<T> map(const std::vector<T>& vector, std::function<T(T&)> transform){
    std::vector<T> result;
    for(auto& element : vector){
        result.push_back(transform(element));
    }
    return result;
}
}
#endif

#endif // B_HPP
