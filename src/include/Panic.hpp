#ifndef PANIC_HPP_
#define PANIC_HPP_


#include <cstdlib>
#include <iostream>
#include "include/ostream_utils.hpp"

namespace janncy {

void output_variadic_(std::ostream &out);

template <typename T, typename... TArgs>
void output_variadic_(std::ostream &out, T value, TArgs... args) {
    out << value << "\n";
    output_variadic_(out, args...);
}

#define panic(...)                                      \
{                                                   \
    std::cerr << "Panic in " << __FILE__;           \
    std::cerr << " on line " << __LINE__ << ": \n"; \
    output_variadic_(std::cerr, __VA_ARGS__);       \
    std::exit(1);                                   \
}

}  // namespace janncy

#endif  // PANIC_HPP_
