#ifndef JANNCY_CIPHERTEXT_H_
#define JANNCY_CIPHERTEXT_H_

#include <HEAAN/src/HEAAN.h>

#include <complex>
#include <vector>

namespace janncy {

class Ciphertext {
 public:
  explicit Ciphertext(heaan::Ciphertext ciphertext);

  Ciphertext Rotate(int amount);

  Ciphertext& operator*=(Ciphertext rhs);
  Ciphertext& operator+=(Ciphertext rhs);
  Ciphertext& operator-=(Ciphertext rhs);

  Ciphertext AddPtVec(std::vector<std::complex<double> > pt_vec);
  Ciphertext MultPtVec(std::vector<std::complex<double> > pt_vec);

  std::vector<std::complex<double> > Decrypt();

  static heaan::Scheme* scheme();

  static int num_slots();

 private:
  static void InitScheme();

  heaan::Ciphertext ciphertext_;
  static heaan::Scheme* scheme_;
  static heaan::Ring* ring_;
  static heaan::SecretKey* secret_key_;
  static int num_slots_;
};

Ciphertext Encrypt(const std::vector<std::complex<double> >& values);
Ciphertext operator*(const Ciphertext& lhs, const Ciphertext& rhs);
Ciphertext operator+(const Ciphertext& lhs, const Ciphertext& rhs);
Ciphertext operator-(const Ciphertext& lhs, const Ciphertext& rhs);

}  // namespace janncy

#endif  // JANNCY_CIPHERTEXT_H_
