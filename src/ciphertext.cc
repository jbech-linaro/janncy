#include "include/ciphertext.h"

#include <HEAAN/src/HEAAN.h>
#include <NTL/ZZ.h>

#include <algorithm>
#include <cassert>
#include <complex>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "include/message.h"
#include "include/utils.h"

namespace janncy {

namespace {

std::unique_ptr<std::complex<double>[]> MessageVecToHeaanMessage(
    const Message::Vector& message_vec) {
  std::unique_ptr<std::complex<double>[]> result(
      new std::complex<double>[message_vec.size()]);
  for (int idx = 0; idx < Ciphertext::num_slots(); idx++) {
    result[idx] = std::complex<double>(message_vec[idx], 0);
  }
  return result;
}

Message::Vector HeaanMessageToMessageVec(std::complex<double>* heaan_message) {
  auto result = Message::Vector{};
  for (int idx = 0; idx < Ciphertext::num_slots(); idx++) {
    result.push_back(heaan_message[idx].real());
  }
  delete[] heaan_message;
  return result;
}

}  // namespace

int Ciphertext::logp = 30;

heaan::Scheme* Ciphertext::scheme_ = nullptr;
heaan::Ring* Ciphertext::ring_ = nullptr;
heaan::SecretKey* Ciphertext::secret_key_ = nullptr;
int Ciphertext::num_slots_ = 8;

Ciphertext Ciphertext::Bootstrap() const {
  heaan::Ciphertext result(ciphertext_);
  Ciphertext::scheme_->bootstrapAndEqual(result, /*logq=*/40, /*logQ=*/800,
                                         /*logT=*/4, /*logI=*/4);
  return Ciphertext(result);
}

Ciphertext::Ciphertext(heaan::Ciphertext ciphertext)
    : ciphertext_(ciphertext) {}

Ciphertext Ciphertext::MulCC(const Ciphertext& rhs) const {
  heaan::Ciphertext ct_result(ciphertext_);
  // TODO(nsamar): The `const_cast` is necessary because HEAAN
  // does not const-qualify its functions properly.
  // When this is fixed, all `const_cast`s in this file should
  // be removed.
  Ciphertext::scheme_->multAndEqual(
      ct_result, const_cast<heaan::Ciphertext&>(rhs.ciphertext_));
  return Ciphertext(ct_result);
}

Ciphertext Ciphertext::MulCP(const Message::Vector& message_vec) const {
  heaan::Ciphertext ct_result;
  auto heaan_message = MessageVecToHeaanMessage(message_vec);
  scheme_->multByConstVec(ct_result,
                          const_cast<heaan::Ciphertext&>(ciphertext_),
                          heaan_message.get(), Ciphertext::logp / 2);
  return Ciphertext(ct_result);
}

Ciphertext Ciphertext::MulCS(Message::Scalar scalar) const {
  heaan::Ciphertext ct_result(ciphertext_);
  Ciphertext::scheme_->multByConst(ct_result,
                                   const_cast<heaan::Ciphertext&>(ciphertext_),
                                   scalar, Ciphertext::logp);
  return Ciphertext(ct_result);
}

Ciphertext Ciphertext::AddCC(const Ciphertext& rhs) const {
  heaan::Ciphertext ct_result(ciphertext_);
  Ciphertext::scheme_->addAndEqual(
      ct_result, const_cast<heaan::Ciphertext&>(rhs.ciphertext_));
  return Ciphertext(ct_result);
}

Ciphertext Ciphertext::AddCP(const Message::Vector& message_vec) const {
  auto pt = Encrypt(message_vec);
  heaan::Ciphertext ct_result;
  scheme_->add(ct_result, const_cast<heaan::Ciphertext&>(ciphertext_),
               pt.ciphertext_);
  return Ciphertext(ct_result);
}

Ciphertext Ciphertext::AddCS(Message::Scalar scalar) const {
  heaan::Ciphertext ct_result(ciphertext_);
  Ciphertext::scheme_->addConst(ct_result,
                                const_cast<heaan::Ciphertext&>(ciphertext_),
                                scalar, Ciphertext::logp);
  return Ciphertext(ct_result);
}

Ciphertext Ciphertext::RotateC(int amount) const {
  auto ct_result = heaan::Ciphertext();
  scheme_->leftRotateFast(ct_result,
                          const_cast<heaan::Ciphertext&>(ciphertext_), amount);
  return Ciphertext(ct_result);
}

Message::Vector Ciphertext::Decrypt() const {
  auto heaan_message = scheme_->decrypt(
      *secret_key_, const_cast<heaan::Ciphertext&>(ciphertext_));
  return HeaanMessageToMessageVec(heaan_message);
}

void Ciphertext::InitScheme() {
  assert(!scheme_);
  ring_ = new heaan::Ring();
  secret_key_ = new heaan::SecretKey(*ring_);
  scheme_ = new heaan::Scheme(*secret_key_, *ring_, /*isSerialized=*/true);
  std::cout << "Adding rotate keys..." << std::endl;
  scheme_->addLeftRotKeys(*secret_key_);
  std::cout << "Adding bootstrapping keys..." << std::endl;
  scheme_->addBootKey(*secret_key_, 3, 44);
  srand(0);
  num_slots_ = 8;
}

heaan::Scheme* Ciphertext::scheme() {
  if (!scheme_) {
    InitScheme();
  }
  return scheme_;
}

int Ciphertext::num_slots() { return num_slots_; }

Ciphertext Ciphertext::Encrypt(const Message::Vector& values) {
  auto ct = heaan::Ciphertext();
  auto value_array = MessageVecToHeaanMessage(values);
  Ciphertext::scheme()->encrypt(ct, value_array.get(), Ciphertext::num_slots(),
                                Ciphertext::logp, /*logQ=*/800);
  return Ciphertext(ct);
}

}  // namespace janncy
