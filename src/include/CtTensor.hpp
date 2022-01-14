#ifndef CT_TENSOR_HPP_
#define CT_TENSOR_HPP_

#include <vector>

#include "CtOp.hpp"

namespace janncy {

class CtTensor {
  public:
    explicit CtTensor(std::vector<const CtOp*> ciphertexts);
    const std::vector<const CtOp*>& ciphertexts() const;

  private:
    std::vector<const CtOp*> ciphertexts_;
};

}  // namespace janncy
#endif  // CT_TENSOR_HPP_
