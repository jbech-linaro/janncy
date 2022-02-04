#ifndef JANNCY_CT_TENSOR_H_
#define JANNCY_CT_TENSOR_H_

#include <vector>

#include "include/ct_op.h"
#include "include/tensor_layout.h"

namespace janncy {

class CtTensor {
 public:
  CtTensor(std::vector<const CtOp*> ciphertexts,
           std::vector<std::vector<int>> offsets);
  const std::vector<const CtOp*>& ciphertexts() const { return ciphertexts_; }
  const std::vector<std::vector<int>>& offsets() const { return offsets_; }

 private:
  std::vector<const CtOp*> ciphertexts_;
  std::vector<std::vector<int>> offsets_;
};

}  // namespace janncy
#endif  // JANNCY_CT_TENSOR_H_
