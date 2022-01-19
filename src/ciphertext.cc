#include "include/ciphertext.h"

#include <HEAAN/src/HEAAN.h>
#include <NTL/ZZ.h>

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

#include "include/utils.h"

namespace janncy {

heaan::Scheme* Ciphertext::scheme_ = nullptr;
heaan::Ring* Ciphertext::ring_ = nullptr;
heaan::SecretKey* Ciphertext::secret_key_ = nullptr;
int Ciphertext::num_slots_ = 8;

Ciphertext Ciphertext::Bootstrap() {
  heaan::Ciphertext result(ciphertext_);
  Ciphertext::scheme_->bootstrapAndEqual(result, /*logq=*/40, /*logQ=*/800,
                                         /*logT=*/4, /*logI=*/4);
  return Ciphertext(result);
}

Ciphertext::Ciphertext(heaan::Ciphertext ciphertext)
    : ciphertext_(ciphertext) {}

Ciphertext Ciphertext::Multiply(const Ciphertext& rhs) const {
  heaan::Ciphertext ct_result(ciphertext_);
  // TODO(nsamar): The `const_cast` is necessary because HEAAN
  // does not const-qualify its functions properly.
  // When this is fixed, all `const_cast`s in this file should
  // be removed.
  Ciphertext::scheme_->multAndEqual(
      ct_result, const_cast<heaan::Ciphertext&>(rhs.ciphertext_));
  return Ciphertext(ct_result);
}

Ciphertext Ciphertext::Add(const Ciphertext& rhs) const {
  heaan::Ciphertext ct_result(ciphertext_);
  Ciphertext::scheme_->addAndEqual(
      ct_result, const_cast<heaan::Ciphertext&>(rhs.ciphertext_));
  return Ciphertext(ct_result);
}

Ciphertext Ciphertext::Subtract(const Ciphertext& rhs) const {
  heaan::Ciphertext ct_result(ciphertext_);
  Ciphertext::scheme_->subAndEqual(
      ct_result, const_cast<heaan::Ciphertext&>(rhs.ciphertext_));
  return Ciphertext(ct_result);
}

Ciphertext Ciphertext::Rotate(int amount) {
  auto ct_result = heaan::Ciphertext();
  scheme_->leftRotateFast(ct_result, ciphertext_, amount);
  return Ciphertext(ct_result);
}

Message Ciphertext::Decrypt() {
  auto ptr_result = scheme_->decrypt(*secret_key_, ciphertext_);
  auto result = Message{};
  for (int idx = 0; idx < num_slots_; idx++) {
    result.push_back(ptr_result[idx]);
  }
  delete[] ptr_result;
  return result;
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

Ciphertext Ciphertext::Encrypt(const Message& values) {
  assert(values.size() == Ciphertext::num_slots());
  auto ct = heaan::Ciphertext();
  MessageElement* value_array = new MessageElement[Ciphertext::num_slots()];
  for (int idx = 0; idx < Ciphertext::num_slots(); idx++) {
    value_array[idx] = values[idx];
  }
  Ciphertext::scheme()->encrypt(ct, value_array, Ciphertext::num_slots(),
                                /*logp=*/30, /*logQ=*/800);
  std::cout << "Slots: " << ct.n << std::endl;
  delete[] value_array;
  return Ciphertext(ct);
}

Ciphertext Ciphertext::AddPtVec(Message pt_vec) {
  auto pt = Encrypt(pt_vec);
  heaan::Ciphertext ct_result;
  scheme_->add(ct_result, ciphertext_, pt.ciphertext_);
  return Ciphertext(ct_result);
}

Ciphertext Ciphertext::MultPtVec(Message pt_vec) {
  heaan::Ciphertext ct_result;
  MessageElement* const_vec = new MessageElement[Ciphertext::num_slots()];
  for (int idx = 0; idx < Ciphertext::num_slots(); idx++) {
    const_vec[idx] = pt_vec[idx];
  }
  scheme_->multByConstVec(ct_result, ciphertext_, const_vec, /*logp/2=*/15);
  delete[] const_vec;
  return Ciphertext(ct_result);
}

}  // namespace janncy
