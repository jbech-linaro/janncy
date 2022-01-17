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
std::string kAllKeysAddedStamp = "/tmp/AllKeysAddedStamp";

Ciphertext::Ciphertext(heaan::Ciphertext ciphertext)
    : ciphertext_(ciphertext) {}

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

Ciphertext& Ciphertext::operator*=(Ciphertext rhs) {
  scheme_->multAndEqual(ciphertext_, rhs.ciphertext_);
  return *this;
}

Ciphertext& Ciphertext::operator+=(Ciphertext rhs) {
  scheme_->addAndEqual(ciphertext_, rhs.ciphertext_);
  return *this;
}

Ciphertext& Ciphertext::operator-=(Ciphertext rhs) {
  scheme_->subAndEqual(ciphertext_, rhs.ciphertext_);
  return *this;
}

Ciphertext Ciphertext::Rotate(int amount) {
  auto ct_result = heaan::Ciphertext();
  scheme_->leftRotateFast(ct_result, ciphertext_, amount);
  return Ciphertext(ct_result);
}

std::vector<std::complex<double> > Ciphertext::Decrypt() {
  auto ptr_result = scheme_->decrypt(*secret_key_, ciphertext_);
  auto result = std::vector<std::complex<double> >{};
  for (int idx = 0; idx < num_slots_; idx++) {
    result.push_back(ptr_result[idx]);
  }
  delete[] ptr_result;
  return result;
}

namespace {

bool KeysExist() {
  std::ifstream stamp_file_in;
  stamp_file_in.open(kAllKeysAddedStamp);
  if (stamp_file_in.fail()) {
    stamp_file_in.close();
    std::ofstream stamp_file;
    stamp_file.open(kAllKeysAddedStamp);
    stamp_file << "dummy" << std::endl;
    stamp_file.close();
    return false;
  }
  stamp_file_in.close();
  return true;
}

}  // namespace

void Ciphertext::InitScheme() {
  assert(!scheme_);
  ring_ = new heaan::Ring();
  secret_key_ = new heaan::SecretKey(*ring_);
  scheme_ = new heaan::Scheme(*secret_key_, *ring_, /*isSerialized=*/true);
  std::ifstream stamp_file_in;
  stamp_file_in.open(kAllKeysAddedStamp);
  if (!KeysExist()) {
    std::cout << "Adding rotate keys..." << std::endl;
    scheme_->addLeftRotKeys(*secret_key_);
    std::cout << "Adding bootstrapping keys..." << std::endl;
    scheme_->addBootKey(*secret_key_, 10, 35);
  }
  num_slots_ = 8;
}

heaan::Scheme* Ciphertext::scheme() {
  if (!scheme_) {
    InitScheme();
  }
  return scheme_;
}

int Ciphertext::num_slots() { return num_slots_; }

Ciphertext Encrypt(const std::vector<std::complex<double> >& values) {
  assert(values.size() == Ciphertext::num_slots());
  auto ct = heaan::Ciphertext();
  std::complex<double>* value_array =
      new std::complex<double>[Ciphertext::num_slots()];
  for (int idx = 0; idx < Ciphertext::num_slots(); idx++) {
    value_array[idx] = values[idx];
  }
  Ciphertext::scheme()->encrypt(ct, value_array, Ciphertext::num_slots(),
                                /*logp=*/30, heaan::logQ);
  delete[] value_array;
  return Ciphertext(ct);
}

Ciphertext Ciphertext::AddPtVec(std::vector<std::complex<double> > pt_vec) {
  auto pt = Encrypt(pt_vec);
  heaan::Ciphertext ct_result;
  scheme_->add(ct_result, ciphertext_, pt.ciphertext_);
  return Ciphertext(ct_result);
}

Ciphertext Ciphertext::MultPtVec(std::vector<std::complex<double> > pt_vec) {
  heaan::Ciphertext ct_result;
  std::complex<double>* const_vec =
      new std::complex<double>[Ciphertext::num_slots()];
  for (int idx = 0; idx < Ciphertext::num_slots(); idx++) {
    const_vec[idx] = pt_vec[idx];
  }
  scheme_->multByConstVec(ct_result, ciphertext_, const_vec, /*logp/2=*/15);
  delete[] const_vec;
  return Ciphertext(ct_result);
}

}  // namespace janncy
