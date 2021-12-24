#ifndef ENCRYPTED_TENSOR_HPP_
#define ENCRYPTED_TENSOR_HPP_

#include <vector>

class CtOp;

class CtTensor {
  public:
    explicit CtTensor(std::vector<CtOp*> parents);
    std::vector<CtOp*> get_ct_ops() const;

  private:
    std::vector<CtOp*> parents_;
};

#endif  // ENCRYPTED_TENSOR_HPP_
