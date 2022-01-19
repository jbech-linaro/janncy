#ifndef JANNCY_CIPHERTEXT_H_
#define JANNCY_CIPHERTEXT_H_

#include <HEAAN/src/HEAAN.h>

#include <complex>
#include <vector>

namespace janncy {

using Message = std::vector<std::complex<double>>;

class Ciphertext {
 public:
  explicit Ciphertext(heaan::Ciphertext ciphertext);

  Ciphertext Rotate(int amount);

  Ciphertext& operator*=(Ciphertext rhs);
  Ciphertext& operator+=(Ciphertext rhs);
  Ciphertext& operator-=(Ciphertext rhs);

  Ciphertext Bootstrap();

  Ciphertext AddPtVec(Message pt_vec);
  Ciphertext MultPtVec(Message pt_vec);

  Message Decrypt();

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

Ciphertext Encrypt(const Message& values);
Ciphertext operator*(const Ciphertext& lhs, const Ciphertext& rhs);
Ciphertext operator+(const Ciphertext& lhs, const Ciphertext& rhs);
Ciphertext operator-(const Ciphertext& lhs, const Ciphertext& rhs);

}  // namespace janncy

#endif  // JANNCY_CIPHERTEXT_H_
