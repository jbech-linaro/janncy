#ifndef RELU_HPP_
#define RELU_HPP_

#include "FlowNode.hpp"
#include "Tensor.hpp"

class ReLU : public FlowNode {
  public:
    static ReLU* create(FlowNode* parent) { return new ReLU(parent); }
    std::string type_str() const { return "ReLU"; }
    CtTensor cipherfy(std::vector<CtTensor> parents) const;

  private:
    ReLU(FlowNode* parent);
};

#endif  // RELU_HPP_
