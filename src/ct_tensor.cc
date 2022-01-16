#include "include/ct_tensor.h"

#include <vector>

#include "include/ct_op.h"

namespace janncy {

CtTensor::CtTensor(std::vector<const CtOp*> ciphertexts)
    : ciphertexts_(std::move(ciphertexts)) {}

const std::vector<const CtOp*>& CtTensor::ciphertexts() const {
  return ciphertexts_;
}

}  // namespace janncy
