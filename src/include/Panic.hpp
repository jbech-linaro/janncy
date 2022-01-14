#ifndef PANIC_HPP_
#define PANIC_HPP_

#include <cstdlib>
#include <iostream>

#include "ostream_utils.hpp"

namespace janncy {

inline void cerr_variadic_() {}

template <typename T, typename... TArgs>
inline void cerr_variadic_(T value, TArgs... args) {
    std::cerr << value << "\n";
    cerr_variadic_(args...);
}

}  // namespace janncy

#define PANIC(...)\
{ \
    std::cerr << "Panic in " << __FILE__ \
              << " on line " << __LINE__  << ": \n"; \
    ::janncy::cerr_variadic_(__VA_ARGS__); \
    std::exit(1); \
}

#define PANIC_IF(CONDITION, ...)\
{ \
    bool cond_value = CONDITION; \
    if (cond_value) { \
        std::cerr << "Panic in " << __FILE__ \
                  << " on line " << __LINE__  << ": \n" \
                  << "Triggered by " << #CONDITION << "\n"; \
        ::janncy::cerr_variadic_(__VA_ARGS__); \
        std::exit(1); \
    } \
}

#endif  // PANIC_HPP_
