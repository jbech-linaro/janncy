#ifndef JANNCY_UTILS_H_
#define JANNCY_UTILS_H_

#include <ostream>
#include <sstream>
#include <string>
#include <vector>

namespace janncy {

double GetUniformRandom();

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
  out << "[";
  for (const auto& x : v) {
    out << x << ", ";
  }
  return out << "]";
}

template <typename T>
std::string ToString(const T& v) {
  std::stringstream ss;
  ss << v;
  return ss.str();  // Unfortunately, creates an unnecessary copy
}

}  // namespace janncy

#endif  // JANNCY_UTILS_H_
