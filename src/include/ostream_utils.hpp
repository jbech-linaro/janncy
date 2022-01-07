#ifndef OSTREAM_UTILS_HPP_
#define OSTREAM_UTILS_HPP_

#include <ostream>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream &out, const std::vector<T> &v) {
    out << "[";
    for (const auto &x : v) {
        out << x << ", ";
    }
    return out << "]";
}

#endif  // OSTREAM_UTILS_HPP_

