#ifndef BATCHNORMALIZATION_HPP_
#define BATCHNORMALIZATION_HPP_

#include "FlowNode.hpp"
#include "Tensor.hpp"

class BatchNormalization : public FlowNode {
  public:
    static BatchNormalization* create(FlowNode* parent) {
        return new BatchNormalization(parent);
    }
    std::string type_str() const { return "BatchNormalization"; }
    CtTensor cipherfy(std::vector<CtTensor> parents) const;

  private:
    BatchNormalization(FlowNode* parent);
};

#endif  // BATCHNORMALIZATION_HPP_
