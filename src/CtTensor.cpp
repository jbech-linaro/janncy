#include "include/CtTensor.hpp"

#include <vector>

#include "include/CtOp.hpp"

namespace janncy {

CtTensor::CtTensor(std::vector<const CtOp*> ciphertexts)
        : ciphertexts_(std::move(ciphertexts)) {}

const std::vector<const CtOp*>& CtTensor::ciphertexts() const {
    return ciphertexts_;
}

}  // namespace janncy
