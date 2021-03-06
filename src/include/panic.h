#ifndef JANNCY_PANIC_H_
#define JANNCY_PANIC_H_

#include <cstdlib>
#include <iostream>

namespace janncy {

inline void CerrVariadic_() {}

template <typename T, typename... TArgs>
void CerrVariadic_(T value, TArgs... args) {
  std::cerr << value << "\n";
  CerrVariadic_(args...);
}

}  // namespace janncy

#define PANIC(...)                                                             \
  {                                                                            \
    std::cerr << "Panic in " << __FILE__ << " on line " << __LINE__ << ": \n"; \
    ::janncy::CerrVariadic_(__VA_ARGS__);                                      \
    std::exit(1);                                                              \
  }

#define PANIC_IF(CONDITION, ...)                                      \
  {                                                                   \
    bool cond_value = CONDITION;                                      \
    if (cond_value) {                                                 \
      std::cerr << "Panic in " << __FILE__ << " on line " << __LINE__ \
                << ": \n"                                             \
                << "Triggered by " << #CONDITION << "\n";             \
      ::janncy::CerrVariadic_(__VA_ARGS__);                           \
      std::exit(1);                                                   \
    }                                                                 \
  }

#endif  // JANNCY_PANIC_H_
