#ifndef CIPHERTEXT_HPP_
#define CIPHERTEXT_HPP_

#include <vector>

namespace janncy {

class Ciphertext {
  public:
    explicit Ciphertext(std::vector<double> values);
    explicit Ciphertext(double value);
    Ciphertext();

    Ciphertext rotate(int amount) const;

    Ciphertext& operator*=(const Ciphertext& rhs);
    Ciphertext& operator+=(const Ciphertext& rhs);
    Ciphertext& operator-=(const Ciphertext& rhs);

    std::vector<double> decrypt() const;

  private:
    std::vector<double> values_;
};

Ciphertext operator*(const Ciphertext& lhs, const Ciphertext& rhs);
Ciphertext operator+(const Ciphertext& lhs, const Ciphertext& rhs);
Ciphertext operator-(const Ciphertext& lhs, const Ciphertext& rhs);

}  // namespace janncy

#endif  // CIPHERTEXT_HPP_
