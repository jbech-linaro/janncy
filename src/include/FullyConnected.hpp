#ifndef FULLYCONNECTED_HPP_
#define FULLYCONNECTED_HPP_

#include "FlowNode.hpp"
#include "Tensor.hpp"

class FullyConnected : public FlowNode {
  public:
    static FullyConnected* create(FlowNode* parent, Tensor matrix) {
        return new FullyConnected(parent, matrix);
    }
    std::string type_str() const { return "FullyConnected"; }
    CtTensor cipherfy(std::vector<CtTensor> parents) const;

  private:
    FullyConnected(FlowNode* parent, Tensor matrix);
};

#endif  // FULLYCONNECTRED_HPP_
