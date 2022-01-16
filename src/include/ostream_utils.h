#ifndef JANNCY_OSTREAM_UTILS_H_
#define JANNCY_OSTREAM_UTILS_H_

#include <ostream>
#include <vector>

namespace janncy {

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &v) {
  out << "[";
  for (const auto &x : v) {
    out << x << ", ";
  }
  return out << "]";
}

}  // namespace janncy

#endif  // JANNCY_OSTREAM_UTILS_H_
