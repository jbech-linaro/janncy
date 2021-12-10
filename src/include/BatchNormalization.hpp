#ifndef BATCHNORMALIZATION_HPP_
#define BATCHNORMALIZATION_HPP_

#include "FlowNode.hpp"
#include "Tensor.hpp"

class FlowVisitor;

class BatchNormalization : public FlowNode {
  public:
    static BatchNormalization* create(FlowNode* parent) {
        return new BatchNormalization(parent);
    }
    void visit(FlowVisitor* visitor);
    std::string type_str() const { return "BatchNormalization"; }

  private:
    BatchNormalization(FlowNode* parent);
};

#endif  // BATCHNORMALIZATION_HPP_
