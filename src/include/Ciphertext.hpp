#ifndef CIPHERTEXT_HPP_
#define CIPHERTEXT_HPP_

#include <HEAAN/src/HEAAN.h>

#include <vector>
#include <complex>

namespace janncy {

class Ciphertext {
  public:
    explicit Ciphertext(heaan::Ciphertext ciphertext);

    Ciphertext rotate(int amount);

    Ciphertext& operator*=(Ciphertext rhs);
    Ciphertext& operator+=(Ciphertext rhs);
    Ciphertext& operator-=(Ciphertext rhs);

    Ciphertext addPtVec(std::vector<std::complex<double> > pt_vec);
    Ciphertext multPtVec(std::vector<std::complex<double> > pt_vec);

    std::vector<std::complex<double> > decrypt();

    static heaan::Scheme* scheme();

    static int num_slots();

  private:
    static void init_scheme();
    heaan::Ciphertext ciphertext_;
    static heaan::Scheme* scheme_;
    static heaan::Ring* ring_;
    static heaan::SecretKey* secret_key_;
    static int num_slots_;
};

Ciphertext encrypt(const std::vector<std::complex<double> >& values);
Ciphertext operator*(const Ciphertext& lhs, const Ciphertext& rhs);
Ciphertext operator+(const Ciphertext& lhs, const Ciphertext& rhs);
Ciphertext operator-(const Ciphertext& lhs, const Ciphertext& rhs);

}  // namespace janncy

#endif  // CIPHERTEXT_HPP_
