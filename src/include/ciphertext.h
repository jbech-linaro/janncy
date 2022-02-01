#ifndef JANNCY_CIPHERTEXT_H_
#define JANNCY_CIPHERTEXT_H_

#include <HEAAN/src/HEAAN.h>

#include "include/message.h"

namespace janncy {

class Ciphertext {
 public:
  explicit Ciphertext(heaan::Ciphertext ciphertext);

  Ciphertext Bootstrap() const;

  static int num_slots();

  Ciphertext MulCC(const Ciphertext& rhs) const;
  Ciphertext MulCP(const Message::Vector& message_vec) const;
  Ciphertext MulCS(Message::Scalar scalar) const;

  Ciphertext AddCC(const Ciphertext& rhs) const;
  Ciphertext AddCP(const Message::Vector& message_vec) const;
  Ciphertext AddCS(const Message::Scalar scalar) const;

  Ciphertext RotateC(int amt) const;

  static Ciphertext Encrypt(const Message::Vector& values);
  Message::Vector Decrypt() const;

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
