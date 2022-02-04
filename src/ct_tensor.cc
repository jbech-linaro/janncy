#include "include/ct_tensor.h"

#include <vector>

#include "include/ct_op.h"

namespace janncy {

CtTensor::CtTensor(std::vector<const CtOp*> ciphertexts,
                   std::vector<std::vector<int>> offsets)
    : ciphertexts_(std::move(ciphertexts)), offsets_(std::move(offsets)) {}

}  // namespace janncy
