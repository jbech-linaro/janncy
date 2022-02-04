#ifndef JANNCY_CT_TENSOR_H_
#define JANNCY_CT_TENSOR_H_

#include <vector>

#include "include/ct_op.h"
#include "include/tensor_layout.h"

namespace janncy {

class CtTensor {
 public:
  explicit CtTensor(std::vector<const CtOp*> ciphertexts);
  const std::vector<const CtOp*>& ciphertexts() const;

 private:
  std::vector<const CtOp*> ciphertexts_;
};

}  // namespace janncy
#endif  // JANNCY_CT_TENSOR_H_
