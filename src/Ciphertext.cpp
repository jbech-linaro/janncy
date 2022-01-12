#include "include/Ciphertext.hpp"

#include "include/utils.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

namespace janncy {

static int N = 16;

Ciphertext::Ciphertext(double value) : values_(N / 2, value) {}

Ciphertext::Ciphertext() : values_(N / 2) {
    std::generate(values_.begin(), values_.end(), get_uniform_random);
}

Ciphertext::Ciphertext(std::vector<double> values) : values_(values) {
    assert(int(values_.size()) == N / 2);
}

Ciphertext operator*(const Ciphertext& lhs, const Ciphertext& rhs) {
    Ciphertext result(lhs);
    result *= rhs;
    return result;
}

Ciphertext operator+(const Ciphertext& lhs, const Ciphertext& rhs) {
    Ciphertext result(lhs);
    result += rhs;
    return result;
}

Ciphertext operator-(const Ciphertext& lhs, const Ciphertext& rhs) {
    Ciphertext result(lhs);
    result -= rhs;
    return result;
}

Ciphertext& Ciphertext::operator*=(const Ciphertext& rhs) {
    assert(values_.size() == rhs.values_.size());
    std::transform(rhs.values_.cbegin(), rhs.values_.cend(), values_.begin(),
                   values_.begin(), std::multiplies<double>());
    return *this;
}

Ciphertext& Ciphertext::operator+=(const Ciphertext& rhs) {
    assert(values_.size() == rhs.values_.size());
    std::transform(rhs.values_.cbegin(), rhs.values_.cend(), values_.begin(),
                   values_.begin(), std::plus<double>());
    return *this;
}

Ciphertext& Ciphertext::operator-=(const Ciphertext& rhs) {
    assert(values_.size() == rhs.values_.size());
    std::transform(rhs.values_.cbegin(), rhs.values_.cend(), values_.begin(),
                   values_.begin(), std::minus<double>());
    return *this;
}

Ciphertext Ciphertext::rotate(int amount) const {
    while (amount <= 0) {
        amount += int(values_.size());
    }
    std::vector<double> new_values = this->values_;
    std::rotate(new_values.begin(), new_values.begin() + amount,
                new_values.end());
    return Ciphertext(new_values);
}

std::vector<double> Ciphertext::decrypt() const { return values_; }

}  // namespace janncy
