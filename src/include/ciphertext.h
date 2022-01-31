#ifndef JANNCY_CIPHERTEXT_H_
#define JANNCY_CIPHERTEXT_H_

#include <HEAAN/src/HEAAN.h>

#include "include/message.h"

namespace janncy {

class Ciphertext {
 public:
  explicit Ciphertext(heaan::Ciphertext ciphertext);

  Ciphertext Rotate(int amount);

  Ciphertext Bootstrap();

  Ciphertext AddPtVec(Message pt_vec);
  Ciphertext MultPtVec(Message pt_vec);

  Message Decrypt();

  static int num_slots();

  Ciphertext ConstMultiply(double rhs) const;
  Ciphertext ConstAdd(double rhs) const;

  Ciphertext Multiply(const Ciphertext& rhs) const;
  Ciphertext Add(const Ciphertext& rhs) const;
  Ciphertext Subtract(const Ciphertext& rhs) const;

  static Ciphertext Encrypt(const Message& values);

 private:
  static void InitScheme();
  static int logp;

  static heaan::Scheme* scheme();
  heaan::Ciphertext ciphertext_;
  static heaan::Scheme* scheme_;
  static heaan::Ring* ring_;
  static heaan::SecretKey* secret_key_;
  static int num_slots_;
};

}  // namespace janncy

#endif  // JANNCY_CIPHERTEXT_H_
