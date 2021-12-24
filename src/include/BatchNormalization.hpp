#ifndef BATCHNORMALIZATION_HPP_
#define BATCHNORMALIZATION_HPP_

#include "FlowNode.hpp"

class FlowVisitor;
class Flow;

class BatchNormalization : public FlowNode {
  public:
    BatchNormalization(std::vector<int> output_shape);

    void visit(Flow* flow, FlowVisitor* visitor);
};

#endif  // BATCHNORMALIZATION_HPP_
