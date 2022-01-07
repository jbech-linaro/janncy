#ifndef PANIC_HPP_
#define PANIC_HPP_

#include <iostream>
#include <cstdlib>
#include "include/ostream_utils.hpp"

void output_variadic_(std::ostream &out);

template <typename T, typename... TArgs>
void output_variadic_(std::ostream &out, T value, TArgs... args) {
    out << value << "\n";
    output_variadic_(out, args...);
}

#define panic(...)\
{ \
    std::cerr << "Panic in " << __FILE__; \
    std::cerr << " on line " << __LINE__  << ": \n"; \
    output_variadic_(std::cerr, __VA_ARGS__); \
    std::exit(1); \
}

#endif  // PANIC_HPP_
